#ifndef COMMON_H
#define COMMON_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <inttypes.h>


#define MAX_SONG_TITLE 128
#define MAX_SONG_DATA 1048576
#define MAX_DEVICES 3
#define MAX_SONGS 256
#define MAX_FILTERS 256
#define ROOM_WIDTH 20.0
#define ROOM_HEIGHT 20.0
#define AUDIO_WAVE_SAMPLES 1024

#define SUCCESS 0
#define FAIL 1

typedef int32_t sample_t;

// Biquad filter state structure
typedef enum {
    BIQUAD_LOWPASS = 0,
    BIQUAD_HIGHPASS,
    BIQUAD_BANDPASS,
    BIQUAD_NOTCH,
    BIQUAD_ALLPASS,
    BIQUAD_PEAKING,
    BIQUAD_LOWSHELF,
    BIQUAD_HIGHSHELF
} biquad_type_t;

typedef struct {
    double b0, b1, b2;  // Feedforward coefficients
    double a1, a2;      // Feedback coefficients (a0 is normalized to 1.0)
    double x1, x2;      // Input delay line
    double y1, y2;      // Output delay line
} biquad_t;

typedef struct {
    double x;
    double y;
} position_t;

typedef struct {
   uint32_t sample_count;
   sample_t samples[AUDIO_WAVE_SAMPLES];
   double peak_pa; // peak pressure amplitude in Pascals
   uint32_t frequency;
   uint16_t bits_per_sample;
   uint16_t channels;
   uint64_t timestamp;
} audio_wave_t;

typedef struct {
   uint16_t bits_per_second;   
   uint16_t channels;
   uint32_t frequency;
   uint64_t sample_count;
   sample_t* samples;
} song_audio_t;


typedef struct {
   uint32_t song_id;
   char title[MAX_SONG_TITLE];
   uint32_t duration_ms;
   song_audio_t audio; 
} song_t;

typedef enum {
    DEVICE_OFF = 0,
    DEVICE_ON,
    DEVICE_RECORDING,
    DEVICE_ERROR
} device_state_t;

typedef struct filter_list {
   biquad_type_t type;
   double frequency;
   double Q;
   double gain;
   biquad_t* biquad;     // Array of biquad states, one per channel
   uint16_t channels;    // Number of channels this filter is configured for
   struct filter_list* next;
} filter_list_t;

typedef struct device {
   uint32_t device_id;
   char name[64];
   device_state_t state;
   position_t position;
   double sensitivity;
   filter_list_t *filters;
   void (*process_audio)(struct device *self, const audio_wave_t *wave, uint32_t chunk_number, uint32_t total_chunks);
   // This function, if set, returns a SUCCESS if the song should be used or a FAIL if not
   int (*jukebooox_filter_song)(struct device *self, const song_t *song);
   int (*device_interact)(struct device *self);
   void *private_data;
} device_t;

typedef struct {
   song_t songs[MAX_SONGS];
   uint32_t song_count;
   device_t *devices[MAX_DEVICES];
   bool device_loaded[MAX_DEVICES];
   position_t jukebox_position;
   double speaker_sensitivity;
   double amp_wattage;
   double volume;
   bool is_playing;
   uint32_t current_song_id;
} jukebox_state_t;

typedef enum {
    CMD_LIST_SONGS = 1,
    CMD_PLAY_SONG,
    CMD_UPLOAD_SONG,
    CMD_LIST_DEVICES,
    CMD_TOGGLE_DEVICE,
    CMD_ADJUST_VOLUME,
    CMD_INTERACT_DEVICE,
    CMD_QUIT
} command_t;


// Function declarations
uint32_t calc_duration_ms(const song_audio_t* song);

void* convert_from_internal_to_wav_samples(const sample_t* samples, uint32_t sample_count, uint16_t current_bits_per_sample, uint16_t desired_bits_per_sample);

// Biquad filter functions
void biquad_lowpass(biquad_t* filter, double frequency, double sample_rate, double Q);
void biquad_highpass(biquad_t* filter, double frequency, double sample_rate, double Q);
void biquad_bandpass(biquad_t* filter, double frequency, double sample_rate, double Q);
void biquad_notch(biquad_t* filter, double frequency, double sample_rate, double Q);
void biquad_allpass(biquad_t* filter, double frequency, double sample_rate, double Q);
void biquad_peaking(biquad_t* filter, double frequency, double sample_rate, double Q, double gain);
void biquad_lowshelf(biquad_t* filter, double frequency, double sample_rate, double Q, double gain);
void biquad_highshelf(biquad_t* filter, double frequency, double sample_rate, double Q, double gain);
void biquad_init(biquad_t* filter, biquad_type_t type, double frequency, double sample_rate, double Q, double gain);
double biquad_process(biquad_t* filter, double input);
void biquad_reset(biquad_t* filter);

// Sample conversion functions
sample_t clip_sample(sample_t sample, uint16_t bps);
double sample_to_normalized_double(sample_t sample, uint16_t bits_per_sample);
sample_t normalized_double_to_sample(double normalized_sample, uint16_t bits_per_sample);

// helper functions
char* get_env_or_default(const char* env_var, const char* default_value);
int get_user_num(const char* prompt);
double random_double(double min, double max);
double round_to_decimals(double value, int decimals);

// Microphone processing functions
double microphone_apply_analog_gain(double sample, double gain);
double microphone_add_noise_floor(double sample, double noise_floor);
double microphone_apply_saturation(double sample, double threshold, double a1, double a2, double a3);

#endif
