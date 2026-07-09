#define _GNU_SOURCE 1
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <signal.h>
#include <errno.h>
#include <time.h>

#ifdef __linux__ 
#include <sys/prctl.h>
#endif

#include "game.h"
#include "bus.h"

int allowed_player_dst = -1;
int allowed_flag_src = -1;

#define DMA_PATH "./leonardo"
#define CACHE_PATH "./raphael"
#define FLAG_PATH "./donatello"
#define PLAYER_PATH "./splinter"
#define SRAM_PATH "./michelangelo"
#define CPU_PATH "./april"

#define PLAYER_ID 0xe

void spawn_chip(char * path, int id, uint32_t address) {

	char driverpid[12] = {0};
	snprintf(driverpid, sizeof(driverpid), "D=%d", getpid());
	char srcid[12] = {0};
	snprintf(srcid, sizeof(srcid), "ID=%d", id);
	char addr[12] = {0};
	snprintf(addr, sizeof(addr), "ADDR=%d", address);

	uint8_t rand_txid = arc4random_uniform(0x100);
	char txid[12] = {0};
	snprintf(txid, sizeof(txid), "T=%d", rand_txid);

	memset(&g_endpoints[id], 0, sizeof(endpoint_t));
	arrsetcap(g_endpoints[id].received_tx, 10);
	g_endpoints[id].txid = rand_txid;

	int forked_pid = fork();
	if (forked_pid) {
		// parent
		g_endpoints[id].pid = forked_pid;
		log("driver has spawned %s, pid %d\n", path, forked_pid);
		while (active_tick == 0) {
			usleep(1000);
		}
		active_tick = 0;
	} else {
		// child
		char *argv[] = {path, NULL};
		char *envp[] = {driverpid, srcid, addr, txid, NULL};
#ifdef __linux__ 
		prctl(PR_SET_PDEATHSIG, SIGTERM);
#endif
		exit(execve(path, argv, envp));
	}
}

/* copypasted from xorshift wikipedia, meant to be recognizable */
uint32_t xorshift32(uint32_t *input)
{
	uint32_t x = *input;
	x ^= x << 13;
	x ^= x >> 17;
	x ^= x << 5;
	return x;
}

void randomize_filter() {
	time_t game_time = time(NULL);
	char *tick_time = getenv("TICK_TIME");
	if (tick_time) {
		log("using tick time: %s\n", tick_time);
		// we have tick time, so use it
		game_time = atoi(tick_time);
	}

	// we want to mask the time to the nearest 5 minutes
	// this makes it the same for every tick
	game_time -= (game_time % (60 * 5));

	uint32_t input = game_time ^ 0x5455414e;
	for(int x = 0; x < 0x100; x++) {
		input = xorshift32(&input);
	}

	// generate allowed player dest
	allowed_player_dst = input & 0x3;

	// generate allowed flag src
	while(1) {
		int val = rand() & 0x3;
		if (val != allowed_player_dst) {
			allowed_flag_src = val;
			break;
		}
	}
	allowed_player_dst += 1;
	allowed_flag_src += 1;
	log("game time: %lu player dst: %d / flag src: %d\n", game_time, allowed_player_dst, allowed_flag_src);
#ifdef DEBUG
	allowed_player_dst = -1;
#endif
	printf("connected => %d\n", allowed_player_dst);
}

void setup() {

	setvbuf(stdin, NULL, _IONBF, 0);
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	setsid();

	randomize_filter();

	alarm(120);

	// set up bus handling. this will be the same for every process
	bus_init(0, NULL, 0);

	// spawn our helper chips for this configuration
	spawn_chip(DMA_PATH, 1, 0x10000);
	spawn_chip(SRAM_PATH, 2, 0x20000);
	spawn_chip(CACHE_PATH, 3, 0x30000);
	spawn_chip(CPU_PATH, 4, 0x40000);

	// spawn the special flag device
	spawn_chip(FLAG_PATH, 0xd, 0xd0000);

	// spawn the device that the player will actually interact with
	spawn_chip(PLAYER_PATH, PLAYER_ID, 0xe0000);
}

int should_filter(transaction_t candidate, int dstid) {
#ifdef DEBUG
	return 0;
#endif
	// if filter not set up, we allow no comms (fail closed)
	if (allowed_player_dst == -1) return 1;
	// if (allowed_flag_src == -1) return 1;

	// we filter in 2 cases

	// the first is if the player attempts to talk to a non-allowed device
	if (candidate.srcid == PLAYER_ID && dstid != allowed_player_dst)
		return 1;

	// // the second is if the flag device is reached from the player device
	// if (dstid == 0xd && candidate.srcid != allowed_flag_src)
	// 	return 1;

	// what's left is allowed. this includes:
	// - player to the specified allowed device per time
	// - flag from any non-player device

	return 0;
}

int ignition() {

	while(1) {

		g_tick++;

		// process the most recent bus transaction for each endpoint
		for(int x = 0; x < sizeof(g_endpoints)/sizeof(g_endpoints[0]); x++) {

			if (g_endpoints[x].pid <= 1) continue;

			// alert the endpoint to the new tick
			if (kill(g_endpoints[x].pid, SIGRTMIN+1)) {
				log("errno = %d\n", errno);
				exit(1);
			}

			transaction_t incoming = g_endpoints[x].incoming_tx;
			int dstid = (incoming.address >> 14) & 0xf;

			// srcid has to be sane
			if (incoming.srcid > sizeof(g_endpoints)/sizeof(g_endpoints[0])) {
				exit(1);
			}

			if (dstid > 0 && (incoming.srcid != 0xf)) {
				if (incoming.txid != g_endpoints[incoming.srcid].txid) {
					log("driver detected bad txid %x vs %x on for tx allegedly from %d\n", incoming.txid, g_endpoints[incoming.srcid].txid, incoming.srcid);
					exit(1);
				} else {
					log("saw valid txid %x vs %x\n", incoming.txid, g_endpoints[incoming.srcid].txid);
				}	
			}

			// is this addressed to the driver?
			if (dstid == 0xf) {
				// check if this is a nop or an ack
				if (incoming.srcid == 0) {
					// nop, nothing to do
				} else {
					if (g_endpoints[incoming.srcid].awaiting_send) {
						g_endpoints[dstid].awaiting_send = 0;
					}
				}
			} else if (dstid != incoming.srcid) {

				// send the transaction to whoever it is addressed to, if idle
				if (!g_endpoints[dstid].awaiting_send) {

					if (should_filter(incoming, dstid)) {
						log("filtering invalid transaction %x -> %x\n", incoming.srcid, dstid);
						// this is a transaction we should filter
						// it is either player -> disallowed or disallowed -> flag
						// generate a bogus ack and flush it
						transaction_t bogus_ack = incoming;
						bogus_ack.data = 0;
						bogus_ack.address = (incoming.srcid << 14);
						bogus_ack.srcid = 0xf;
						flush_tx(g_endpoints[incoming.srcid].pid, bogus_ack, NULL);
					} else {
						g_endpoints[dstid].outgoing_tx = incoming;
						memset(&g_endpoints[dstid].incoming_tx, 0, sizeof(transaction_t));
						log("endpoint %d setting awaiting send to 1\n", dstid);
						g_endpoints[dstid].awaiting_send = 1;
					}
				}
			}
		}

		// flush all outgoing transactions
		for(int x = 0; x < sizeof(g_endpoints)/sizeof(g_endpoints[0]); x++) {
			if (g_endpoints[x].awaiting_send) {
				g_endpoints[x].awaiting_send = 0;
				transaction_t outgoing = g_endpoints[x].outgoing_tx;
				memset(&g_endpoints[x].outgoing_tx, 0, sizeof(transaction_t));
				flush_tx(g_endpoints[x].pid, outgoing, NULL);
			}
		}

		// copy over all received ticks
		sigset_t x;
		sigemptyset (&x);
		sigaddset(&x, SIGRTMIN);
		sigprocmask(SIG_BLOCK, &x, NULL);
		for(int x = 0; x < sizeof(g_endpoints)/sizeof(g_endpoints[0]); x++) {
			if (arrlenu(g_endpoints[x].received_tx) > 0)
				g_endpoints[x].incoming_tx = arrpop(g_endpoints[x].received_tx);
		}
		sigprocmask(SIG_UNBLOCK, &x, NULL);

		// wait until the end of the tick
		usleep(10000);

		// rinse and repeat
	}
	return 0;
}

int main(int argc, char **argv) {
	if (argc > 1) {
		chdir(argv[1]);
	}
	setup();
	lockdown_driver();

	return ignition();
}