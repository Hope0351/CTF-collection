#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "wav.h"
#include "common.h"

// LibFuzzer target function
int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    // Don't fuzz with empty data or extremely small data
    if (size < 12) {
        return 0;
    }
    
    // Don't fuzz with excessively large data to avoid timeouts
    if (size > 1024 * 1024) {  // 1MB limit
        return 0;
    }
    
    // Call the target function
    song_audio_t *song = parse_wav(size, (void*)data);
    
    // Clean up if parsing succeeded
    if (song) {
        if (song->samples) {
            free(song->samples);
        }
        free(song);
    }
    
    return 0;
}
