#ifndef MACOS_PLAY_DEVICE_H
#define MACOS_PLAY_DEVICE_H

#ifdef DEBUG
#ifdef __APPLE__

#include "common.h"
#include <AudioToolbox/AudioQueue.h>

#define MACOS_PLAY_BUFFER_SIZE 4096
#define MACOS_PLAY_NUM_BUFFERS 3
#define MACOS_AUDIO_BUFFER_COUNT 128  // Ring buffer size

typedef struct {
    AudioQueueRef audio_queue;
    AudioStreamBasicDescription audio_format;
    AudioQueueBufferRef audio_buffers[MACOS_PLAY_NUM_BUFFERS];
    bool is_playing;
    bool is_initialized;
    bool audio_queue_created;  // Track if audio queue exists
    double volume;
    
    // Current audio format info
    uint32_t current_sample_rate;
    uint16_t current_bits_per_sample;
    uint16_t current_channels;
    
    // Thread-safe ring buffer for audio chunks
    audio_wave_t audio_ring_buffer[MACOS_AUDIO_BUFFER_COUNT];
    volatile uint32_t write_index;  // Where to write next chunk
    volatile uint32_t read_index;   // Where callback reads from
    volatile uint32_t available_chunks; // How many chunks ready
    
    // Audio playback state
    uint32_t current_chunk_position; // Position within current chunk
} macos_play_state_t;

device_t *macos_play_create(uint32_t device_id, position_t pos);
void macos_play_destroy(device_t *device);

void macos_play_process_audio(device_t *device, const audio_wave_t *wave, uint32_t chunk_number, uint32_t total_chunks);
void macos_play_set_volume(device_t *device, double volume);

#endif /* __APPLE__ */
#endif /* DEBUG */

#endif /* MACOS_PLAY_DEVICE_H */
