#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>

#include "bus.h"
#include "game.h"

#define REGISTER_BASE 0x7000

int deadlock = 0;

uint32_t flag[0x40] = {0};

uint32_t verifier[0x40] = {0};

uint32_t verified = 0;

uint32_t mmio_handler(int is_read, uint32_t address, uint32_t data) {
	uint32_t offset = (address & 0xFFFF) - REGISTER_BASE;
	if (offset < 0x100) {
		return flag[offset >> 2];
	} else if ((offset >= 0x100) && (offset < 0x200)) {
		if (is_read) {
			return 0;
		} else {
			verifier[(offset - 0x100) >> 2] = data;
		}
	} else if (offset == 0x240) {
		if (is_read) {
			return verified;
		} else if (verified == 0) {
			verified = 1;
			for(int x = 0; x < 0x40; x += 4) {
				log("flag @ 0x%02x: %x %x %x %x\n", x, flag[x], flag[x+1], flag[x+2], flag[x+3]);
				log("verifier @ 0x%02x: %x %x %x %x\n", x, verifier[x], verifier[x+1], verifier[x+2], verifier[x+3]);
			}
			if (!memcmp(flag, verifier, 0x100)) {
				verified = 2;
			}
		}
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

#ifdef DEBUG
	strncpy((char *)flag, "flag{MY-FAKE-FLAG}", 0x100);
#else
	int fd = open("/flag", O_RDONLY);
	read(fd, flag, 0x100);
	close(fd);
#endif

	bus_init(driver_pid, data_queue, id);
	lockdown_chip(driver_pid);

	// indicate to the driver that we have loaded and are ready
	log("driver pid is %d\n", driver_pid);
	kill(driver_pid, SIGRTMIN+1);

#ifdef DEBUG
	// print out the flag as 32b values to make it easier to quickly validate test scripts
	for(int x = 0; x < 0x40; x += 4) {
		log("flag @ 0x%02x: %x %x %x %x\n", x, flag[x], flag[x+1], flag[x+2], flag[x+3]);
	}
#endif

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
	}

	log("goodbye\n");
	return 0;
}