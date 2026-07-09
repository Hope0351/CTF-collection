#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <fcntl.h>
#include <math.h>
#include <unistd.h>

#include "wav.h"
#include "whisper.h"
#include "echooo.h"
#include "common.h"

#define STRNCASECMP_CONST(str_const, str_to_check) \
    (strncasecmp((str_const), (str_to_check), strlen(str_const)) == 0)

#ifdef DEBUG
#define DEBUG_PRINTF(...) dev_printf("DEBUG: " __VA_ARGS__)
#else
#define DEBUG_PRINTF(...) do {} while(0)
#endif

#define WAKE_WORD_ONE "hey"
#define WAKE_WORD_TWO "hacker"

// Microphone simulation constants - tunable parameters
#define MIC_ANALOG_GAIN 2.0          // Front-end analog gain
#define MIC_NOISE_FLOOR 0.001        // Background noise level
#define MIC_NONLINEAR_A1 0.96         // Linear coefficient
#define MIC_NONLINEAR_A2 0.03         // Quadratic coefficient  
#define MIC_NONLINEAR_A3 0.01        // Cubic coefficient
#define MIC_SATURATION_THRESHOLD 0.9 // Saturation point
#define MIC_LOWPASS_FREQ 8000.0      // Low-pass filter cutoff (Hz)
#define MIC_LOWPASS_Q 0.707          // Low-pass filter Q factor
#define MIC_HIGHPASS_FREQ 400.0       // High-pass filter cutoff (Hz)
#define MIC_HIGHPASS_Q 0.707         // High-pass filter Q factor

static void dev_printf(const char *format, ...) {
    va_list args;
    va_start(args, format);
    printf("[ECHOOO] ");
    vprintf(format, args);
    va_end(args);
}

// Static filter state for microphone processing - moved outside function for reset capability
static biquad_t lowpass_filters[2] = {0};
static biquad_t highpass_filters[2] = {0};
static bool filters_initialized = false;
static uint32_t last_sample_rate = 0;

// Reset microphone filters for new song processing
static void echooo_microphone_reset_filters(void) {
   memset(&lowpass_filters, 0, sizeof(lowpass_filters));
   memset(&highpass_filters, 0, sizeof(highpass_filters));
   filters_initialized = false;
   last_sample_rate = 0;
   DEBUG_PRINTF("Reset microphone filters for new song\n");
}

// Modify in-place the wave samples to simulate microphone distortion 
static void echooo_microphone_process(audio_wave_t* wave)
{
   if (!wave || wave->sample_count == 0) {
      return;
   }
   
   // Initialize filters on first use or if sample rate changed
   if (!filters_initialized || last_sample_rate != wave->frequency) {
      biquad_lowpass(&lowpass_filters[0], MIC_LOWPASS_FREQ, (double)wave->frequency, MIC_LOWPASS_Q);
      biquad_lowpass(&lowpass_filters[1], MIC_LOWPASS_FREQ, (double)wave->frequency, MIC_LOWPASS_Q);
      biquad_highpass(&highpass_filters[0], MIC_HIGHPASS_FREQ, (double)wave->frequency, MIC_HIGHPASS_Q);
      biquad_highpass(&highpass_filters[1], MIC_HIGHPASS_FREQ, (double)wave->frequency, MIC_HIGHPASS_Q);
      filters_initialized = true;
      last_sample_rate = wave->frequency;
      DEBUG_PRINTF("Initialized microphone filters: LP=%.1fHz HP=%.1fHz at %dHz sample rate\n", 
                   MIC_LOWPASS_FREQ, MIC_HIGHPASS_FREQ, wave->frequency);
   }

   // Process each sample
   uint16_t current_channel = 0;
   for (uint32_t i = 0; i < wave->sample_count; i++) {
      // Convert to normalized double for processing
      double sample = sample_to_normalized_double(wave->samples[i], wave->bits_per_sample);
      
      /* 1) Analogue front-end gain with noise */
      sample = microphone_apply_analog_gain(sample, MIC_ANALOG_GAIN);
      
      // Add some noise floor
      // TODO: Check if this fucks up the poller, if it does then we leave it out
      // sample = microphone_add_noise_floor(sample, MIC_NOISE_FLOOR);
      
      /* 2) Polynomial non-linearity (up to 3rd order) */
      sample = microphone_apply_saturation(sample, MIC_SATURATION_THRESHOLD, 
                                         MIC_NONLINEAR_A1, MIC_NONLINEAR_A2, MIC_NONLINEAR_A3);
      
      /* 3) High-pass filter to remove DC and low frequencies */
      sample = biquad_process(&highpass_filters[current_channel], sample);
      
      /* 4) Low-pass filter to keep it in standard human speech range */
      sample = biquad_process(&lowpass_filters[current_channel], sample);

      current_channel = (current_channel + 1) % wave->channels;
      
      // Convert back to sample_t and clamp
      wave->samples[i] = normalized_double_to_sample(sample, wave->bits_per_sample);
   }
   
   DEBUG_PRINTF("Processed %u samples through microphone simulation\n", wave->sample_count);
}


static void execute_command(char** commands)
{
   // commands is a NULL terminated array of characters
   
   // do a system (commands, but add spaces to the commands first)
   // similar to python: system(" ".join(commands))
   
   if (!commands || !commands[0]) {
      return;
   }
   
   // Calculate total length needed for the command string
   size_t total_len = 0;
   for (int i = 0; commands[i]; i++) {
      total_len += strlen(commands[i]) + 1; // +1 for space or null terminator
   }
   
   // Allocate buffer for the full command
   char* full_command = malloc(total_len);
   if (!full_command) {
      dev_printf("Failed to allocate memory for command execution\n");
      return;
   }
   
   // Build the command string by joining with spaces
   full_command[0] = '\0';
   for (int i = 0; commands[i]; i++) {
      if (i > 0) {
         strcat(full_command, " ");
      }
      strcat(full_command, commands[i]);
   }

#ifdef DEBUG
   dev_printf("Executing command: %s\n", full_command);
#endif
   
   // Execute the command
   int result = system(full_command);
   if (result == -1) {
      dev_printf("Command execution failed\n");
   } else {
#ifdef DEBUG
      dev_printf("Command executed with return code: %d\n", result);
#endif
   }
   
   free(full_command);
}

// This is the meat, where we actually process looking for commands to execute
static void process_input(char** input)
{
   char* prior_input = NULL;
   dev_printf("processing voice input\n");
#ifdef DEBUG
   for (uint32_t i = 0; input[i]; i++)
   {
      char* current_input = input[i];
      printf("%s\n", current_input);
   }
#endif
   for (uint32_t i = 0; input[i]; i++)
   {
      char* current_input = input[i];
      if (prior_input == NULL)
      {
         prior_input = current_input;
         continue;
      }

      DEBUG_PRINTF("%s %s\n", prior_input, current_input);
      if (STRNCASECMP_CONST(WAKE_WORD_ONE, prior_input) && STRNCASECMP_CONST(WAKE_WORD_TWO, current_input))
      {
         DEBUG_PRINTF("Admin access\n");
         execute_command(input+i+1);
         return;
      }
      if (STRNCASECMP_CONST("say", prior_input) && STRNCASECMP_CONST("hello", current_input))
      {
         DEBUG_PRINTF("say hello\n");
         dev_printf("hello\n");
      }
      if (STRNCASECMP_CONST("simon", prior_input) && STRNCASECMP_CONST("says", current_input))
      {
         DEBUG_PRINTF("simon says\n");
         printf("[ECHOOO] ");
         for (uint32_t j = i + 1; input[j]; j++)
         {
            printf("%s ", input[j]);
         }
         printf("\n");
      }
      prior_input = current_input;
   }
}

// A filter that removes any input that contains either of the wake words
static int echooo_filter_song([[maybe_unused]] struct device *self, const song_t *song)
{
   uint64_t num_samples = song->audio.sample_count;
   int16_t* internal_samples = convert_from_internal_to_wav_samples(song->audio.samples, num_samples, song->audio.bits_per_second, 16);
   if (internal_samples == NULL)
   {
      return FAIL;
   }

   if (song->audio.channels != 1 && song->audio.channels != 2)
   {
      return FAIL;
   }

   uint64_t wav_size = 0;
   void* wav = NULL;
   int result = create_wav(internal_samples, num_samples, 16, song->audio.frequency, song->audio.channels, &wav_size, &wav);
   if (result == FAIL)
   {
      free(internal_samples);
      return FAIL;
   }

   char** the_input = whisper_transcribe(wav, wav_size);

#ifdef DEBUG
   DEBUG_PRINTF("filter whisper output: ");
   for (uint32_t i = 0; the_input[i]; i++)
   {
      char* current_input = the_input[i];
      printf("%s ", current_input);
   }
   printf("\n");
#endif


   int to_return = SUCCESS;
   for (uint32_t i = 0; the_input[i]; i++)
   {
      char* current_input = the_input[i];
      DEBUG_PRINTF("Filter evaluating %s\n", current_input);
      if (STRNCASECMP_CONST(WAKE_WORD_ONE, current_input) || STRNCASECMP_CONST(WAKE_WORD_TWO, current_input))
      {
         DEBUG_PRINTF("Found wake word, fail\n");

         #ifdef DEBUG
         // We want to capture this wav file for debugging

         // get a valid temp file (we need the filename, we'll indicate it here as <tmp_filename>
         char tmp_filename[] = "/tmp/debug_wav_XXXXXX";
         int tmp_fd = mkstemp(tmp_filename);
         if (tmp_fd == -1) {
            DEBUG_PRINTF("Failed to create temporary file for debugging\n");
         } else {
            // write content of wav to <tmp_filename>
            ssize_t bytes_written = write(tmp_fd, wav, wav_size);
            close(tmp_fd);
            
            if (bytes_written == (ssize_t)wav_size) {
               DEBUG_PRINTF("Problem compressed wav file:\n");
               
               printf("START_DEBUG_WAV\n");
               // Use system to: gzip the file, pipe it to base64, this should output the base64 content to stdout
               char gzip_command[512];
               snprintf(gzip_command, sizeof(gzip_command), "gzip -c %s | base64", tmp_filename);
               system(gzip_command);
               printf("END_DEBUG_WAV\n");
            } else {
               DEBUG_PRINTF("Failed to write wav data to temporary file\n");
            }
            
            // Clean up temporary file
            unlink(tmp_filename);
         }
         
         #endif
         
         to_return = FAIL;
         break;
      }
   }
   
   for (uint32_t i = 0; the_input[i]; i++)
   {
      free(the_input[i]);
   }
   free(the_input);
   free(internal_samples);
   free(wav);
   return to_return;
}



static void echooo_process_audio(device_t *device, const audio_wave_t *wave, uint32_t chunk_number, uint32_t total_chunks) {
    if (!device || !device->private_data || !wave) {
        return;
    }
    
    echooo_state_t *state = (echooo_state_t *)device->private_data;

    // only to stereo or mono
    if (wave->channels != 1 && wave->channels != 2)
    {
       DEBUG_PRINTF("Incorrect number of channels\n");
       return;
    }
    
    // create a local copy
    audio_wave_t local_wave = {0};
    memcpy(&local_wave, wave, sizeof(*wave));

    // microphone process the wave audio
    echooo_microphone_process(&local_wave);
    
    // convert from audio_wave_t to our internal sample (16-bits), and add it to the sample list    
    int16_t* internal_samples = convert_from_internal_to_wav_samples(local_wave.samples, local_wave.sample_count, local_wave.bits_per_sample, 16);
    if (state->last == NULL)
    {
       state->head = calloc(1, sizeof(sample_list_t));
       state->head->samples = internal_samples;
       state->head->num_samples = local_wave.sample_count;
       state->head->next = NULL;
       state->last = state->head;
       DEBUG_PRINTF("Added to start of list\n");
    }
    else
    {
       state->last->next = calloc(1, sizeof(sample_list_t));;
       state->last->next->samples = internal_samples;
       state->last->next->num_samples = local_wave.sample_count;
       state->last->next->next = NULL;
       state->last = state->last->next;
    }

    // On the last chunk
    if (chunk_number == total_chunks)
    {
       // convert to a wav, pass it to whisper, then clean everything up

       // Figure out how many samples we have
       uint64_t total_samples = 0;

       {
          sample_list_t* cur = state->head;
          while (cur)
          {
             total_samples += cur->num_samples;
             cur = cur->next;
          }
       }

       DEBUG_PRINTF("Total number of samples %d\n", total_samples);

       // alloc enough size
       int16_t* samples = calloc(1, sizeof(int16_t) * total_samples);

       // then go through and copy over all the samples to here
       {
          sample_list_t* cur = state->head;
          int16_t* next_sample = samples;
          while (cur)
          {
             memcpy(next_sample, cur->samples, cur->num_samples*sizeof(*next_sample));
             next_sample += cur->num_samples;
             cur = cur->next;
          }
       }

       // convert to wav
       uint64_t wav_size = 0;
       void* wav = NULL;
       int result = create_wav(samples, total_samples, 16, wave->frequency, wave->channels, &wav_size, &wav);
       if (result == FAIL)
       {
          goto done_rest;
       }

#ifdef DEBUG
       dev_printf("Writing tmp file\n");
       int fd = open("/tmp/test.wav", O_WRONLY | O_CREAT | O_TRUNC);
       int num_written = write(fd, wav, wav_size);
       dev_printf("%d: %d/%d\n", fd, num_written, wav_size);
       close(fd);
#endif

       // pass to whisper
       char** the_input = whisper_transcribe(wav, wav_size);

       // process whisper
       process_input(the_input);

       // clean everything up
       free(wav);
       for (uint32_t i = 0; the_input[i]; i++)
       {
          free(the_input[i]);
       }
       free(the_input);
       
      done_rest:
       free(samples);
       
       sample_list_t* cur = state->head;
       while (cur)
       {
          sample_list_t* tmp = cur;
          cur = cur->next;
          free(tmp->samples);
          free(tmp);
       }
       state->head = NULL;
       state->last = NULL;
       
       // Reset microphone filters for next song
       echooo_microphone_reset_filters();
    }
    
    dev_printf("Processing audio wave with Pa %.2f (chunk %u/%u)\n", wave->peak_pa, chunk_number, total_chunks);
}

device_t *echooo_create(uint32_t device_id, position_t pos) {
    device_t *device = calloc(1, sizeof(device_t));
    if (!device) {
        return NULL;
    }
    
    echooo_state_t *state = calloc(1, sizeof(echooo_state_t));
    if (!state) {
        free(device);
        return NULL;
    }
    
    // Initialize device
    device->device_id = device_id;
    snprintf(device->name, sizeof(device->name), "Echooo Device %u", device_id);
    device->state = DEVICE_OFF;
    device->position = pos;
    device->sensitivity = 1.0;
    device->process_audio = echooo_process_audio;
    device->jukebooox_filter_song = echooo_filter_song;
    device->device_interact = NULL;
    device->private_data = state;
    
    return device;
}

void echooo_destroy(device_t *device) {
    if (device) {
        if (device->private_data) {
            free(device->private_data);
        }
        free(device);
    }
}

