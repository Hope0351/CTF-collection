#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <signal.h>
#include <unistd.h>
#include <pthread.h>

#include "bus.h"
#include "game.h"


#define REGISTER_BASE 0x3000

int deadlock = 0;

static volatile uint8_t *checkpoint_buf = NULL;

struct dma_buf {
	/*
		bit 0 - direction
	*/
	uint32_t control;
	uint32_t index;
	uint32_t locked;

	/*
		0 - not started
		1 - in progress
		2 - done
		3 - error
	*/
	uint32_t status;
	uint32_t src_addr;
	uint32_t dst_addr;
	uint32_t xfer_count;
	uint32_t width;
	uint32_t address_mask;
	uint32_t xor_key;
};

uint32_t history[0x100] = {0};
uint32_t history_idx;

// the current DMA structure we are using
static struct dma_buf *curr_dma = NULL;

// the alternate DMA structure that can get loaded separately
static struct dma_buf *alt_dma = NULL;

static pthread_t curr_thread;
static pthread_t alt_thread;

#define CTRL_DIRECTION (1 << 0)
#define CTRL_SENSE (1 << 1)
#define SRAM_BASE 0x29000
void memory_write(uint32_t addr, uint32_t value) {
	// actually write the memory to sram
	bus_write(SRAM_BASE + 8, addr);
	bus_write(SRAM_BASE + 0x100, value);
	bus_write(SRAM_BASE + 0, CTRL_SENSE);
	log("dma memory_write(0x%x, 0x%x)\n", addr, value);
}

uint32_t memory_read(uint32_t addr) {
	// actually read the memory from sram
	bus_write(SRAM_BASE + 8, addr);
	bus_write(SRAM_BASE + 0, CTRL_SENSE | CTRL_DIRECTION);

	uint32_t result = bus_read(SRAM_BASE + 0x100);
	log("dma memory_read(0x%x) -> 0x%x\n", addr, result);
	return result;
}

static volatile int thread_ready = 0;
void *dma_handler_thread(void *is_alt) {
#ifdef DEBUG
	char *thread_name = (is_alt == NULL) ? "MAIN" : "ALT";
#endif

	sigset_t x;
	sigemptyset (&x);
	sigaddset(&x, SIGRTMIN);
	sigaddset(&x, SIGRTMIN+1);
	pthread_sigmask(SIG_BLOCK, &x, NULL);
	thread_ready = 1;

	while(1) {

		volatile struct dma_buf *arg = (is_alt == NULL) ? curr_dma : alt_dma;

		if(arg == NULL) {
			usleep(100000);
			continue;
		}

		if (arg->status == 3) {
			usleep(100000);
			continue;
		}

		// if we have no status, we are not even loaded
		if (arg->status < 1) {
			usleep(100000);
			continue;
		}

		// wait to be signalled
		// BUG: we need to reload it here every time... otherwise we can use stale heap buffer
		while(arg->status < 2) {
			usleep(100000);
		}

		log("dma (%s): thread started\n", thread_name);

		// calculate our starting address
		uint32_t starting_address = arg->src_addr;
		if (arg->control & 1) {
			// inverted direction -- so add our length 
			starting_address += (arg->width * (arg->xfer_count - 1));
		}

		log("dma (%s): starting addr 0x%x mask: 0x%x width %d count 0x%x\n", thread_name, arg->src_addr, arg->address_mask, arg->width, arg->xfer_count);

		uint32_t dest_addr = arg->dst_addr;

		while (arg->xfer_count) {
			// this loop occurs over (at least) 2 ticks. we first read the value, then write it out

			// calculate our read address
			uint32_t read_addr = starting_address;
			if (arg->address_mask) {
				read_addr &= arg->address_mask;
			}

			// retrieve the value that we are supposed to read
			uint32_t val = memory_read(read_addr);
			log("dma (%s): read addr 0x%x -> 0x%x remaining count 0x%x\n", thread_name, read_addr, val, arg->xfer_count);

			if (arg->xor_key) {
				val ^= arg->xor_key;
			}

			// mask to desired write size
			uint64_t mask = (uint64_t)arg->width;
			mask = ((1uLL << (mask * 8uLL)) - 1uLL);
			val = (uint32_t)(mask & (uint64_t)val);

			// note that we have implicitly waited for >1 tick, due to the read.
			uint32_t write_addr = dest_addr;
			if (arg->address_mask) {
				write_addr &= arg->address_mask;
			}
			history[history_idx++] = dest_addr;
			history[history_idx++] = val;
			history_idx = history_idx & 0xff;
			memory_write(dest_addr, val);
			log("dma (%s): wrote out addr 0x%x <- 0x%x remaining count 0x%x\n", thread_name, write_addr, val, arg->xfer_count);

			// increment addresses
			if (arg->control & 1) {
				starting_address -= arg->width;
			} else {
				starting_address += arg->width;
			}
			dest_addr += arg->width;
			arg->xfer_count--;

			// debug state to see how many copies have been performed
			arg->index++;
		}

		log("dma (%s): completed transfer\n", thread_name);
		memset((void *)arg, 0, sizeof(struct dma_buf));
		arg->status = 3;
	}

	return NULL;
}

uint32_t mmio_handler(int is_read, uint32_t address, uint32_t data, int is_secure) {
	if (deadlock) return 0;

	address &= 0xffff;

	log("dma mmio 0x%x 0x%x %d\n", address, data, is_read);

	switch(address - REGISTER_BASE) {

	case 0: /* CTRL */
		if (is_read) {
			return 0; // RAZ
		} else {
			if (!curr_dma->locked)
				curr_dma->control = data;
		}
		break;
	case 4: /* STATUS */
		if (is_read) {
			return curr_dma->status;
		} else {
			log("dma set MAIN status to %d\n", data);
			curr_dma->status = data;
		}
		break;
	case 8: /* SRC_ADDR */
		if (is_read) {
			return curr_dma->src_addr;
		} else {
			if (!curr_dma->locked)
				curr_dma->src_addr = data;
		}
		break;
	case 0xc: /* DST_ADDR */
		if (is_read) {
			return curr_dma->dst_addr;
		} else {
			if (!curr_dma->locked)
				curr_dma->dst_addr = data;
		}
		break;
	case 0x10: /* ALT DMA STATUS */
		if (is_read) {
			return alt_dma->status;
		} else {
			log("dma set ALT status to %d\n", data);
			alt_dma->status = data;
		}
		break;
	case 0x14: /* XFER_COUNT */
		if (is_read) {
			return curr_dma->xfer_count;
		} else {
			if (!curr_dma->locked)
				curr_dma->xfer_count = data;
		}
		break;
	case 0x18: /* DEADLOCK */
		// writing here deadlocks forever ;)
		deadlock = 1;
		break;
	case 0x1c: /* TRIGGER */
		if (is_read) {
			return 0;
		} else {
			// spawn our DMA thread to actually do the copy
			int allowed = curr_dma ? (curr_dma->status < 2) : 1;
			allowed |= alt_dma ? (alt_dma->status < 2) : 1;
			if (allowed) {
				if (data) {
					curr_dma->status = 2;
				} else {
					alt_dma->status = 2;
				}
			} else {
				log("dma ignoring start due to not allowed\n");
			}
		}
		break;
	case 0x20: /* WIDTH */
		// 1, 2, 4, or 8 (!) byte writes
		if (is_read) {
			return curr_dma->width;
		} else {
			if (!curr_dma->locked)
				curr_dma->width = data;
		}
		break;
	case 0x24: /* ADDRESS MASK */
		if (is_read) {
			return curr_dma->address_mask;
		} else {
			if (!curr_dma->locked)
				curr_dma->address_mask = data;
		}
		break;
	case 0x28: /* FREEZE */
		// freezes config in place until current transfer is complete
		if (is_read) {
			// RAZ
			return 0;
		} else {
			curr_dma->locked = 1;
		}
		break;
	case 0x30: /* XOR */
		// xor key for data
		if (is_read) {
			return curr_dma->xor_key;
		} else {
			if (!curr_dma->locked)
				curr_dma->xor_key = data;
		}
		break;
	case 0x34: /* TRANSFER ID */
		// DMA engine will support 2 simultaneous transfers
		// NOTE: this should NOT be used by default... ONLY for pwn (and poller)

		// BUG: a thread could be actively using this when it is freed
		if (alt_dma) {
			free(alt_dma);
			alt_dma = NULL;
		}
		alt_dma = curr_dma;
		curr_dma = malloc(sizeof(*curr_dma));
		return 0;
	case 0x38: /* INDEX */
		// read only index that the DMA engine is currently using for a transfer
		// when not used, set to 0
		return curr_dma->index;
	case 0x40: /* CHECKPOINT */
		if (data == 0x13371337) {
			// this saves the entire DMA range to a checkpoint buffer which is then read out
			// the buffer is allocated via malloc and NOT freed on its own
			checkpoint_buf = calloc(1, sizeof(*curr_dma));
			memcpy(checkpoint_buf, curr_dma, sizeof(*curr_dma));
		}
		break;
	case 0x44: /* CHECKPOINT_CLR */
		// CLEARS the checkpoint buffer... _by calling free() w/o subsequent null
		free(checkpoint_buf);
		return 0;
	default:
		if (checkpoint_buf) {
			if (((address - REGISTER_BASE) >= 0x100) && (address - REGISTER_BASE) < 0x200) {
				uintptr_t offset = address - REGISTER_BASE - 0x100;
				return *(uint32_t *)&checkpoint_buf[offset];
			}
		}
		if (((address - REGISTER_BASE) >= 0x400) && (address - REGISTER_BASE) < 0x800) {
			uintptr_t offset = address - REGISTER_BASE - 0x400;
			offset >>= 2;
			return history[offset];
		}

		break;
	}

	return 0;
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

	// initialize our dma buffer
	curr_dma = calloc(1, sizeof(*curr_dma));
	curr_dma->width = 4; // default width

	pthread_create(&curr_thread, NULL, dma_handler_thread, NULL);
	while (thread_ready == 0) {
		usleep(5000);
	}
	thread_ready = 0;
	pthread_create(&alt_thread, NULL, dma_handler_thread, (void *)1);
	while (thread_ready == 0) {
		usleep(5000);
	}
	thread_ready = 0;

	bus_init(driver_pid, data_queue, id);
	lockdown_chip(driver_pid);

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
			uint32_t result = mmio_handler(incoming.is_read, incoming.address << 2, incoming.data, incoming.secure);

			// construct our ack
			incoming.data = result;
			incoming.address = incoming.srcid << 14;
			incoming.srcid = 0xf;

			submit_tx(incoming, NULL);
		}
	}

	log("goodbye\n");
	return 0;
}