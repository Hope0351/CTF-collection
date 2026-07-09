#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <stdint.h>
#include <sys/prctl.h>
#include <linux/seccomp.h>

#include "bus.h"
#include "game.h"

#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"

_Atomic uint8_t rand_txid = 0;

_Atomic int g_tick = -1;
_Atomic int active_tick = 0;
uint8_t srcid_masking[0x10] = {0};

transaction_t *g_recvqueue = NULL;
transaction_t *g_ackqueue = NULL;

endpoint_t g_endpoints[0x10] = {0};

pid_t driver_pid = 0;

int self_id = 0xff;

uint8_t srcid_to_rand(uint8_t srcid) { 
	log("srcid_to_rand(%d) -> %d\n", srcid, srcid_masking[srcid]);
	return srcid_masking[srcid];
}

uint8_t rand_to_srcid(uint8_t rand) {
	uint8_t ret = 0;
	for(int x = 0; x < sizeof(srcid_masking)/sizeof(srcid_masking[0]); x++) {
		if (srcid_masking[x] == rand) {
			ret = x;
			break;
		}
	}
	log("rand_to_srcid(%d) -> %d\n", rand, ret);
	return ret;
}

static void bus_handler(int sig, siginfo_t *val, void *ucontext) {
	// retrieve value
	transaction_t tx = {0};
	memcpy(&tx, &val->si_value.sival_ptr, sizeof(tx));

	log("id %d%s rx: txid %x srcid %d%s secure %d address 0x%x data 0x%x\n",
		self_id, driver_pid ? "" : " (DRIVER)", tx.txid, tx.srcid,
		tx.srcid == 0xf ? " (ACK)" : "", tx.secure, (tx.address << 2), tx.data
	);

	if (driver_pid == 0) {
		// we are the driver -- assign this transaction to the appropriate enpdoint
		int dstid = (tx.address >> 14) & 0xf;

		if (tx.srcid == 0xf && (tx.address & 0x3fff) == 0) {
			// this is an ack and can be sent from anyone, in theory

			// unrandomize the dstid, which was based on our original srcid
			dstid = rand_to_srcid(dstid);
			tx.address = (dstid << 14);
		} else if (val->si_pid != g_endpoints[tx.srcid].pid) {
			log("driver received signal from bogus pid %d, expected %d for srcdid %d. bye\n", val->si_pid, g_endpoints[tx.srcid].pid, tx.srcid);
			exit(1);
		}

		arrins(g_endpoints[dstid].received_tx, 0, tx);
	} else {

		if (driver_pid != val->si_pid) {
			log("child received signal from non-driver. bye\n");
			exit(1);
		}

		// check if this is an ack
		if (tx.srcid == 0xf) {
			arrins(g_ackqueue, 0, tx);
		} else {
			arrins(g_recvqueue, 0, tx);
		}
	}
}

// SIGRTMIN+1
static void tick_handler(int sig, siginfo_t *val, void *ucontext) {
	if (driver_pid) {
		// SIGRTMIN+1 indicates a new tick has begun
		g_tick += 1;
	}

	active_tick = 1;
}


int flush_tx(pid_t target, transaction_t tx, transaction_t *reply_tx) {
	union sigval sv = {0};

	// we are flushing a tx, as driver -- randomize the srcid
	if (driver_pid == 0) {
		if (tx.srcid != 0xf) {
			tx.srcid = srcid_to_rand(tx.srcid);
		}
	}

	memcpy(&sv.sival_ptr, &tx, sizeof(tx));

	log("id %d%s tx txid %x srcid %d%s secure %d address 0x%x data 0x%x\n",
		self_id, driver_pid ? "" : " (DRIVER)", tx.txid, tx.srcid,
		tx.srcid == 0xf ? " (ACK)" : "", tx.secure, (tx.address << 2), tx.data
	);

	int ret = sigqueue(target, SIGRTMIN, sv);
	log("sigqueue(%d, SIGRTMIN, %p) returns %d\n", target, sv.sival_ptr, ret);
	if (ret) {
		// if this fails we probably have no reason to continue at all
		exit(1);
	}

	if (reply_tx == NULL) {
		// do not wait for ACK. used by driver
		return ret;
	}

	memset(reply_tx, 0, sizeof(transaction_t));

	// wait up to 1s for a reply
	ret = ETIMEDOUT;
	int total_wait_time = 1 * MICROS_PER_SEC;
	int curr_wait_time = 0;
	while(curr_wait_time < total_wait_time) {
		// bus is only 1 wide, we must receive an ack before our next message
		if (arrlenu(g_ackqueue) > 0) {
			if (g_ackqueue[0].txid == tx.txid) {
				log("child %d received ack for txid %x\n", self_id, tx.txid);
				// we just received an ack

				*reply_tx = g_ackqueue[0];
				arrdel(g_ackqueue, 0);
				ret = 0;
				break;
			}
		}
		usleep(10000);
		curr_wait_time += 10000;
	}
	return ret;
}

int submit_tx(transaction_t tx, transaction_t *reply_tx) {
	// no-op if no driver pid set
	if (driver_pid) {
		return flush_tx(driver_pid, tx, reply_tx);
	}
	return EINVAL;
}

uint32_t bus_read(uint32_t addr) {
	transaction_t tx = {0};
	tx.txid = rand_txid;
	tx.srcid = self_id;
	tx.secure = 0;
	tx.is_read = 1;
	tx.address = (addr & 0xffffc) >> 2;
	tx.data = 0;

	log("id %d issuing bus_read(0x%x)\n", self_id, addr);

	transaction_t reply = {0};
	if (submit_tx(tx, &reply)) {
		log("ERROR! id %d issuing bus_read(0x%x), timed out\n", self_id, addr);
	}
	return reply.data;
}

int bus_write(uint32_t addr, uint32_t value) {
	transaction_t tx = {0};
	tx.txid = rand_txid;
	tx.srcid = self_id; // TODO: do I set this? or do I just want the driver to assign this?
	tx.secure = 0;
	tx.is_read = 0;
	tx.address = (addr & 0xffffc) >> 2;
	tx.data = value;

	log("id %d issuing bus_write(0x%x, 0x%x)\n", self_id, addr, value);

	transaction_t reply = {0};

	return submit_tx(tx, &reply);
}

void lockdown_chip(int driver_pid) {
#if defined(__x86_64__)
	static unsigned char filter[] = {32,0,0,0,4,0,0,0,21,0,0,25,62,0,0,192,32,0,0,0,0,0,0,0,53,0,23,0,0,0,0,64,21,0,23,0,1,0,0,0,21,0,22,0,0,0,0,0,21,0,21,0,60,0,0,0,21,0,20,0,231,0,0,0,21,0,19,0,102,0,0,0,21,0,18,0,39,0,0,0,21,0,17,0,13,0,0,0,21,0,16,0,15,0,0,0,21,0,15,0,12,0,0,0,21,0,14,0,9,0,0,0,21,0,13,0,11,0,0,0,21,0,12,0,25,0,0,0,21,0,11,0,219,0,0,0,21,0,10,0,230,0,0,0,21,0,2,0,129,0,0,0,21,0,1,0,62,0,0,0,6,0,0,0,0,0,0,0,32,0,0,0,16,0,0,0,21,0,0,4,55,19,55,19,32,0,0,0,24,0,0,0,21,0,3,0,34,0,0,0,21,0,2,0,35,0,0,0,6,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,6,0,0,0,0,0,255,127};
#else
	static unsigned char filter[] = {32,0,0,0,4,0,0,0,21,0,0,25,183,0,0,192,32,0,0,0,0,0,0,0,53,0,23,0,0,0,0,64,21,0,23,0,64,0,0,0,21,0,22,0,63,0,0,0,21,0,21,0,93,0,0,0,21,0,20,0,94,0,0,0,21,0,19,0,174,0,0,0,21,0,18,0,172,0,0,0,21,0,17,0,134,0,0,0,21,0,16,0,139,0,0,0,21,0,15,0,214,0,0,0,21,0,14,0,222,0,0,0,21,0,13,0,215,0,0,0,21,0,12,0,216,0,0,0,21,0,11,0,128,0,0,0,21,0,10,0,115,0,0,0,21,0,2,0,138,0,0,0,21,0,1,0,129,0,0,0,6,0,0,0,0,0,0,0,32,0,0,0,16,0,0,0,21,0,0,4,55,19,55,19,32,0,0,0,24,0,0,0,21,0,3,0,34,0,0,0,21,0,2,0,35,0,0,0,6,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,6,0,0,0,0,0,255,127};
#endif
	struct prog {
		unsigned short len;
		unsigned char *filter;
	} rule = {
		.len = sizeof(filter) >> 3,
		.filter = filter
	};
	// insert our target pid
	memcpy(memmem(filter, sizeof(filter), "\x37\x13\x37\x13", 4), &driver_pid, 4);
	if(prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0) < 0) { perror("prctl(PR_SET_NO_NEW_PRIVS)"); exit(2); }
	if(prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &rule) < 0) { perror("prctl(PR_SET_SECCOMP)"); exit(2); }
}

void lockdown_driver() {
#if defined(__x86_64__)
	static unsigned char filter[] = {32,0,0,0,4,0,0,0,21,0,0,22,62,0,0,192,32,0,0,0,0,0,0,0,53,0,20,0,0,0,0,64,21,0,20,0,1,0,0,0,21,0,19,0,0,0,0,0,21,0,18,0,60,0,0,0,21,0,17,0,231,0,0,0,21,0,16,0,102,0,0,0,21,0,15,0,39,0,0,0,21,0,14,0,13,0,0,0,21,0,13,0,15,0,0,0,21,0,12,0,14,0,0,0,21,0,11,0,12,0,0,0,21,0,10,0,9,0,0,0,21,0,9,0,219,0,0,0,21,0,8,0,230,0,0,0,21,0,2,0,129,0,0,0,21,0,1,0,62,0,0,0,6,0,0,0,0,0,0,0,32,0,0,0,24,0,0,0,21,0,3,0,34,0,0,0,21,0,2,0,35,0,0,0,6,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,6,0,0,0,0,0,255,127};
#else
	static unsigned char filter[] = {32,0,0,0,4,0,0,0,21,0,0,22,183,0,0,192,32,0,0,0,0,0,0,0,53,0,20,0,0,0,0,64,21,0,20,0,64,0,0,0,21,0,19,0,63,0,0,0,21,0,18,0,93,0,0,0,21,0,17,0,94,0,0,0,21,0,16,0,174,0,0,0,21,0,15,0,172,0,0,0,21,0,14,0,134,0,0,0,21,0,13,0,139,0,0,0,21,0,12,0,135,0,0,0,21,0,11,0,214,0,0,0,21,0,10,0,222,0,0,0,21,0,9,0,128,0,0,0,21,0,8,0,115,0,0,0,21,0,2,0,138,0,0,0,21,0,1,0,129,0,0,0,6,0,0,0,0,0,0,0,32,0,0,0,24,0,0,0,21,0,3,0,34,0,0,0,21,0,2,0,35,0,0,0,6,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,6,0,0,0,0,0,255,127};
#endif
	struct prog {
		unsigned short len;
		unsigned char *filter;
	} rule = {
		.len = sizeof(filter) >> 3,
		.filter = filter
	};
	if(prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0) < 0) { perror("prctl(PR_SET_NO_NEW_PRIVS)"); exit(2); }
	if(prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &rule) < 0) { perror("prctl(PR_SET_SECCOMP)"); exit(2); }
}

int bus_init(int target_driver_pid, transaction_t *queue, int id) {

	log("pid %d doing bus init, is driver: %s\n", getpid(), target_driver_pid == 0 ? "YES" : "NO");

	if (queue)
		g_recvqueue = queue;

	// set up signal handler for a normal bus transaction
	struct sigaction sa;
	sigemptyset(&sa.sa_mask);
	sa.sa_sigaction = bus_handler;
	sa.sa_flags = SA_SIGINFO | SA_RESTART;
	sigaction(SIGRTMIN, &sa, NULL);

	sigemptyset(&sa.sa_mask);
	sa.sa_sigaction = tick_handler;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGRTMIN+1, &sa, NULL);

	if (target_driver_pid) {
		driver_pid = target_driver_pid;
		self_id = id;

		rand_txid = atoi(getenv("T"));
		log("id %d using rand_txid of %x\n", id, rand_txid);
	} else {
		uint8_t rotates[] = {1, 2, 3, 4, 0xd, 0xe};
		for(int idx = 0; idx < sizeof(rotates)/sizeof(rotates[0]); idx++) {
			int x = rotates[idx];
			log("%d becomes %d\n", rotates[idx], x);
			int found = 1;
			while(found) {
				srcid_masking[x] = arc4random_uniform(10) + 1;
				found = 0;
				for(int y = 0; y < x; y++) {
					if (srcid_masking[x] == srcid_masking[y]) {
						found = 1;
						break;
					}
				}
			}
		}
	}

	return 0;
}