#ifndef BUS_H
#define BUS_H

/*
	every program, including driver, has the same bus handling code
	the only difference is based on pid
*/

struct __attribute__((packed)) transaction {
	uint64_t txid : 8;
	uint64_t secure : 1;
	uint64_t data : 32;
	uint64_t srcid : 4;
	uint64_t address : 18;
	uint64_t is_read : 1;
};
typedef struct transaction transaction_t;

struct endpoint {
	int pid;
	int awaiting_send;
	uint8_t txid;
	transaction_t incoming_tx;
	transaction_t outgoing_tx;
	transaction_t *received_tx;
};

typedef struct endpoint endpoint_t;

extern _Atomic int g_tick;
extern _Atomic int active_tick;
extern _Atomic uint8_t rand_txid;
extern pid_t driver_pid;

extern endpoint_t g_endpoints[0x10];

int bus_init(int is_driver, transaction_t *queue, int id);
uint32_t bus_read(uint32_t addr);
int bus_write(uint32_t addr, uint32_t value);
int flush_tx(pid_t target, transaction_t tx, transaction_t *reply_tx);
int submit_tx(transaction_t tx, transaction_t *reply_tx);
void lockdown_chip(int driver_pid);
void lockdown_driver();

#endif