#ifndef PROOODIGI_H
#define PROOODIGI_H

#include "common.h"

#define TAPE_HEADER_SIZE 55
#define TAPE_DATA_SIZE 1048576

#define PROOODIGI_MIN_FREQUENCY 22000

#define PROOODIGI_MIN_BPM 60
#define PROOODIGI_MAX_BPM 180

typedef struct {
   uint8_t header[TAPE_HEADER_SIZE];
   uint8_t data[TAPE_DATA_SIZE];
} tape_t;

typedef struct {
   tape_t *tape;
   size_t tape_size;
   uint32_t frequency;
   uint16_t bits_per_sample;
   int16_t desired_key;
   bool has_recording;
} prooodigi_state_t;

device_t *prooodigi_create(uint32_t device_id, position_t pos);
void prooodigi_destroy(device_t *device);

#endif
