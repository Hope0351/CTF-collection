#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <signal.h>
#include <unistd.h>

#include "bus.h"
#include "game.h"


int main(int argc, char **argv) {

	setvbuf(stdin, NULL, _IONBF, 0);
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	int id = atoi(getenv("ID"));
	int driver_pid = atoi(getenv("D"));

	transaction_t *data_queue = NULL;

	// set queue depth
	arrsetcap(data_queue, 10);

	bus_init(driver_pid, data_queue, id);
	lockdown_chip(driver_pid);

	kill(driver_pid, SIGRTMIN+1);

	log("going into player loop\n");

	while(1) {

		// wait for tick
		while (!active_tick) {
			usleep(5000);
		}
		active_tick = 0;

		char input[0x20] = {0};
		uint32_t address = 0;
		uint32_t data = 0;
		printf("> ");
		fgets(input, sizeof(input), stdin);
		input[0x1f] = 0;
		input[strcspn(input, "\n")] = 0;

		log("player input was: '%s'\n", input);
		if (input[0] == 'r') {
			// issue bus read
			sscanf(&input[2], "0x%x", &address);
			log("going to read address 0x%x\n", address);
			printf("= OK 0x%x\n", bus_read(address));
		} else if (input[0] == 'w') {
			// issue bus write
			sscanf(&input[2], "0x%x 0x%x", &address, &data);
			bus_write(address, data);
			printf("= OK\n");
		} else if (input[0] == 'x') {
			break;
		}
	}

	log("goodbye\n");
	return 0;
}