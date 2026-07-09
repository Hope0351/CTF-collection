#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdarg.h>
#include <unistd.h>
#include <inttypes.h>
#include <sys/mman.h>
#include <math.h>

#include "prooodigi.h"
#include "key_detection.h"

#ifdef DEBUG
#define DEBUG_PRINTF(...) dev_printf("DEBUG: " __VA_ARGS__)
#else
#define DEBUG_PRINTF(...) do {} while(0)
#endif

void dev_printf(const char *format, ...) {
    va_list args;
    va_start(args, format);
    printf("[PROOODIGI] ");
    vprintf(format, args);
    va_end(args);
}


int rand_range(int min, int max) {
    if (max <= min) return min;  // handle edge case
    return min + rand() % (max - min + 1);
}

// A filter that removes any song input that has too low of frequency or not mono
int prooodigi_filter_song([[maybe_unused]] struct device *self, const song_t *song)
{
   if (song->audio.frequency < PROOODIGI_MIN_FREQUENCY)
   {
      DEBUG_PRINTF("FAIL frequency: %d\n", song->audio.frequency);
      return FAIL;
   }

   if (song->audio.channels != 1)
   {
      DEBUG_PRINTF("FAIL channels: %d\n", song->audio.channels);
      return FAIL;
   }
   return SUCCESS;
}

void prooodigi_reset_master(prooodigi_state_t *prooodigi)
{
   prooodigi->tape_size = 0;
   prooodigi->has_recording = 0;
}



void prooodigi_process_audio(device_t *device, const audio_wave_t *wave, uint32_t chunk_number, uint32_t total_chunks) {
    if (!device || !device->private_data || !wave) {
        return;
    }
    
    prooodigi_state_t *state = (prooodigi_state_t *)device->private_data;

    if (chunk_number == 1)
    {
       prooodigi_reset_master(state);
       state->frequency = wave->frequency;
       state->bits_per_sample = wave->bits_per_sample;
       state->has_recording = true;
       DEBUG_PRINTF("Got a new song to record to tape %dhz %dbps\n", state->frequency, state->bits_per_sample);
    }

    if (state->tape_size >= TAPE_DATA_SIZE)
    {
       dev_printf("Tape full\n");
       return;
    }


    // should we process the wave at all? Just in case, create a local_wave
    audio_wave_t local_wave = {0};
    memcpy(&local_wave, wave, sizeof(*wave));

    
    // Record data to tape
    for (size_t i = 0; i < local_wave.sample_count; i++)
    {
       sample_t the_sample = clip_sample(local_wave.samples[i], local_wave.bits_per_sample);

       size_t num_bytes_to_copy = local_wave.bits_per_sample / 8;
       for (size_t j = 0; j < num_bytes_to_copy; j++)
       {
          if (state->tape_size >= TAPE_DATA_SIZE)
          {
             dev_printf("Tape full\n");
             return;
          }

          state->tape->data[state->tape_size] = ((uint8_t*)&the_sample)[j];
          state->tape_size += 1;
       }
    }
}

void print_prooodigi_menu()
{
   printf("\n=== prooodigi ===\n");
   printf("1. Download master\n");
   printf("2. Validate master\n");
   printf("3. Reset master\n");
   printf("4. Crash and burn\n");
   printf("5. Quit\n");
   fflush(stdout);
}

/*
  Goal of this function is to see if the blown up sample (normalized so the loudest sound is 0db) will trigger a vinyl 
 */
size_t
count_clicks_vinyl_jump(const double_t *samples,
                        size_t        sample_num,
                        double        sample_rate)
{

   size_t clicks = 0;
   size_t window = 1024;
   size_t hop = 256;

   double V_MAX_CM_S = 200;
   double F_REF = 1000;
   double SLOPE_MAX = 2 * M_PI * F_REF;
   double T_abs = (V_MAX_CM_S / 50) * (SLOPE_MAX / sample_rate);

   for (size_t i = 0; i < sample_num; i += hop)
   {
      double max_amp = 0.0;

      for (size_t j = i; j < (i+window); j++)
      {
         if (j >= sample_num)
         {
            break;
         }
            
         if (fabs(samples[j]) > max_amp)
         {
            max_amp = fabs(samples[j]);
         }
      }

      if (max_amp == 0.0)
      {
         continue;
      }

      for (size_t j = i+1; j < (i+window); j++)
      {
         if (j >= sample_num)
         {
            break;
         }

         double norm_sample = samples[j] / max_amp;
         double norm_prior_sample = samples[j-1] / max_amp;

         double diff = norm_sample - norm_prior_sample;

         if (fabs(diff) > T_abs)
         {
            clicks += 1;
         }
      }
   }
   return clicks;
}

// this is the core function that they need to get their shellcode to conform to in order to be executed
bool validate_recording(prooodigi_state_t *prooodigi, int16_t* key)
{

   if (prooodigi->bits_per_sample == 0)
   {
      return false;
   }

   size_t num_samples = prooodigi->tape_size / (prooodigi->bits_per_sample / 8);

   if (num_samples == 0)
   {
      return false;
   }

   // Check if bpm is what we want
   double* samples_double = calloc(num_samples, sizeof(double));
   if (samples_double == NULL)
   {
      return false;
   }

   for (size_t i = 0; i < num_samples; i++)
   {
      sample_t sample = 0;
      if (prooodigi->bits_per_sample == 8)
      {
         sample = prooodigi->tape->data[i];
      }
      else if (prooodigi->bits_per_sample == 16)
      {
         sample = ((int16_t*)prooodigi->tape->data)[i];
      }
      else if (prooodigi->bits_per_sample == 32)
      {
         sample = ((sample_t*)prooodigi->tape->data)[i];
      }
      samples_double[i] = sample_to_normalized_double(sample, prooodigi->bits_per_sample);
   }

   size_t vinyl_clicks = count_clicks_vinyl_jump(samples_double, num_samples, prooodigi->frequency);

   *key = detect_key(samples_double, num_samples, prooodigi->frequency);

   DEBUG_PRINTF("vinyl_clicks=%" PRIu64  " in key %s\n", vinyl_clicks, KEY_NAMES[*key]);

   if (*key != prooodigi->desired_key)
   {
      dev_printf("Not in the right key %d... pass\n", *key);
      free(samples_double);
      return false;
   }

   if (vinyl_clicks != 0)
   {
      dev_printf("I can't master this at full volume on vinyl, can't handle any clicks or pops... pass\n");
      free(samples_double);
      return false;
   }

   free(samples_double);
   return true;
}


void prooodigi_validate_master(prooodigi_state_t *prooodigi)
{
   int16_t key = -1;
   if (validate_recording(prooodigi, &key))
   {
      dev_printf("Recording in %s is valid.\n", KEY_NAMES[key]);      
   }
   else
   {
      dev_printf("Recording in %s is not valid.\n", KEY_NAMES[key]);
   }
}

void prooodigi_download_master(prooodigi_state_t *prooodigi)
{
   if (prooodigi->tape == NULL)
   {
      dev_printf("No tape!\n");
      return;
   }
   dev_printf("Master tape size: %" PRIu64 "\n", prooodigi->tape_size);

   uint64_t total_written = 0;
   size_t remaining = prooodigi->tape_size;

   while (total_written < prooodigi->tape_size)
   {
      size_t num_written = write(1, prooodigi->tape->data + total_written, remaining);
      if (num_written <= 0) {
         break;
      }
      total_written += num_written;
      remaining -= num_written;
   }

   dev_printf("Done sending master\n");
}

__attribute__((naked)) static void shellcode_header(void* new_sp) {
   __asm__ volatile (
      "mov %rdi, %rsp         \n\t"  // Set up the new stack
      "xorq %rax, %rax        \n\t"  // Zero all registers
      "xorq %rax, %rax        \n\t"  // Zero all registers
      "xorq %rbx, %rbx        \n\t"  
      "xorq %rcx, %rcx        \n\t"
      "xorq %rdx, %rdx        \n\t"
      "xorq %rsi, %rsi        \n\t"
      "xorq %rdi, %rdi        \n\t"
      "xorq %r8, %r8          \n\t"
      "xorq %r9, %r9          \n\t"
      "xorq %r10, %r10        \n\t"
      "xorq %r11, %r11        \n\t"
      "xorq %r12, %r12        \n\t"
      "xorq %r13, %r13        \n\t"
      "xorq %r14, %r14        \n\t"
      "xorq %r15, %r15        \n\t"
      "xorq %rbp, %rbp        \n\t"  // Zero base pointer
      "the_end:         \n\t"  // Label marking end of useful shellcode
   );
}

static size_t get_shellcode_size() {
   size_t size;
   __asm__ volatile (
      "leaq the_end(%%rip), %%rax \n\t"
      "leaq %c1(%%rip), %%rbx          \n\t"
      "subq %%rbx, %%rax               \n\t"
      "movq %%rax, %0                  \n\t"
      : "=m" (size)
      : "i" (shellcode_header)
      : "rax", "rbx"
   );
   return size;
}

void prooodigi_crash_and_burn(prooodigi_state_t *prooodigi)
{
   int16_t key;
   if (!validate_recording(prooodigi, &key))
   {
      dev_printf("Not a good recording anyway, nothing to do...\n");
      return;
   }
   dev_printf("This will really destroy everything\n");
   
   if (!prooodigi || !prooodigi->tape) {
      dev_printf("No tape to execute!\n");
      return;
   }

   // Check size compatibility at runtime
   size_t shellcode_size = get_shellcode_size();
   DEBUG_PRINTF("Shellcode header size: %zu, Tape header size: %d\n", shellcode_size, TAPE_HEADER_SIZE);
   
   if (shellcode_size != TAPE_HEADER_SIZE) {
      DEBUG_PRINTF("ERROR: Shellcode header (%zu bytes) too large for tape header (%d bytes)\n", 
                 shellcode_size, TAPE_HEADER_SIZE);
      return;
   }
   
   // Copy the shellcode header to the tape header
   memcpy(prooodigi->tape->header, (void*)shellcode_header, shellcode_size);
   
   // Execute the shellcode header from tape, which will zero registers and jump to tape data
   void (*copied_header)(void*) = (void(*)(void))prooodigi->tape->header;

   // Set up a new stack
   void* new_stack = mmap(NULL, 0x200, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
   if (new_stack == MAP_FAILED)
   {
      DEBUG_PRINTF("new stack allocation failed\n");
      return;
   }
   copied_header(new_stack);
}



int device_interact(device_t* device)
{
   bool running = true;

   prooodigi_state_t *prooodigi = (prooodigi_state_t *)device->private_data;

   while (running)
   {
      print_prooodigi_menu();
      int choice = get_user_num("Select option: ");
      if (choice == -1) {
         break;
      }
      switch (choice)
      {
         case 1:
            prooodigi_download_master(prooodigi);
            break;
         case 2:
            prooodigi_validate_master(prooodigi);
            break;
         case 3:
            prooodigi_reset_master(prooodigi);
            break;
         case 4:
            prooodigi_crash_and_burn(prooodigi);
            break;
         default:
            running = false;
            break;
      }
   }
   return SUCCESS;   
}


device_t *prooodigi_create(uint32_t device_id, position_t pos) {
    device_t *device = calloc(1, sizeof(device_t));
    if (!device) {
        return NULL;
    }
    
    prooodigi_state_t *state = calloc(1, sizeof(prooodigi_state_t));
    if (!state) {
        free(device);
        return NULL;
    }
    
    // Initialize device
    device->device_id = device_id;
    snprintf(device->name, sizeof(device->name), "Mitsubishi ProooDigi %u", device_id);
    device->state = DEVICE_OFF;
    device->position = pos;
    device->sensitivity = 2.0;  // More sensitive than other devices
    device->process_audio = prooodigi_process_audio;
    device->jukebooox_filter_song = prooodigi_filter_song;
    device->device_interact = device_interact;
    device->private_data = state;
    
    state->tape_size = 0;
    state->tape = mmap(NULL, sizeof(tape_t), PROT_EXEC | PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (state->tape == MAP_FAILED)
    {
       DEBUG_PRINTF("Unable to mmap the tape, failure\n");
       free(device);
       return NULL;
    }

    uint16_t rand_key = rand_range(0, KEY_NUMBERS-1);

    state->desired_key = rand_key;

    dev_printf("Looking for a song to master into vinyl that slaps in %s\n", KEY_NAMES[state->desired_key]);
    state->has_recording = false;
    
    return device;
}

void prooodigi_destroy(device_t *device) {
    if (device) {
        if (device->private_data) {
            free(device->private_data);
        }
        free(device);
    }
}

