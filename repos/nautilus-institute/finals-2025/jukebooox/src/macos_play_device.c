#ifdef DEBUG
#ifdef __APPLE__

#include "macos_play_device.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Forward declarations
static void macos_play_audio_callback(void *user_data, AudioQueueRef queue, AudioQueueBufferRef buffer);
static bool macos_play_setup_audio_queue(macos_play_state_t *state, uint32_t sample_rate, uint16_t bits_per_sample, uint16_t channels);
static void macos_play_teardown_audio_queue(macos_play_state_t *state);

static bool macos_play_setup_audio_queue(macos_play_state_t *state, uint32_t sample_rate, uint16_t bits_per_sample, uint16_t channels) {
    printf("[macOS Audio] Setting up audio queue: %dHz, %d-bit, %d channels\n", 
           sample_rate, bits_per_sample, channels);
    
    // Configure audio format
    state->audio_format.mSampleRate = sample_rate;
    state->audio_format.mFormatID = kAudioFormatLinearPCM;
    state->audio_format.mChannelsPerFrame = channels;
    state->audio_format.mBitsPerChannel = bits_per_sample;
    state->audio_format.mBytesPerFrame = (bits_per_sample / 8) * channels;
    state->audio_format.mBytesPerPacket = state->audio_format.mBytesPerFrame;
    state->audio_format.mFramesPerPacket = 1;
    
    // Set format flags based on bit depth
    if (bits_per_sample == 8) {
        state->audio_format.mFormatFlags = kLinearPCMFormatFlagIsPacked; // 8-bit is unsigned
    } else {
        state->audio_format.mFormatFlags = kLinearPCMFormatFlagIsSignedInteger | kLinearPCMFormatFlagIsPacked;
    }
    
    // Create audio queue
    OSStatus result = AudioQueueNewOutput(
        &state->audio_format,
        macos_play_audio_callback,
        state,
        NULL,
        NULL,
        0,
        &state->audio_queue
    );
    
    if (result != noErr) {
        printf("[macOS Audio] Failed to create audio queue: %d\n", (int)result);
        return false;
    }
    
    // Allocate and enqueue buffers
    for (int i = 0; i < MACOS_PLAY_NUM_BUFFERS; i++) {
        result = AudioQueueAllocateBuffer(
            state->audio_queue,
            MACOS_PLAY_BUFFER_SIZE * state->audio_format.mBytesPerFrame,
            &state->audio_buffers[i]
        );
        
        if (result != noErr) {
            printf("[macOS Audio] Failed to allocate audio buffer %d: %d\n", i, (int)result);
            AudioQueueDispose(state->audio_queue, true);
            return false;
        }
        
        // Initialize buffer with silence
        memset(state->audio_buffers[i]->mAudioData, 0, state->audio_buffers[i]->mAudioDataBytesCapacity);
        state->audio_buffers[i]->mAudioDataByteSize = state->audio_buffers[i]->mAudioDataBytesCapacity;
        
        AudioQueueEnqueueBuffer(state->audio_queue, state->audio_buffers[i], 0, NULL);
    }
    
    state->audio_queue_created = true;
    state->current_sample_rate = sample_rate;
    state->current_bits_per_sample = bits_per_sample;
    state->current_channels = channels;
    
    printf("[macOS Audio] Audio queue created successfully\n");
    return true;
}

static void macos_play_teardown_audio_queue(macos_play_state_t *state) {
    if (!state->audio_queue_created) {
        return;
    }
    
    printf("[macOS Audio] Tearing down audio queue\n");
    
    if (state->is_playing) {
        AudioQueueStop(state->audio_queue, true);
        state->is_playing = false;
    }
    
    AudioQueueDispose(state->audio_queue, true);
    state->audio_queue_created = false;
    state->current_sample_rate = 0;
    state->current_bits_per_sample = 0;
    state->current_channels = 0;
}

static void macos_play_audio_callback(void *user_data, AudioQueueRef queue, AudioQueueBufferRef buffer) {
    macos_play_state_t *state = (macos_play_state_t *)user_data;
    
    printf("[macOS Audio] Callback called, playing=%s, chunks=%d\n", 
           state->is_playing ? "true" : "false",
           state->available_chunks);
    
    if (!state->is_playing) {
        // Fill with silence when not playing
        memset(buffer->mAudioData, 0, buffer->mAudioDataBytesCapacity);
        buffer->mAudioDataByteSize = buffer->mAudioDataBytesCapacity;
        AudioQueueEnqueueBuffer(queue, buffer, 0, NULL);
        return;
    }
    
    // Calculate number of frames to fill
    uint32_t frames_to_fill = buffer->mAudioDataBytesCapacity / state->audio_format.mBytesPerFrame;    
    
    printf("[macOS Audio] Filling %d frames, volume=%.2f, %d channels, chunks available=%d\n", 
           frames_to_fill, state->volume, state->audio_format.mChannelsPerFrame, state->available_chunks);

    uint16_t bps = state->current_bits_per_sample;    
    // Generate audio samples from ring buffer
    for (uint32_t frame = 0; frame < frames_to_fill; frame++) {
        uint16_t channels = state->audio_format.mChannelsPerFrame;
        
        // Fill each channel with its corresponding sample from interleaved data
        for (uint16_t ch = 0; ch < channels; ch++) {
            uint64_t sample = 0;
            
            // Check if we have audio chunks available
            if (state->available_chunks > 0) {
                uint32_t read_idx = state->read_index;
                audio_wave_t *current_chunk = &state->audio_ring_buffer[read_idx];
                
                // Read sample from current chunk (samples are interleaved by channel)
                if (state->current_chunk_position < current_chunk->sample_count) {
                    // Convert from sample_t (int32_t) to output format based on bits per sample
                    sample_t raw_sample = current_chunk->samples[state->current_chunk_position];
                    
                    if (bps == 8) {
                       sample = (char)raw_sample;
                    } else if (bps == 16) {
                       sample = (int16_t)raw_sample; 
                    } else if (bps == 32) {
                       sample = (int32_t)raw_sample;
                    }
                    state->current_chunk_position++;
                } else {
                    // Finished current chunk, move to next
                    printf("[macOS Audio] Finished chunk %d, moving to next\n", read_idx);
                    state->current_chunk_position = 0;
                    state->read_index = (read_idx + 1) % MACOS_AUDIO_BUFFER_COUNT;
                    __sync_fetch_and_sub(&state->available_chunks, 1); // Atomic decrement
                    
                    // Try to get sample from new chunk
                    if (state->available_chunks > 0) {
                        current_chunk = &state->audio_ring_buffer[state->read_index];
                        if (current_chunk->sample_count > 0) {
                            sample_t raw_sample = current_chunk->samples[0];
                            if (bps == 8) {
                               sample = (char)raw_sample;
                            } else if (bps == 16) {
                               sample = (int16_t)raw_sample; 
                            } else if (bps == 32) {
                               sample = (int32_t)raw_sample;
                            }
                            state->current_chunk_position = 1;
                        }
                    }
                }
            }
            // If no data available, sample remains 0 (silence)
            
            // Output sample to the correct channel
            if (bps == 8) {
                char *output = (char *)buffer->mAudioData;
                output[(frame * channels) + ch] = (char)sample;
            } else if (bps == 16) {
                int16_t *output = (int16_t *)buffer->mAudioData;
                output[(frame * channels) + ch] = (int16_t)sample;
            } else if (bps == 32) {
                int32_t *output = (int32_t *)buffer->mAudioData;
                output[(frame * channels) + ch] = (int32_t)sample;
            }
        }
    }
    
    buffer->mAudioDataByteSize = frames_to_fill * state->audio_format.mBytesPerFrame;
    
    // Stop if no more chunks available
    if (state->available_chunks == 0) {
        printf("[macOS Audio] No more audio chunks, stopping playback\n");
        state->is_playing = false;
    }
    AudioQueueEnqueueBuffer(queue, buffer, 0, NULL);
}

device_t *macos_play_create(uint32_t device_id, position_t pos) {
    device_t *device = calloc(1, sizeof(device_t));
    if (!device) {
        return NULL;
    }
    
    macos_play_state_t *state = calloc(1, sizeof(macos_play_state_t));
    if (!state) {
        free(device);
        return NULL;
    }
    
    // Initialize device structure
    device->device_id = device_id;
    strncpy(device->name, "macOS Debug Player", sizeof(device->name) - 1);
    device->state = DEVICE_OFF;
    device->position = pos;
    device->sensitivity = 1.0;
    device->process_audio = macos_play_process_audio;
    device->private_data = state;
    
    // Audio queue will be created dynamically when we know the format
    
    // Initialize audio device state
    state->is_initialized = true;
    state->is_playing = false;
    state->audio_queue_created = false;
    state->volume = 1.0;
    
    // Initialize audio format tracking (will be set when first audio arrives)
    state->current_sample_rate = 0;
    state->current_bits_per_sample = 0;
    state->current_channels = 0;
    
    // Initialize ring buffer
    state->write_index = 0;
    state->read_index = 0;
    state->available_chunks = 0;
    state->current_chunk_position = 0;
    
    // Clear ring buffer
    memset(state->audio_ring_buffer, 0, sizeof(state->audio_ring_buffer));
    
    device->state = DEVICE_OFF;
    
    printf("[macOS Audio] Debug audio device created successfully (format will be set dynamically)\n");
    printf("[macOS Audio] Device position: (%.1f, %.1f)\n", pos.x, pos.y);
    return device;
}

void macos_play_destroy(device_t *device) {
    if (!device || !device->private_data) {
        return;
    }
    
    macos_play_state_t *state = (macos_play_state_t *)device->private_data;
    
    if (state->audio_queue_created) {
        macos_play_teardown_audio_queue(state);
    }
    
    free(state);
    free(device);
    printf("[macOS Audio] Debug audio device destroyed\n");
}

void macos_play_process_audio(device_t *device, const audio_wave_t *wave, uint32_t chunk_number, uint32_t total_chunks) {
    if (!device || !device->private_data || !wave) {
        printf("[macOS Audio] process_audio called with NULL parameters\n");
        return;
    }
    
    macos_play_state_t *state = (macos_play_state_t *)device->private_data;
    
    if (!state->is_initialized) {
        printf("[macOS Audio] Device not initialized\n");
        return;
    }
    
    if (device->state == DEVICE_OFF) {
        printf("[macOS Audio] Device is OFF, ignoring audio\n");
        return;
    }
    
    printf("[macOS Audio] Processing audio wave: samples=%d, amplitude=%.2f, %dHz, %d-bit, %d channels (chunk %u/%u)\n", 
           wave->sample_count, wave->amplitude, wave->frequency, wave->bits_per_sample, wave->channels, chunk_number, total_chunks);
    
    // Use wave amplitude directly (no distance calculation)
    state->volume = wave->amplitude;
    
    // Check if we need to create or recreate audio queue based on format
    bool format_changed = false;
    if (!state->audio_queue_created) {
        // First time - create audio queue
        printf("[macOS Audio] Creating audio queue for first time\n");
        if (!macos_play_setup_audio_queue(state, wave->frequency, wave->bits_per_sample, wave->channels)) {
            printf("[macOS Audio] Failed to setup audio queue\n");
            device->state = DEVICE_ERROR;
            return;
        }
    } else {
        // Check if format changed
        if (state->current_sample_rate != wave->frequency ||
            state->current_bits_per_sample != wave->bits_per_sample ||
            state->current_channels != wave->channels) {
            
            printf("[macOS Audio] Audio format changed - recreating audio queue\n");
            printf("[macOS Audio] Old: %dHz, %d-bit, %d channels\n", 
                   state->current_sample_rate, state->current_bits_per_sample, state->current_channels);
            printf("[macOS Audio] New: %dHz, %d-bit, %d channels\n", 
                   wave->frequency, wave->bits_per_sample, wave->channels);
            
            macos_play_teardown_audio_queue(state);
            if (!macos_play_setup_audio_queue(state, wave->frequency, wave->bits_per_sample, wave->channels)) {
                printf("[macOS Audio] Failed to recreate audio queue\n");
                device->state = DEVICE_ERROR;
                return;
            }
            format_changed = true;
        }
    }
    
    // Clear ring buffer if format changed
    if (format_changed) {
        printf("[macOS Audio] Clearing ring buffer due to format change\n");
        state->write_index = 0;
        state->read_index = 0;
        state->available_chunks = 0;
        state->current_chunk_position = 0;
        memset(state->audio_ring_buffer, 0, sizeof(state->audio_ring_buffer));
    }
    
    // Check if ring buffer has space
    if (state->available_chunks >= MACOS_AUDIO_BUFFER_COUNT) {
        printf("[macOS Audio] Ring buffer full (%d chunks), dropping audio chunk\n", 
               state->available_chunks);
        return; // Drop chunk if buffer full
    }
    
    // Write to next available slot in ring buffer
    uint32_t write_idx = state->write_index;
    printf("[macOS Audio] Writing chunk to buffer slot %d\n", write_idx);
    memcpy(&state->audio_ring_buffer[write_idx], wave, sizeof(audio_wave_t));
    
    // Atomically update indices
    state->write_index = (write_idx + 1) % MACOS_AUDIO_BUFFER_COUNT;
    __sync_fetch_and_add(&state->available_chunks, 1); // Atomic increment
    
    printf("[macOS Audio] Ring buffer now has %d chunks available\n", state->available_chunks);
    
    // Start playback if not already playing and we have data
    if (!state->is_playing && state->available_chunks > 0) {
        printf("[macOS Audio] Starting audio queue with %d chunks...\n", state->available_chunks);
        state->current_chunk_position = 0;
        
        OSStatus result = AudioQueueStart(state->audio_queue, NULL);
        if (result == noErr) {
            state->is_playing = true;
            device->state = DEVICE_ON;
            printf("[macOS Audio] ✅ Audio playback started! Volume=%.2f\n", state->volume);
            printf("[macOS Audio] Ring buffer playback initialized with %d chunks\n", state->available_chunks);
        } else {
            printf("[macOS Audio] ❌ Failed to start audio queue: %d\n", (int)result);
            device->state = DEVICE_ERROR;
        }
    } else if (state->is_playing) {
        printf("[macOS Audio] Audio already playing, added chunk to ring buffer\n");
    }
}

void macos_play_set_volume(device_t *device, double volume) {
    if (!device || !device->private_data) {
        return;
    }
    
    macos_play_state_t *state = (macos_play_state_t *)device->private_data;
    
    if (volume < 0.0) volume = 0.0;
    if (volume > 1.0) volume = 1.0;
    
    state->volume = volume;
    printf("macOS debug device volume set to %.2f\n", volume);
}

#endif /* __APPLE__ */
#endif /* DEBUG */
