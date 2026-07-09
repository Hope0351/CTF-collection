#ifndef WAV_H
#define WAV_H

#include "common.h"

#define RIFF_TAG    0x46464952  // "RIFF" (0x52, 0x49, 0x46, 0x46)
#define FORMAT_TAG  0x20746D66  // "fmt " (0x66, 0x6D, 0x74, 0x20)
#define WAV_TAG     0x45564157  // "WAVE" (0x57, 0x41, 0x56, 0x45)
#define DATA_TAG    0x61746164  // "data" (0x64, 0x61, 0x74, 0x61)

#define PCM_FORMAT 1

// We are assuming that we're on a little endian machine so we don't have a worry about moving bits around 
#if defined(__BYTE_ORDER__) && __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__
#  error "This code is intended only for a little-endian system."
#endif

/*
  [Master RIFF chunk]
   FileTypeBlocID  (4 bytes) : Identifier « RIFF »  (0x52, 0x49, 0x46, 0x46)
   FileSize        (4 bytes) : Overall file size minus 8 bytes
   FileFormatID    (4 bytes) : Format = « WAVE »  (0x57, 0x41, 0x56, 0x45)
*/
typedef struct {
   uint32_t file_type_block;
   uint32_t file_size; // Overall file size minus 8 bytes
   uint32_t file_format_id; 
} master_riff_chunk_t;

/*
[Chunk describing the data format]
   FormatBlocID    (4 bytes) : Identifier « fmt␣ »  (0x66, 0x6D, 0x74, 0x20)
   BlocSize        (4 bytes) : Chunk size minus 8 bytes, which is 16 bytes here  (0x10)
   AudioFormat     (2 bytes) : Audio format (1: PCM integer, 3: IEEE 754 float)
   NbrChannels     (2 bytes) : Number of channels
   Frequency       (4 bytes) : Sample rate (in hertz)
   BytePerSec      (4 bytes) : Number of bytes to read per second (Frequency * BytePerBloc).
   BytePerBloc     (2 bytes) : Number of bytes per block (NbrChannels * BitsPerSample / 8).
   BitsPerSample   (2 bytes) : Number of bits per sample
*/
typedef struct {
    uint32_t format_block_id;    // Identifier "fmt " (0x66, 0x6D, 0x74, 0x20)
    uint32_t block_size;         // Chunk size minus 8 bytes, which is 16 bytes here (0x10)
    uint16_t audio_format;       // Audio format (1: PCM integer, 3: IEEE 754 float)
    uint16_t num_channels;       // Number of channels
    uint32_t frequency;          // Sample rate (in hertz)
    uint32_t byte_per_sec;       // Number of bytes to read per second (Frequency * BytePerBloc)
    uint16_t byte_per_block;     // Number of bytes per block (NbrChannels * BitsPerSample / 8)
    uint16_t bits_per_sample;    // Number of bits per sample
} data_format_chunk_t;

/*
[Chunk containing the sampled data]
   DataBlocID      (4 bytes) : Identifier « data »  (0x64, 0x61, 0x74, 0x61)
   DataSize        (4 bytes) : SampledData size
   SampledData  
*/

typedef struct {
    uint32_t data_block_id;      // Identifier "data" (0x64, 0x61, 0x74, 0x61)
    uint32_t data_size;          // SampledData size
} data_chunk_header_t;

typedef struct {
   data_chunk_header_t header;
   uint8_t sampled_data[];      // Flexible array member for actual audio data
} data_chunk_t;

typedef struct {
   master_riff_chunk_t master_chunk;
   data_format_chunk_t data_format_chunk;
   data_chunk_header_t data_chunk_header;
   uint8_t sampled_data[];
} our_wav_output_t;


song_audio_t* parse_wav(uint64_t size, void* data);

int create_wav(void* samples, uint64_t num_samples, uint16_t bits_per_sample, uint32_t frequency, uint16_t num_channels, uint64_t *size, void** data);

#endif
