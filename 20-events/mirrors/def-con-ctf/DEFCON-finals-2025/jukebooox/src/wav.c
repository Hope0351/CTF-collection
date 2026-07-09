#include "common.h"
#include "wav.h"

// This function should advance data looking for the next chunk that
// has a tag called tag.
static int get_next_chunk(uint64_t* size, void** data, uint32_t tag)
{
    uint8_t* current = (uint8_t*)*data;
    uint64_t remaining = *size;
    
    while (remaining >= 8) {  // Need at least 8 bytes for chunk header (4 bytes tag + 4 bytes size)
        uint32_t chunk_tag = *(uint32_t*)current;
        uint64_t chunk_size = *(uint32_t*)(current + 4);
        
        if (chunk_tag == tag) {
            // Found the chunk we're looking for
            *data = current;  // Update data pointer to be this chunk
            *size = remaining;  // Update remaining size
            return SUCCESS;  // We did it
        }
        
        // Skip this chunk and move to next
        uint64_t total_chunk_size = 8 + chunk_size;
        if (total_chunk_size > remaining) {
            break;  // Chunk size is invalid
        }
        
        current += total_chunk_size;
        remaining -= total_chunk_size;
    }
    
    return FAIL;  // Chunk not found
}

song_audio_t* parse_wav(uint64_t size, void* data)
{
   if (data == NULL)
   {
      return NULL;
   }
   if (size < sizeof(master_riff_chunk_t))
   {
      return NULL;
   }
   master_riff_chunk_t *master_chunk = (master_riff_chunk_t *)data;

   // sanity check master chunk
   if (master_chunk->file_type_block != RIFF_TAG)
   {
      return NULL;
   }

   if (master_chunk->file_format_id != WAV_TAG)
   {
      return NULL;
   }

   if ((size - 8) != master_chunk->file_size)
   {
      return NULL;
   }

   data = (void*) ((uint8_t*)data + sizeof(*master_chunk));
   size = size - sizeof(*master_chunk);

   song_audio_t* song = calloc(1, sizeof(song_audio_t));

   if (FAIL == get_next_chunk(&size, &data, FORMAT_TAG))
   {
      free(song);
      return NULL;
   }

   // Now data should point to a format chunk
   
   data_format_chunk_t* fmt_chunk = (data_format_chunk_t*)data;
   if ((fmt_chunk->block_size + 8) > sizeof(*fmt_chunk))
   {
      free(song);
      return NULL;
   }

   if ((fmt_chunk->block_size + 8) > size)
   {
      free(song);
      return NULL;
   }

   // we only support PCM
   if (fmt_chunk->audio_format != PCM_FORMAT)
   {
      free(song);
      return NULL;
   }

   // check that bits_per_sample is supported
   uint16_t bps = fmt_chunk->bits_per_sample;
   if (bps != 8 && bps != 16 && bps != 32)
   {
      free(song);
      return NULL;
   }

   song->channels = fmt_chunk->num_channels;
   song->frequency = fmt_chunk->frequency;
   song->bits_per_second = bps;

   // Now read in all the samples from data
   bool done = false;

   uint32_t free_samples = 32;
   
   song->samples = calloc(free_samples, sizeof(*(song->samples)));
#ifdef DEBUG
   printf("samples = %p\n", song->samples);
#endif

   song->sample_count = 0;
   
   while (!done)
   {
      if (FAIL == get_next_chunk(&size, &data, DATA_TAG))
      {
         done = true;
         continue;
      }
      data_chunk_t* data_chunk = data;
      if (data_chunk->header.data_size > size)
      {
         done = true;
         continue;
      }
      if ((data_chunk->header.data_size + 8) > size)
      {
         done = true;
         continue;
      }

      uint64_t required_samples = data_chunk->header.data_size / (bps / 8);
      if (required_samples > free_samples)
      {
         uint64_t new_size = sizeof(*(song->samples))*(required_samples + song->sample_count);
         song->samples = realloc(song->samples, new_size);
         #ifdef DEBUG
         printf("new samples = %p\n", song->samples);
         #endif
         free_samples = required_samples;
      }

      // now we should absoultely have enough space
      sample_t* new_samples = song->samples + song->sample_count;

      // 32 means 4 bytes (our native size, so we can memcpy)
      if (bps == 32)
      {
         memcpy(new_samples, data_chunk->sampled_data, sizeof(*new_samples)*required_samples);
      }
      else if (bps == 8)
      {
         // hmm, bps of 8 means we need to copy each byte over
         uint8_t* data_8_bit = (uint8_t*)data_chunk->sampled_data;
         for (uint64_t i = 0; i < required_samples; i++)
         {
            new_samples[i] = data_8_bit[i];
         }
      }
      else if (bps == 16)
      {
         // bps of 16 means two bytes
         int16_t* data_16_bit = (int16_t*)data_chunk->sampled_data;
         for (uint64_t i = 0; i < required_samples; i++)
         {
            new_samples[i] = data_16_bit[i];
            /* if (i > 0x600) */
            /* { */
            /*    printf("0x%x\n", new_samples[i]); */
            /* } */
         }
      }
      free_samples -= required_samples;
      song->sample_count += required_samples;

      // need to increment the chunk
      uint64_t chunk_size = (data_chunk->header.data_size + 8);
      size -= chunk_size;
      data = (void*) ((uint8_t*)data + chunk_size);
   }

   return song;
}

// Create a wav in wav of size size based on samples, num_samples, bits_per_sample, frequency, and num_channels
int create_wav(void* samples, uint64_t num_samples, uint16_t bits_per_sample, uint32_t frequency, uint16_t num_channels, uint64_t *size, void** wav)
{
   uint64_t data_size = num_samples * (bits_per_sample / 8);
   if (data_size < num_samples)
   {
      return FAIL;
   }

   uint64_t wav_size = sizeof(our_wav_output_t) + data_size;
   if (wav_size < data_size)
   {
      return FAIL;
   }
   
   our_wav_output_t* output = calloc(1, wav_size);
   if (output == NULL)
   {
      return FAIL;
   }

   output->master_chunk.file_type_block = RIFF_TAG;
   output->master_chunk.file_size = wav_size - 8;
   output->master_chunk.file_format_id = WAV_TAG;

   output->data_format_chunk.format_block_id = FORMAT_TAG;
   output->data_format_chunk.block_size = sizeof(data_format_chunk_t) - 8;
   output->data_format_chunk.audio_format = PCM_FORMAT;
   output->data_format_chunk.num_channels = num_channels;
   output->data_format_chunk.frequency = frequency;
   output->data_format_chunk.byte_per_block = num_channels * bits_per_sample / 8;
   output->data_format_chunk.byte_per_sec = frequency * output->data_format_chunk.byte_per_block;
   output->data_format_chunk.bits_per_sample = bits_per_sample;

   // data chunk
   output->data_chunk_header.data_block_id = DATA_TAG;
   output->data_chunk_header.data_size = data_size;
   memcpy(&output->sampled_data, samples, data_size);


   *size = wav_size;
   *wav = output;
   return SUCCESS;
}
