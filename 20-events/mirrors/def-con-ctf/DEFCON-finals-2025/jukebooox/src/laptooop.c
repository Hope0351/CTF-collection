#include "laptooop.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>
#include <assert.h>

#ifdef DEBUG
#define DEBUG_PRINTF(...) dev_printf("DEBUG: " __VA_ARGS__)
#else
#define DEBUG_PRINTF(...) do {} while(0)
#endif

// Audio processing functions
static void laptooop_process_audio(device_t *device, const audio_wave_t *wave, uint32_t chunk_number, uint32_t total_chunks);

// interaction functions
static void laptooop_download_recording(laptooop_state_t *device);
static void laptooop_clear_recording(laptooop_state_t *device);

// HDD simulation functions
static void hdd_init(hdd_t *hdd);
static void hdd_power_on(hdd_t *hdd);
static void hdd_power_off(hdd_t *hdd);
static void hdd_clear_data(hdd_t *hdd);
static void hdd_write(hdd_t *hdd, uint8_t* bytes, uint32_t num_bytes, uint64_t acceptable_duration);
static void hdd_clear_resonance(hdd_t *hdd, double frequency);
static void hdd_process_resonance(hdd_t *hdd, const audio_wave_t *wave);

// Actuator arm functions
static void actuator_init(actuator_arm_t *arm);
static void actuator_clear_resonance(actuator_arm_t *arm, double frequency);
static uint64_t actuator_move_arm(actuator_arm_t *arm, uint32_t platter_index, uint32_t byte_index);

// Shock sensor functions
static void shock_sensor_init(shock_sensor_t *sensor);
static void shock_sensor_clear_resonance(shock_sensor_t *sensor, double frequency);
static bool shock_sensor_triggered(shock_sensor_t *sensor);
static void shock_sensor_update_state(shock_sensor_t *sensor, double dt_ms);

// Microphone functions
static void laptooop_microphone_init(microphone_t *mic);
static void laptooop_microphone_cleanup(microphone_t *mic);
static void laptooop_microphone_ensure_channels(microphone_t *mic, uint16_t channels, uint32_t sample_rate);


static void dev_printf(const char *format, ...) {
    va_list args;
    va_start(args, format);
    printf("[LAPTOOOP] ");
    vprintf(format, args);
    va_end(args);
}

static uint64_t get_timestamp_ms(void) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (uint64_t)(tv.tv_sec) * 1000 + (uint64_t)(tv.tv_usec) / 1000;
}

static void clear_resonances(Mode* modes, size_t num_modes, double frequency)
{
   for (size_t i = 0; i < num_modes; i++)
   {
      Mode* res = &modes[i];
      
      DEBUG_PRINTF("Clearing f0=%f Q=%f mass=%f coupling=%f\n",
                   res->f0,
                   res->Q,
                   res->mass,
                   res->coupling);
      biquad_bandpass(&res->biquad, res->f0, frequency, res->Q);

      res->x = 0;
      res->v = 0;
      res->a = 0;
      
      if (res->f0 >= frequency / 2.0)
      {
         res->active = false;
      }
      else
      {
         res->active = true;
      }

   }
}

static void print_laptooop_menu()
{
   printf("\n=== laptooop ===\n");
   printf("1. Download recording\n");
   printf("2. Clear recording\n");
   printf("3. Quit\n");
   fflush(stdout);
}

static int device_interact(device_t* device)
{
   bool running = true;

   laptooop_state_t *laptooop = (laptooop_state_t *)device->private_data;

   while (running)
   {
       print_laptooop_menu();
      int choice = get_user_num("Select option: ");
      if (choice == -1) {
         break;
      }
      switch (choice)
      {
         case 1:
            laptooop_download_recording(laptooop);
            break;
         case 2:
            laptooop_clear_recording(laptooop);
            break;
         default:
            running = false;
            break;
      }
   }
   return SUCCESS;   
}

static inline double damping_ratio(const Mode *m)
{
   return 1.0 / (2.0 * m->Q);
}

static void mode_step_mechanics(Mode *m, double force, double dt)
{
   if (!m->active)
   {
      return;
   }
   double omega0 = 2.0 * M_PI * m->f0;
   double zeta   = damping_ratio(m);

   double a = (force / m->mass)
      - 2.0 * zeta * omega0 * m->v
      - omega0 * omega0 * m->x;

   m->a = a;
   m->v += a * dt;
   m->x += m->v * dt;
}

static void process_sample_pa(double sample_pa, double dt, Mode *modes, size_t n_modes)
{
    for (size_t i = 0; i < n_modes; ++i) {
        Mode *m = &modes[i];

        /* 1. band‑pass filter */
        double w = biquad_process(&m->biquad, sample_pa); 

        /* 2. force & mechanics */
        double force = m->coupling * w; // (N/Pa) × Pa = Newtons
        #define OVERSAMPLE 8
        for (int j = 0; j < OVERSAMPLE; j++)
        {
           mode_step_mechanics(m, force / OVERSAMPLE, dt / OVERSAMPLE);
        }
    }
}

// A filter that removes any song input that has too high of a frequency
static int laptooop_filter_song([[maybe_unused]] struct device *self, const song_t *song)
{
   if (song->audio.frequency > LAPTOOOP_MAX_FREQUENCY)
   {
      return FAIL;
   }

   return SUCCESS;
}

// Device management functions
device_t *laptooop_create(uint32_t device_id, position_t pos) {
    device_t *device = calloc(1, sizeof(device_t));
    if (!device) {
        return NULL;
    }
    
    laptooop_state_t *state = malloc(sizeof(laptooop_state_t));
    if (!state) {
        free(device);
        return NULL;
    }
    
    // Allocate memory for HDD
    state->hdd = malloc(sizeof(hdd_t));
    if (!state->hdd) {
        free(state);
        free(device);
        return NULL;
    }
    
    // Initialize device
    device->device_id = device_id;
    snprintf(device->name, sizeof(device->name), "Laptooop %s", "ThinkPad T420");
    device->state = DEVICE_OFF;
    device->position = pos;
    device->sensitivity = 1.0;
    device->process_audio = laptooop_process_audio;
    device->device_interact = device_interact;
    device->private_data = state;
    
    // Initialize laptop state
    snprintf(state->model_name, sizeof(state->model_name), "ThinkPad T420");
    state->laptop_powered = false;
    state->chassis_resonance = 2500.0; // Hz
    state->boot_time = 0;
    
    // Set device toggle handler
    device->filters = NULL;

    // We won't accept songs with too high of a frequency
    device->jukebooox_filter_song = laptooop_filter_song;
    
    // Initialize HDD
    hdd_init(state->hdd);
    
    // Initialize microphone
    laptooop_microphone_init(&state->mic);
    
    dev_printf("Created laptooop '%s' at position (%.1f, %.1f)\n",
               state->model_name, pos.x, pos.y);
    
    return device;
}

void laptooop_destroy(device_t *device) {
    if (!device) return;
    
    laptooop_state_t *state = (laptooop_state_t *)device->private_data;
    if (state) {
        laptooop_microphone_cleanup(&state->mic);
        if (state->hdd) {
            free(state->hdd);
        }
        free(state);
    }
    free(device);
}

#ifdef DEBUG
FILE* debug_displacement = NULL;
uint32_t g_chunk_number = 0;
#endif


// Audio processing functions
static void laptooop_process_audio(device_t *device, const audio_wave_t *wave, uint32_t chunk_number, uint32_t total_chunks) {
    if (!device || !wave) {
        return;
    }
    
    laptooop_state_t *state = (laptooop_state_t *)device->private_data;
    if (!state) {
        return;
    }
    
    // Handle device state changes
    if (device->state == DEVICE_OFF && state->laptop_powered) {
        state->laptop_powered = false;
        hdd_power_off(state->hdd);
        dev_printf("Shutting down...\n");
        return;
    }
    
    if (device->state != DEVICE_ON) {
        return;
    }
    
    // Sync laptop power state with device state
    if (!state->laptop_powered && device->state == DEVICE_ON) {
        state->laptop_powered = true;
        state->boot_time = get_timestamp_ms();
        hdd_power_on(state->hdd);
        dev_printf("Booting up...\n");
    }

    // create a local copy
    audio_wave_t local_wave = {0};
    memcpy(&local_wave, wave, sizeof(*wave));

    // Log first and last chunk
    if (chunk_number == 1) {
        dev_printf("Starting audio recording, %u total chunks expected\n", total_chunks);

#ifdef DEBUG
        /* debug_displacement = fopen("/tmp/displacement.csv", "w"); */
        /* fprintf(debug_displacement, "time,arm_0,arm_1,arm_2,arm_3,sensor_0,sensor_1\n"); */
        /* fprintf(debug_displacement, "0,0,0,0,0,0,0\n"); */
#endif

        // clear any prior recording
        state->hdd->hdd_clear_data_func(state->hdd);

        // clear any resonance 
        hdd_clear_resonance(state->hdd, wave->frequency);

        // store information about the recording in the laptop
        state->recording_bps = wave->bits_per_sample;
        state->recording_frequency = wave->frequency;
        state->recording_channels = wave->channels;
    }

    // calculate the period in nanoseconds (how many nanoseconds the hdd has to write)
    uint64_t time_between_samples = 0;;
    if (local_wave.frequency == 0)
    {
       time_between_samples = UINT64_MAX;
    }
    else
    {
       time_between_samples = 1000000000ULL / local_wave.frequency;
    }
    uint64_t time_for_all_samples = time_between_samples * local_wave.sample_count;
    
    // Ensure microphone filters are set up for the correct number of channels
    laptooop_microphone_ensure_channels(&state->mic, local_wave.channels, local_wave.frequency);
    
    // Process audio through microphone simulation
    uint16_t current_channel = 0;
    for (uint32_t i = 0; i < local_wave.sample_count; i++) {
        // Convert to normalized double for processing
        double sample = sample_to_normalized_double(local_wave.samples[i], local_wave.bits_per_sample);
        
        // Apply microphone processing chain
        sample = microphone_apply_analog_gain(sample, state->mic.analog_gain);
        sample = microphone_add_noise_floor(sample, state->mic.noise_floor);
        sample = microphone_apply_saturation(sample, state->mic.saturation_threshold,
                                           state->mic.nonlinear_a1, state->mic.nonlinear_a2,
                                           state->mic.nonlinear_a3);
        
        /* // Apply filters */
        sample = biquad_process(&state->mic.highpass_filters[current_channel], sample);
        sample = biquad_process(&state->mic.lowpass_filters[current_channel], sample);
        
        // Convert back to sample format and store to HDD simulation
        
        sample_t processed_sample = normalized_double_to_sample(sample, local_wave.bits_per_sample);
        local_wave.samples[i] = processed_sample;
        
        current_channel = (current_channel + 1) % local_wave.channels;
    }

    // write the samples to the hard drive in wav format
    void* samples = convert_from_internal_to_wav_samples(&local_wave.samples, local_wave.sample_count, local_wave.bits_per_sample, local_wave.bits_per_sample);
    size_t num_bytes = (local_wave.bits_per_sample / 8) * local_wave.sample_count;

#ifdef DEBUG
    g_chunk_number = chunk_number;
#endif
    // Since we're buffering these samples before writing them, the effect will happen before writing
    hdd_process_resonance(state->hdd, wave);    

    hdd_write(state->hdd, samples, num_bytes, time_for_all_samples);

    // assume that even after we've written all the samples the head is reparked
    state->hdd->sensor.head_parked = false;

    free(samples);

    if (state->hdd->write_errors >= HDD_WRITE_ERROR_LIMIT)
    {
       DEBUG_PRINTF("Too many write errors %d, shutting down HDD\n", state->hdd->write_errors);
       state->hdd->status = HDD_STATUS_ERROR;
       // VULN
       // Note: doesn't quite make sense here
       #ifdef DEBUG
       printf("hdd=%p\n", state->hdd);
       #endif
       free(state->hdd);
       return;
    }

    
    if (chunk_number == total_chunks) {
        dev_printf("Completed audio recording, %u chunks processed\n", total_chunks);
        state->hdd->status = HDD_STATUS_IDLE;

#ifdef DEBUG
        /* fclose(debug_displacement); */
#endif
    }
}

static void laptooop_download_recording(laptooop_state_t *device)
{
   if (device->hdd->status != HDD_STATUS_IDLE)
   {
      dev_printf("HDD error, cannot read recording\n");
      return;
   }

   if (device->hdd->num_bytes_written == 0)
   {
      dev_printf("Nothing recorded, cannot download!\n");
      return;
   }

   // collate the samples from all the platters
   uint8_t *raw_data = malloc(device->hdd->num_bytes_written);
   if (raw_data == NULL)
   {
      return;
   }

   size_t current_platter = 0;
   size_t current_platter_pos = 0;
   for (size_t i = 0; i < device->hdd->num_bytes_written; i++)
   {
      raw_data[i] = device->hdd->platters[current_platter][current_platter_pos];

      current_platter_pos += 1;
      if (current_platter_pos >= PLATTER_SIZE)
      {
         current_platter_pos = 0;
         current_platter += 1;
         #ifdef DEBUG
         if (current_platter >= NUM_PLATTERS)
         {
            printf("%d\n", current_platter);
         }
         #endif
      }
   }
   

   uint64_t num_samples = device->hdd->num_bytes_written / (device->recording_bps / 8);
   uint64_t wav_bytes = 0;
   uint8_t *wav_data = NULL;

   DEBUG_PRINTF("num_samples=%" PRIu64 " num_bytes_written=%" PRIu64 "\n", num_samples,  device->hdd->num_bytes_written);
   int result = create_wav(raw_data, num_samples, device->recording_bps, device->recording_frequency, device->recording_channels, &wav_bytes, &wav_data);
   free(raw_data);
   if (result == FAIL)
   {
      dev_printf("Error converting to wav, cannot download\n");
      return;
   }

   dev_printf("Recording size: %" PRIu64 "\n", wav_bytes);

   uint64_t total_written = 0;
   size_t remaining = wav_bytes;

   while (total_written < wav_bytes)
   {
      size_t num_written = write(1, wav_data + total_written, remaining);
      if (num_written <= 0) {
         break;
      }
      total_written += num_written;
      remaining -= num_written;
   }

   free(wav_data);
   
   dev_printf("Done sending recording\n");
}

static void laptooop_clear_recording(laptooop_state_t *device)
{
   if (device->hdd->status != HDD_STATUS_IDLE)
   {
      dev_printf("HDD error, cannot clear recording\n");
      return;
   }

   // don't use the "hdd_clear_data" function, so we can put a bug in there
   device->hdd->current_platter = 0;
   device->hdd->current_free_byte = 0;
   device->hdd->num_bytes_written = 0;
   actuator_move_arm(&device->hdd->arm, 0, 0);
}

// HDD simulation functions
static void hdd_init(hdd_t *hdd) {
   // VULN to not set everything to zero so we should leak some data.
   // memset(hdd, 0, sizeof(hdd_t));
   hdd->powered = false;
   hdd->current_platter = 0;
   hdd->current_free_byte = 0;
   hdd->num_bytes_written = 0;
   hdd->write_errors = 0;
   hdd->status = HDD_STATUS_IDLE;

   hdd->hdd_clear_data_func = hdd_clear_data;

   for (size_t i = 0; i < NUM_PLATTERS; i++)
   {
      hdd->platters[i] = malloc(PLATTER_SIZE);
   }

   hdd->self = hdd;
    
   // Initialize actuator arm
   actuator_init(&hdd->arm);
    
   // Initialize shock sensor
   shock_sensor_init(&hdd->sensor);
}



static void hdd_clear_resonance(hdd_t *hdd, double frequency)
{
   actuator_clear_resonance(&hdd->arm, frequency);
   shock_sensor_clear_resonance(&hdd->sensor, frequency);
}

static void hdd_process_resonance(hdd_t *hdd, const audio_wave_t *wave)
{
   double dt = 1.0 / wave->frequency;
  
   for (size_t i = 0; i < wave->sample_count; i++)
   {
      sample_t sample = wave->samples[i];

      double normalized_sample = sample_to_normalized_double(sample, wave->bits_per_sample);

      // Convert to pressure in Pascals
      double pressure = normalized_sample * wave->peak_pa;

      process_sample_pa(pressure, dt, hdd->arm.resonance, ARM_RESONANCE_NUM);
      process_sample_pa(pressure, dt, hdd->sensor.resonance, SHOCK_RESONANCE_NUM);
      shock_sensor_update_state(&hdd->sensor, dt * 1000.0);

#ifdef DEBUG
      /* if (i % 1 == 0) */
      /* { */
      /*    double t = ((i+1) * dt) + (g_chunk_number - 1) * dt * AUDIO_WAVE_SAMPLES; */
      /*    fprintf(debug_displacement, "%.6f,%.12e,%.12e,%.12e,%.12e,%.12e,%.12e\n",  */
      /*            (double)t, */
      /*            (double)hdd->arm.resonance[0].x, */
      /*            (double)hdd->arm.resonance[1].x, */
      /*            (double)hdd->arm.resonance[2].x, */
      /*            (double)hdd->arm.resonance[3].x, */
      /*            (double)hdd->sensor.resonance[0].x, */
      /*            (double)hdd->sensor.resonance[1].x */
      /*       ); */
      /* } */
#endif


   }
}

static void hdd_power_on(hdd_t *hdd) {
    if (!hdd->powered) {
        hdd->powered = true;
        hdd->status = HDD_STATUS_IDLE;
        DEBUG_PRINTF("HDD powered on\n");
    }
}

static void hdd_power_off(hdd_t *hdd) {
    if (hdd->powered) {
        hdd->powered = false;
        hdd->status = HDD_STATUS_PARKED;
        hdd->arm.position = 0.0; // Park heads
        DEBUG_PRINTF("HDD powered off, heads parked\n");
    }
}

static void hdd_clear_data(hdd_t *hdd)
{
   hdd->current_platter = 0;
   hdd->current_free_byte = 0;
   // IDEA: we can remove the following line to have an information leak when sending over multiple files
   // hdd->num_bytes_written = 0;
   actuator_move_arm(&hdd->arm, 0, 0);
   return;
}

static void hdd_write(hdd_t *hdd, uint8_t *bytes, uint32_t num_bytes, uint64_t acceptable_duration_ns)
{
   if (!hdd || !bytes || num_bytes == 0) {
       return;
   }
   
   // Check if HDD is powered and operational
   if (!hdd->powered) {
       hdd->write_errors++;
       return;
   }

   if (hdd->status != HDD_STATUS_IDLE)
   {
      return;
   }

   uint64_t total_seek_time_ns = 0;
   
   // Check if shock sensor has parked the heads
   if (shock_sensor_triggered(&hdd->sensor)) {
      hdd->write_errors++;
      DEBUG_PRINTF("Write failed: heads parked due to shock sensor\n");
      return;
   }
   
   hdd->status = HDD_STATUS_WRITING;
   
   uint32_t bytes_written = 0;
   
   while (bytes_written < num_bytes) {
       // Check if we need to move to next platter
       if (hdd->current_free_byte >= PLATTER_SIZE) {
           hdd->current_platter++;
           hdd->current_free_byte = 0;
           
           // Check if we've run out of platters
           if (hdd->current_platter >= NUM_PLATTERS) {
               DEBUG_PRINTF("Write failed: out of storage space\n");
               hdd->write_errors++;
               hdd->status = HDD_STATUS_ERROR;
               return;
           }
       }
       
       // Calculate seek time to target position
       uint64_t seek_time_ns = actuator_move_arm(&hdd->arm, hdd->current_platter, hdd->current_free_byte);

       // Add to total seek time
       total_seek_time_ns += seek_time_ns;

#ifdef DEBUG
       if (seek_time_ns > 0 && (hdd->current_free_byte % 100 == 0))
       {
          printf("Seeking to %d:%d duration=%llu total_seek_so_far=%llu seek_time_ns=%llu\n",
                 hdd->current_platter,
                 hdd->current_free_byte,
                 acceptable_duration_ns,
                 total_seek_time_ns,
                 seek_time_ns
             );
       }
#endif

       
       // Check if total seek time exceeds acceptable duration
       if (total_seek_time_ns > acceptable_duration_ns) {
           DEBUG_PRINTF("Write failed: total seek time %lu ns exceeds acceptable duration %lu ns\n", 
                       total_seek_time_ns, acceptable_duration_ns);
           hdd->write_errors++;
           hdd->status = HDD_STATUS_IDLE;
           return;
       }

       // Write byte to platter

       hdd->platters[hdd->current_platter][hdd->current_free_byte] = bytes[bytes_written];
       
       hdd->current_free_byte++;
       hdd->num_bytes_written++;
       bytes_written++;
   }
   
   hdd->status = HDD_STATUS_IDLE;
}

// Actuator arm functions
static void actuator_init(actuator_arm_t *arm) {
    memset(arm, 0, sizeof(actuator_arm_t));
    arm->position = 0.0; // Start at outer edge

    Mode modes[] = {
       { .f0 = round(random_double(500.0, 2000.0)), .Q = 13.7, .mass = 1.0, .coupling = 0.08 },
       { .f0 = round(random_double(2200.0, 4000.0)), .Q = 19.3, .mass = 1.0, .coupling = 0.06 },
       { .f0 = round(random_double(4100.0, 6000.0)), .Q = 45.7, .mass = 0.8, .coupling = 0.025 },
       { .f0 = round(random_double(6100.0, 8000.0)), .Q = 54.0, .mass = 0.6, .coupling = 0.070 }
    };

    #ifdef DEBUG
    printf("Actuator modes\n");
    for (int i = 0; i < ARM_RESONANCE_NUM; i++)
    {
       printf("F0=%f\n", modes[i].f0);
    }
    #endif

    assert(ARM_RESONANCE_NUM == sizeof(modes) / sizeof(*modes));

    memcpy(arm->resonance, modes, sizeof(modes));
}

static void actuator_clear_resonance(actuator_arm_t *arm, double frequency)
{
   DEBUG_PRINTF("clear arm resonances freq=%ghz\n", frequency);
   clear_resonances(arm->resonance, ARM_RESONANCE_NUM, frequency);
}

static uint64_t actuator_move_arm(actuator_arm_t *arm, uint32_t platter_index, uint32_t byte_index)
{
   // Calculate target position based on byte position within platter
   // Position ranges from 0.0 (outer edge) to 1.0 (inner edge)
   // All platters share the same radial positions - platter_index doesn't affect arm position
   double target_position = (double)byte_index / PLATTER_SIZE;
   
   // Clamp target position to valid range
   if (target_position > 1.0) target_position = 1.0;
   if (target_position < 0.0) target_position = 0.0;

   // Calculate error due to the resonance frequency
   double x = 0;
   for (int i = 0; i < ARM_RESONANCE_NUM; i++)
   {
      x += arm->resonance[i].x;
   }
  
   double pos_tol = (double)HDD_POSITIONING_THRESHOLD_M;
   double max_penalty = 50.0;

   double x_abs = fabs(x);

   double penalty_factor = max_penalty;
   double error_penalty;
   if (x_abs >= pos_tol) {
      error_penalty = max_penalty;
   } else {
      // Exponential penalty smoothly approaching max_penalty near pos_tol
      // We'll choose the exponent base so that at x == pos_tol, it equals max_penalty
      //
      // penalty = exp(k * x / pos_tol)
      // Want: exp(k * 1.0) = max_penalty → k = ln(max_penalty)
      double k = log(max_penalty);
      penalty_factor = exp(k * (x_abs / pos_tol));
      error_penalty = penalty_factor;
   }
#ifdef DEBUG
   if (x*1e9 > 10)
   {
      // DEBUG_PRINTF("x=%.12em x_nm=%fnm fabs(x)=%.12e penalty_factor=%.12e pos_tol=%.12e\n",x, x*1e9, fabs(x), penalty_factor, pos_tol);
   }
#endif

   // printf("error_penalty=%f\n", error_penalty);

   // Calculate distance to move
   double seek_distance = fabs(target_position - arm->position);
   
   // If we're already at the target position, no movement needed
   // Blue Note paper: within 7.5nm is considered "at position"
   // Convert to our normalized position scale
   double normalized_threshold = HDD_POSITIONING_THRESHOLD_M / HDD_ACTUATOR_STROKE_LENGTH_M;
   
   if ((seek_distance * error_penalty) < normalized_threshold) {
       return 0;
   }
   
   // Update arm state
   arm->target_position = target_position;
   arm->is_seeking = true;
   arm->last_seek_time = get_timestamp_ms();
   
   // Calculate seek time based on distance and positioning errors
   // Base seek time: assume 4.5ms for full stroke (0.0 to 1.0)
   uint64_t base_seek_time_ns = (uint64_t)(seek_distance * 4500000); // 4.5ms in nanoseconds

   uint64_t total_seek_time_ns = (uint64_t)(base_seek_time_ns * error_penalty);
   
   // Update arm position (simplified - assume instantaneous for simulation)
   arm->position = target_position;
   arm->is_seeking = false;

   return total_seek_time_ns;
}

// Shock sensor functions
static void shock_sensor_init(shock_sensor_t *sensor) {
    memset(sensor, 0, sizeof(shock_sensor_t));
    sensor->park_duration_ms = HDD_SHOCK_PARK_DURATION_MS;
    sensor->head_parked = false;
    sensor->remaining_park_duration_ms = 0;

    Mode modes[] = {
       { .f0 = round(random_double(20000.0, 30000.0)), .Q = 6.5, .mass = 0.01, .coupling = 0.04 },
       { .f0 = round(random_double(32000.0, 48000.0)), .Q = 8.3, .mass = 0.015, .coupling = 0.05 }
    };

    #ifdef DEBUG
    printf("Sensor modes\n");
    for (int i = 0; i < SHOCK_RESONANCE_NUM; i++)
    {
       printf("F0=%f\n", modes[i].f0);
    }
    #endif


    assert(SHOCK_RESONANCE_NUM == sizeof(modes) / sizeof(*modes));

    memcpy(sensor->resonance, modes, sizeof(modes));
}

static void shock_sensor_clear_resonance(shock_sensor_t *sensor, double frequency)
{
   DEBUG_PRINTF("clear shock sensor resonances freq=%ghz\n", frequency);
   clear_resonances(sensor->resonance, SHOCK_RESONANCE_NUM, frequency);
   sensor->head_parked = false;
}

// dt_ms is time since last update
static void shock_sensor_update_state(shock_sensor_t *sensor, double dt_ms)
{
   if (sensor->head_parked)
   {
      sensor->remaining_park_duration_ms -= dt_ms;

      if (sensor->remaining_park_duration_ms > 0)
      {
         return;
      }
      DEBUG_PRINTF("Maybe Unparking Head\n");
      sensor->remaining_park_duration_ms = 0;
   }
   
   // Get acceleration of sensor
   double a = 0;

   for (int i = 0; i < SHOCK_RESONANCE_NUM; i++)
   {
      a += sensor->resonance[i].a;
   }
   double a_g = fabs(a) / 9.81;

   // DEBUG_PRINTF("dt_ms=%f a=%f a_g=%f\n", dt_ms, a, a_g);

   if (a_g > 15)
   {
      DEBUG_PRINTF("PARKING HEAD\n");
      sensor->head_parked = true;
      sensor->remaining_park_duration_ms = sensor->park_duration_ms;
   }
   else
   {
      sensor->head_parked = false;
   }

}

static bool shock_sensor_triggered(shock_sensor_t *sensor)
{    
    return sensor->head_parked;
}

// Microphone functions
static void laptooop_microphone_init(microphone_t *mic) {
    memset(mic, 0, sizeof(microphone_t));
    
    // Set default parameters for laptop microphone
    mic->analog_gain = LAPTOOOP_MIC_ANALOG_GAIN;
    mic->noise_floor = LAPTOOOP_MIC_NOISE_FLOOR;
    mic->saturation_threshold = LAPTOOOP_MIC_SATURATION_THRESHOLD;
    mic->nonlinear_a1 = LAPTOOOP_MIC_NONLINEAR_A1;
    mic->nonlinear_a2 = LAPTOOOP_MIC_NONLINEAR_A2;
    mic->nonlinear_a3 = LAPTOOOP_MIC_NONLINEAR_A3;
    mic->lowpass_freq = LAPTOOOP_MIC_LOWPASS_FREQ;
    mic->lowpass_q = LAPTOOOP_MIC_LOWPASS_Q;
    mic->highpass_freq = LAPTOOOP_MIC_HIGHPASS_FREQ;
    mic->highpass_q = LAPTOOOP_MIC_HIGHPASS_Q;
    mic->sensitivity = 0.8; // Slightly less sensitive than dedicated mic
    mic->powered = true;
    mic->filters_initialized = false;
    mic->num_channels = 0;
}

static void laptooop_microphone_cleanup(microphone_t *mic) {
    if (mic->lowpass_filters) {
        free(mic->lowpass_filters);
        mic->lowpass_filters = NULL;
    }
    if (mic->highpass_filters) {
        free(mic->highpass_filters);
        mic->highpass_filters = NULL;
    }
    mic->num_channels = 0;
    mic->filters_initialized = false;
}

static void laptooop_microphone_ensure_channels(microphone_t *mic, uint16_t channels, uint32_t sample_rate) {
    // Check if we need to reallocate or reinitialize
    if (mic->num_channels != channels || mic->last_sample_rate != sample_rate || !mic->filters_initialized) {
        // Clean up old filters
        laptooop_microphone_cleanup(mic);
        
        // Allocate new filter arrays
        mic->lowpass_filters = calloc(channels, sizeof(biquad_t));
        mic->highpass_filters = calloc(channels, sizeof(biquad_t));
        
        if (!mic->lowpass_filters || !mic->highpass_filters) {
            laptooop_microphone_cleanup(mic);
            return;
        }
        
        // Initialize filters for each channel
        for (uint16_t i = 0; i < channels; i++) {
           biquad_lowpass(&mic->lowpass_filters[i], mic->lowpass_freq, 
                          (double)sample_rate, mic->lowpass_q);
            biquad_highpass(&mic->highpass_filters[i], mic->highpass_freq, 
                           (double)sample_rate, mic->highpass_q);
        }
        
        mic->num_channels = channels;
        mic->last_sample_rate = sample_rate;
        mic->filters_initialized = true;
        
        DEBUG_PRINTF("Initialized microphone filters: LP=%.1fHz HP=%.1fHz at %uHz sample rate, %u channels\n",
                    mic->lowpass_freq, mic->highpass_freq, sample_rate, channels);
    }
}
