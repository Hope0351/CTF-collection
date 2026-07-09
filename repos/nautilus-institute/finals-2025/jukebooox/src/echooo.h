#ifndef ECHOOO_H
#define ECHOOO_H

#include "common.h"

#define ECHOOO_BUFFER_SIZE 4096
#define ECHOOO_MAX_DELAY_MS 5000

typedef struct sample_list {
   int16_t* samples;
   uint32_t num_samples;
   struct sample_list* next;
} sample_list_t;

typedef struct {
   sample_list_t* head;
   sample_list_t* last;
   biquad_t lowpass_filter;
   biquad_t highpass_filter;
   bool filters_initialized;
} echooo_state_t;

device_t *echooo_create(uint32_t device_id, position_t pos);
void echooo_destroy(device_t *device);

void echooo_set_delay(device_t *device, uint32_t delay_ms);
void echooo_set_feedback(device_t *device, double gain);

#endif
