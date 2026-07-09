#ifndef GAME_H
#define GAME_H

#include "stb_ds.h"

#ifdef DEBUG
#define log(x, ...) printf("[+] " x, ##__VA_ARGS__)
#else
#define log(x, ...)
#endif

#define MICROS_PER_SEC 1000000

#endif