#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <signal.h>
#include <unistd.h>
#include <pthread.h>

#include "bus.h"
#include "game.h"

#define REGISTER_BASE 0x30
#define SRAM_BASE 0x29000

int deadlock = 0;

#define CTRL_DIRECTION (1 << 0)
#define CTRL_SENSE (1 << 1)
#define CTRL_UNLOCK (1 << 2)

struct __attribute__((packed)) cache_buf {
	uint32_t *buffer;
	uint32_t *tags;
	/*
		bit 0 - direction (read or write)
		bit 1 - sense data
		bit 2 - aes encryption on/off
		bit 3 - aes peek sense
		bit 4 - aes mirror
		bit 5 - secure
	*/
	uint32_t control;
	uint32_t locked;

	/*
		0 - not started
		1 - in progress
		2 - done
		3 - error
	*/
	uint32_t status;
	uint32_t cache_config;
	uint32_t flush_addr;
	uint8_t *tag_addr;
	int32_t tag_offset;
	uint32_t history_idx;
	/*
		0 - no prefetch
		1 - prefetch in rotating order, each tick
		2 - prefetch sequentually from shortaddress in top 16 bits of this field
	*/
	uint32_t prefetch_ctrl;
	uint32_t bypass_mask;
	uint32_t running_xor;
	uint32_t history[0x100];
	uint32_t secure_lock;
};

// the current DMA structure we are using
static struct cache_buf *curr_cache = NULL;

uint32_t resolve_cache_index(uint32_t shortaddr) {
	// converts an address to where it (would) be located in the cache
	return (shortaddr & 0xfff) * 0x9e3779b1 >> 24;
}

void update_cache_state(uint32_t address, uint32_t data) {
	// this will process the sram state and make the relevant updates so it is consistent
	// this happens once per sense. sram does not rely on reaching out to any other services,
	// so we can be sure this function will not do any bus_read or bus_write calls

	// check if we are doing a read or a write
	log("update_cache_state: ctrl is 0x%x\n", curr_cache->control);
	if (curr_cache->control & CTRL_SENSE) {
		if (curr_cache->control & CTRL_DIRECTION) {
			// doing a READ
			log("update_cache_state: doing a READ from 0x%x", address);
		} else {
			// doing a WRITE
			log("update_cache_state: doing a WRITE to 0x%x <- 0x%x", address, data);
		}
		curr_cache->control -= CTRL_SENSE;
	}
	if (curr_cache->control & CTRL_UNLOCK) {
		curr_cache->secure_lock = 0;
	}
}

void flush_addr() {
	// flush this address from the cache, but only if it's in the cache already
	curr_cache->tags[resolve_cache_index(curr_cache->flush_addr)] = 0xffffffff;
}

void flush_all() {
	// flush the entire cache
	memset(curr_cache->tags, 0xff, 0x400);
	free(curr_cache->tag_addr);
	curr_cache->tag_addr = NULL;
}

int in_cache(uint32_t shortaddr) {
	if ((curr_cache->bypass_mask & shortaddr) != 0) {
		return 0;
	}
	// returns true if an address is in the cache
	if (curr_cache->tags[resolve_cache_index(shortaddr)] == shortaddr)
		return 1;
	return 0;
}

void memory_write(uint32_t shortaddr, uint32_t value) {
	// actually read the memory from sram
	uint32_t real_address = shortaddr;
	bus_write(SRAM_BASE + 8, shortaddr);
	bus_write(SRAM_BASE + 0x100, value);
	bus_write(SRAM_BASE + 0, CTRL_SENSE);
	log("memory_write(0x%x, 0x%x)\n", shortaddr, value);
}

uint32_t memory_read(uint32_t shortaddr) {
	// actually read the memory from sram
	uint32_t real_address = shortaddr;
	bus_write(SRAM_BASE + 8, shortaddr);
	bus_write(SRAM_BASE + 0, CTRL_SENSE | CTRL_DIRECTION);

	uint32_t result = bus_read(SRAM_BASE + 0x100);
	log("memory_read(0x%x) -> 0x%x\n", shortaddr, result);
	return result;
}

uint32_t cache_resolve(int is_read, uint32_t shortaddr, uint32_t data) {
	// our address here is a 16-bit shortaddr that is intended for sram
	// we handle both reads and writes here
	uint32_t result = 0;
	int cache_idx = resolve_cache_index(shortaddr);
	log("cache_result (%s) 0x%x -> 0x%x (data: 0x%x)\n", is_read ? "READ" : "WRITE", shortaddr, cache_idx, data);
	if (is_read) {
		if (in_cache(shortaddr)) {
			result = curr_cache->buffer[cache_idx];
			curr_cache->running_xor ^= result;
			log("\tin buf, 0x%x -> %x\n", shortaddr, result);
		} else {
			// directly fetch this an update
			result = memory_read(shortaddr);

			curr_cache->buffer[cache_idx] = result;
			curr_cache->running_xor ^= result;
			curr_cache->tags[cache_idx] = shortaddr;
		}
	} else {
		// handling a write
		int cache_idx = resolve_cache_index(shortaddr);

		// TODO: how do we track and handle writeback?
		curr_cache->buffer[cache_idx] = data;
		curr_cache->running_xor ^= result;
		curr_cache->tags[cache_idx] = shortaddr;
		memory_write(shortaddr, data);
	}
	return result;
}

uint32_t mmio_handler(int is_read, uint32_t address, uint32_t data) {
	if (deadlock) return 0;

	log("cache mmio_handler(%d, 0x%x, 0x%x)\n", is_read, address, data);

	if ((address & 0xf000) != 0) {
		// this is a lookup intended for sram
		// the nibble at 0xf000 will be +1 what it is intended to be
		// and obviously the target is intended to be sram instead
		address = (address - 0x1000) & 0xffff;

		return cache_resolve(is_read, address, data);
	}

	address &= 0xfff;

	/* store address and data into history buffer */
	curr_cache->history[curr_cache->history_idx++] = address - REGISTER_BASE;
	if (curr_cache->history_idx > 0x30) curr_cache->history_idx = 0;
	curr_cache->history[curr_cache->history_idx++] = data;
	if (curr_cache->history_idx > 0x30) curr_cache->history_idx = 0;

	switch(address - REGISTER_BASE) {
	case 0: /* CTRL */
		if (is_read) {
			return 0; // RAZ
		} else {
			if (!curr_cache->control) {
				curr_cache->control = data;
			}
		}
		update_cache_state(address, data);
		break;
	case 4: /* STATUS */
		return 0xffffffff;
	case 8: /* CONFIG */
		if (is_read) {
			return curr_cache->cache_config;
		} else {
			if (!curr_cache->locked)
				curr_cache->cache_config = data;
		}
		break;
	case 0xc: /* FLUSH_ADDR */
		if (is_read) {
			return 0;
		} else {
			if (!curr_cache->locked) {
				curr_cache->flush_addr = (data - 0x1000) & 0xffff;
				flush_addr();
			}
		}
		break;
	case 0x10: /* FLUSH_ALL */
		if (is_read) {
			return 0;
		} else {
			if (!curr_cache->locked) {
				flush_all();
			}
		}
		break;
	case 0x14: /* HISTORY_IDX */
		if (is_read) {
			return curr_cache->history_idx;
		} else {
			if (!curr_cache->locked)
				curr_cache->history_idx = 0;
		}
		break;
	case 0x18: /* DEADLOCK */
		// writing here deadlocks forever ;)
		deadlock = 1;
		break;
	case 0x1c: /* TAG_ADDR */
		if (is_read) {
			return (uint32_t)curr_cache->tag_addr;
		} else {
			if (!curr_cache->locked && (curr_cache->secure_lock == 0)) {
				if (!curr_cache->tag_addr) {
					curr_cache->tag_addr = malloc(data);
					memset(curr_cache->tag_addr, 0x33, data);
				} else {
					curr_cache->tag_offset = data;
				}
			}
		}
		break;
	case 0x20: /* TAG_DATA */
		if (is_read) {
			return 0;
		} else {
			if (!curr_cache->locked && (curr_cache->secure_lock == 0)) {
				if (curr_cache->tag_addr) {
					*(uint32_t *)(curr_cache->tag_addr + curr_cache->tag_offset) = data;
				}
			}
		}
		break;
	case 0x24: /* SECURE_LENGTH */
		return 0xffffffff;
	case 0x28: /* SECURE_LOCK */
		if (is_read) {
			return curr_cache->secure_lock;
		} else {
			if (!curr_cache->locked && (curr_cache->secure_lock == 0))
				curr_cache->secure_lock = data != 0;
		}
		break;
	case 0x2c: /* PREFETCH_CTRL */
		if (is_read) {
			return curr_cache->prefetch_ctrl;
		} else {
			curr_cache->prefetch_ctrl = data;
		}
		break;
	case 0x30: /* RUNNING_XOR */
		if (is_read) {
			return curr_cache->running_xor;
		} else {
			curr_cache->running_xor = data;
		}
		break;
	default:
		if (address - REGISTER_BASE >= 0x100) {
			if (address - REGISTER_BASE < 0x100 + sizeof(curr_cache->history) + (curr_cache->history_idx*4)) {
				/* SRAM_LOG_HISTORY */
				uintptr_t offset = address - REGISTER_BASE - 0x100;
				if (is_read) {
					return curr_cache->history[offset >> 2];
				} else {
					curr_cache->history[offset >> 2] = 0;
				}
			}
		}
		break;
	}

	return 0;
}

void cache_process_next() {

	// on each tick we process any outstanding work items, if we have them
	switch (curr_cache->prefetch_ctrl & 0xff) {
	case 1: {
			uint32_t next_idx = curr_cache->prefetch_ctrl >> 24;
			log("cache doing prefetch strategy 1, idx 0x%x\n", next_idx);
			uint32_t shortaddr = curr_cache->tags[next_idx];
			int cache_idx = resolve_cache_index(shortaddr);
			uint32_t result = memory_read(shortaddr);

			curr_cache->buffer[cache_idx] = result;
			curr_cache->running_xor ^= result;
			curr_cache->tags[cache_idx] = shortaddr;
			curr_cache->prefetch_ctrl = (curr_cache->prefetch_ctrl & 0x00ffffff) | (++next_idx) << 24;
			break;
		}
	case 2:
		{
			uint32_t shortaddr = curr_cache->prefetch_ctrl >> 16;
			log("cache doing prefetch strategy 2, shortaddr 0x%x\n", shortaddr);
			int cache_idx = resolve_cache_index(shortaddr);
			uint32_t result = memory_read(shortaddr);

			curr_cache->buffer[cache_idx] = result;
			curr_cache->running_xor ^= result;
			curr_cache->tags[cache_idx] = shortaddr;
			curr_cache->prefetch_ctrl = (curr_cache->prefetch_ctrl & 0xff) | (shortaddr + 4) << 16;
			break;
		}
	default:
		break;
	}
}

int main(int argc, char **argv) {

	setvbuf(stdin, NULL, _IONBF, 0);
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	int id = atoi(getenv("ID"));
	int driver_pid = atoi(getenv("D"));

	log("child %s (id %d) targeting driver pid %d\n", argv[0], id, driver_pid);

	transaction_t *data_queue = NULL;

	// set queue depth
	arrsetcap(data_queue, 10);

	bus_init(driver_pid, data_queue, id);
	lockdown_chip(driver_pid);

	// initialize our dma buffer
	curr_cache = calloc(1, sizeof(*curr_cache));

	// allocate our actual cache buffers
	curr_cache->buffer = calloc(4, 0x100);
	curr_cache->tags = calloc(4, 0x100);
	curr_cache->secure_lock = 1;

	// indicate to the driver that we have loaded and are ready
	log("driver pid is %d\n", driver_pid);
	kill(driver_pid, SIGRTMIN+1);

	// for purposes of debug: issue a read to our friend
	while (1) {

		// wait for tick to increment
		while (!active_tick) {
			usleep(5000);
		}
		active_tick = 0;

		// process all packets
		while (arrlen(data_queue) > 0) {
			log("child %d processing packet on tick %d\n", id, g_tick);

			// pop next packet
			transaction_t incoming = arrpop(data_queue);

			log("child %d received %s for 0x%x 0x%x\n", id, incoming.is_read ? "READ" : "WRITE", incoming.address << 2, incoming.data);
			uint32_t result = mmio_handler(incoming.is_read, incoming.address << 2, incoming.data);

			// construct our ack
			incoming.data = result;
			incoming.address = incoming.srcid << 14;
			incoming.srcid = 0xf;

			submit_tx(incoming, NULL);
		}

		cache_process_next();
	}

	log("goodbye\n");
	return 0;
}