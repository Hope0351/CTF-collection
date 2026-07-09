#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <signal.h>
#include <unistd.h>
#include <pthread.h>

#include "bus.h"
#include "game.h"
#include "aes.h"

#define REGISTER_BASE 0x9000

int deadlock = 0;

#define CTRL_DIRECTION (1 << 0)
#define CTRL_SENSE (1 << 1)
#define CTRL_AES_ENCRYPT (1 << 2)
#define CTRL_AES_PEEK_SENSE (1 << 3)
#define CTRL_MIRROR (1 << 4)
#define CTRL_SECURE (1 << 5)

struct __attribute__((packed)) sram_params {
	uint32_t address;
	uint32_t in_flight_data;
	uint32_t last_error;
};

struct __attribute__((packed)) sram_buf {
	uint8_t *buffer;
	/*
		bit 0 - direction (read or write)
		bit 1 - sense data
		bit 2 - aes encryption on/off
		bit 3 - aes peek sense
		bit 4 - aes mirror
		bit 5 - secure
	*/
	uint32_t control;

	/*
		0 - not started
		1 - in progress
		2 - done
		3 - error
	*/
	uint32_t status;
	uint32_t bank_size;
	uint32_t bank_count;
	uint32_t bank_sel;
	uint32_t last_error;
	uint32_t history_idx;
	uint32_t aes_key[4];
	uint32_t aes_base_addr;
	uint32_t aes_peek_addr;
	uint32_t sram_history[0x100];
	uint32_t secure_lock;
	uint32_t secure_base;
	uint32_t secure_len;
	uint32_t mirror_base;
	uint32_t mirror_length;
	uint32_t aes_length;
};

// the current DMA structure we are using
static struct sram_buf *curr_sram = NULL;
static struct sram_params sram_params[0x10] = {0};

void update_buffer() {
	log("sram: update_buffer %d * 0x%x = %x\n", curr_sram->bank_count, curr_sram->bank_size, curr_sram->bank_count * curr_sram->bank_size);
	free(curr_sram->buffer);
	curr_sram->buffer = calloc(curr_sram->bank_count, curr_sram->bank_size);
}

uint32_t read_from_address(uint32_t address, int should_decrypt) {
	// this function assumes a PHYSICAL address (which is just an offset into our sram_history)
	log("sram read_from_address(0x%x)\n", address);

	// the only relevant code here is AES. if we have AES enabled for this region, we decrypt before read
	if (curr_sram->control & CTRL_AES_ENCRYPT && should_decrypt) {
		if (address >= curr_sram->aes_base_addr) {
			if (address < (curr_sram->aes_base_addr + curr_sram->aes_length)) {
				/* we are encrypted. set up an AES context and decrypt this */
				struct AES_ctx ctx = {0};
				AES_init_ctx(&ctx, (const uint8_t *)curr_sram->aes_key);
				uint8_t buf[0x10] = {0};
				memcpy(buf, &curr_sram->buffer[address], 0x10);
				AES_ECB_decrypt(&ctx, buf);
				return *(uint32_t *)&buf[0];
			}
		}
	}

	/* we are not encrypted, so just return the data */
	return *(uint32_t *)&curr_sram->buffer[address];
}

void write_to_address(uint32_t address, uint32_t data) {
	// this function assumes a PHYSICAL address (which is just an offset into our sram_history)
	log("sram write_to_address(0x%x, 0x%x)\n", address, data);

	// the only relevant code here is AES. if we have AES enabled for this region, we decrypt before read
	if (curr_sram->control & CTRL_AES_ENCRYPT) {
		if (address >= curr_sram->aes_base_addr) {
			if (address < (curr_sram->aes_base_addr + curr_sram->aes_length)) {
				/* we are encrypted. set up an AES context and decrypt this */
				struct AES_ctx ctx = {0};
				AES_init_ctx(&ctx, (const uint8_t *)curr_sram->aes_key);
				uint8_t buf[0x10] = {0};
				memcpy(buf, &curr_sram->buffer[address], 0x10);
				AES_ECB_decrypt(&ctx, buf);
				*(uint32_t *)&buf[0] = data;
				AES_ECB_encrypt(&ctx, buf);
				memcpy(&curr_sram->buffer[address], buf, 0x10);
				return;
			}
		}
	}

	*(uint32_t *)&curr_sram->buffer[address] = data;
}

uint32_t convert_virt_to_phys(uint32_t address) {
	// our virtual addresses are formed such that the top byte is the bank #,
	// and the bytes under that are limited to be max 0x4000

	// upon error we return 0, mapping to (hopefully) a safe bank

	// handle secure by denying the read
	if (curr_sram->control & CTRL_SECURE) {
		if (address >= curr_sram->secure_base) {
			if (address < (curr_sram->secure_base + curr_sram->secure_len)) {
				curr_sram->last_error = 3;
				return 0;
			}
		}
	}

	/* BUG: this should be before secure */
	// handle mirroring by mapping it back to zero
	if (curr_sram->control & CTRL_MIRROR) {
		if (address >= curr_sram->mirror_base) {
			if (address < (curr_sram->mirror_base + curr_sram->mirror_length)) {
				log("sram mirror: converting 0x%x -> 0x%x\n", address, address - curr_sram->mirror_base);
				address -= curr_sram->mirror_base;
			}
		}
	}

	uint32_t bank = address >> 24;
	uint32_t offset = address & 0xffff;
	/* BUG: off by 1, this lets you read/write one bank offset's worth off the stack */
	if ((bank + curr_sram->bank_sel) > curr_sram->bank_count) {
		curr_sram->last_error = 1;
		return 0;
	}

	/* BUG: we don't check for unaligned here, so we can read/write up to 3 bytes off the end */
	if (offset > curr_sram->bank_size) {
		log("sram: offset 0x%x > banksize 0x%x\n", offset, curr_sram->bank_size);
		curr_sram->last_error = 2;
		return 0;
	}

	// add our bank offset
	bank = bank + curr_sram->bank_sel;

	// return the converted address
	return (bank * curr_sram->bank_size) + offset;
}

void update_sram_state(int srcid) {
	// this will process the sram state and make the relevant updates so it is consistent
	// this happens once per sense. sram does not rely on reaching out to any other services,
	// so we can be sure this function will not do any bus_read or bus_write calls

	// check if we are doing a read or a write
	log("update_sram_state: ctrl is 0x%x\n", curr_sram->control);
	if (curr_sram->control & CTRL_SENSE) {
		if (curr_sram->control & CTRL_DIRECTION) {
			// doing a READ
			sram_params[srcid].in_flight_data = read_from_address(convert_virt_to_phys(sram_params[srcid].address), 1);
			log("update_sram_state: doing a READ from 0x%x -> 0x%x\n", sram_params[srcid].address, sram_params[srcid].in_flight_data);
		} else {
			// doing a WRITE
			log("update_sram_state: doing a WRITE to 0x%x <- 0x%x\n", sram_params[srcid].address, sram_params[srcid].in_flight_data);
			write_to_address(convert_virt_to_phys(sram_params[srcid].address), sram_params[srcid].in_flight_data);
			sram_params[srcid].in_flight_data = 0;
		}
		curr_sram->control -= CTRL_SENSE;
	}

	if (curr_sram->control & CTRL_AES_PEEK_SENSE) {
		sram_params[srcid].in_flight_data = read_from_address(convert_virt_to_phys(sram_params[srcid].address), 0);
		curr_sram->control -= CTRL_AES_PEEK_SENSE;
	}

	if (curr_sram->last_error != 0) {
		sram_params[srcid].last_error = curr_sram->last_error;
		curr_sram->last_error = 0;
	}
}

uint32_t mmio_handler(int is_read, uint32_t address, uint32_t data, uint32_t srcid) {
	if (deadlock) return 0;

	address &= 0xffff;

	log("sram mmio_handler(%s, 0x%x, 0x%x, %d)\n", is_read ? "READ" : "WRITE", address, data, srcid);

	/* store address and data into history buffer */
	curr_sram->sram_history[curr_sram->history_idx++] = address - REGISTER_BASE;
	curr_sram->sram_history[curr_sram->history_idx++] = data;
	curr_sram->history_idx &= 0xff;

	switch(address - REGISTER_BASE) {
	case 0: /* CTRL */
		if (is_read) {
			return 0; // RAZ
		} else {
			// once these 3 are set, they cannot be unset
			uint32_t sticky = curr_sram->control & (CTRL_AES_ENCRYPT | CTRL_MIRROR | CTRL_SECURE);
			curr_sram->control = data | sticky;
		}
		update_sram_state(srcid);
		break;
	case 4: /* STATUS */
		return 0xffffffff;
	case 8: /* ADDRESS */
		if (is_read) {
			return sram_params[srcid].address;
		} else {
			sram_params[srcid].address = data;
		}
		break;
	case 0xc: /* BANK_SIZE */
		if (is_read) {
			return curr_sram->bank_size;
		} else {
			curr_sram->bank_size = data & 0x7fff;
			update_buffer();
		}
		break;
	case 0x10: /* BANK_COUNT */
		if (is_read) {
			return curr_sram->bank_count;
		} else {
			curr_sram->bank_count = data & 0x3f;
			update_buffer();
		}
		break;
	case 0x14: /* HISTORY_IDX */
		if (is_read) {
			return curr_sram->history_idx;
		} else {
			curr_sram->history_idx = 0;
		}
		break;
	case 0x18: /* DEADLOCK */
		// writing here deadlocks forever ;)
		deadlock = 1;
		break;
	case 0x1c: /* LAST_ERROR */
		if (is_read) {
			return sram_params[srcid].last_error;
		} else {
			// just clear last_error
			sram_params[srcid].last_error = 0;
		}
		break;
	case 0x20: /* SECURE_BASE */
		if (is_read) {
			return curr_sram->secure_base;
		} else {
			if (curr_sram->secure_lock == 0)
				curr_sram->secure_base = data;
		}
		break;
	case 0x24: /* SECURE_LENGTH */
		if (is_read) {
			return curr_sram->secure_len;
		} else {
			if (curr_sram->secure_lock == 0)
				curr_sram->secure_len = data;
		}
		break;
	case 0x28: /* SECURE_LOCK */
		if (is_read) {
			return curr_sram->secure_lock;
		} else {
			if (curr_sram->secure_lock == 0)
				curr_sram->secure_lock = data != 0;
		}
		break;
	case 0x2c: /* BANK_SEL */
		if (is_read) {
			return curr_sram->bank_sel;
		} else {
			curr_sram->bank_sel = data;
		}
		break;
	case 0x30: /* SRAM_MIRROR_BASE */
		if (is_read) {
			return curr_sram->mirror_base;
		} else {
			curr_sram->mirror_base = data;
		}
		break;
	case 0x34: /* SRAM_MIRROR_LENGTH */
		if (is_read) {
			return curr_sram->mirror_length;
		} else {
			curr_sram->mirror_length = data;
		}
		break;
	case 0x40: /* useless */
		if (is_read) {
			return 0;
		} else {
			curr_sram->aes_key[0] ^= data;
		}
		break;
	case 0x44: /* AES_ENCRYPT_BASE */
		if (is_read) {
			return curr_sram->aes_base_addr;
		} else {
			curr_sram->aes_base_addr = data;
		}
		break;
	case 0x48: /* AES_LENGTH */
		if (is_read) {
			return curr_sram->aes_length;
		} else {
			/* BUG: this should be checked to be 16-byte aligned */
			curr_sram->aes_length = data;
		}
		break;
	case 0x50: /* AES_KEY0 */
		if (is_read) {
			return 0;
		} else {
			curr_sram->aes_key[0] = data;
		}
	case 0x54: /* AES_KEY1 */
		if (is_read) {
			return 0;
		} else {
			curr_sram->aes_key[1] = data;
		}
	case 0x58: /* AES_KEY2 */
		if (is_read) {
			return 0;
		} else {
			curr_sram->aes_key[2] = data;
		}
		break;
	case 0x5c: /* AES_KEY3 */
		if (is_read) {
			return 0;
		} else {
			curr_sram->aes_key[3] = data;
		}
		break;
	case 0x60: /* AES_PEEK_ENCRYPTED_ADDR */
		if (is_read) {
			return curr_sram->aes_peek_addr;
		} else {
			curr_sram->aes_peek_addr = data;
		}
		break;
	case 0x100:
		if (is_read) {
			return sram_params[srcid].in_flight_data;
		} else {
			sram_params[srcid].in_flight_data = data;
		}
		break;
	default:
		if (address - REGISTER_BASE >= 0x1000) {
			if (address - REGISTER_BASE < 0x1000 + sizeof(curr_sram->sram_history)) {
				/* SRAM_LOG_HISTORY */
				uintptr_t offset = address - REGISTER_BASE - 0x1000;
				if (is_read) {
					return curr_sram->sram_history[offset >> 2];
				} else {
					/* BUG: should be uint32_t instead of uint64_t */
					*(uint64_t *)&curr_sram->sram_history[offset >> 2] = 0;
				}
			}
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

	bus_init(driver_pid, data_queue, id);
	lockdown_chip(driver_pid);

	// initialize our dma buffer
	curr_sram = calloc(1, sizeof(*curr_sram));

	// allocate our actual sram buffer
	curr_sram->bank_count = 0x10;
	curr_sram->bank_size = 0x4000;
	curr_sram->buffer = calloc(curr_sram->bank_count, curr_sram->bank_size);

	// make each bank unique to start
	for(int x = 0; x < curr_sram->bank_count; x++) {
		memset(&curr_sram->buffer[curr_sram->bank_size * x], x, curr_sram->bank_size);
	}

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
			uint32_t result = mmio_handler(incoming.is_read, incoming.address << 2, incoming.data, incoming.srcid);

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