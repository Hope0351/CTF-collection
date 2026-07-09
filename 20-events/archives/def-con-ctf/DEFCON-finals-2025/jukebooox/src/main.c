#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#include <dlfcn.h>

#include "common.h"
#include "wav.h"
#include "echooo.h"
#include "prooodigi.h"
#include "laptooop.h"
#include "md5.h"
#ifdef DEBUG
#include "whisper.h"
#ifdef __APPLE__
#include "macos_play_device.h"
#endif
#endif

#ifdef DEBUG
#define DEBUG_PRINTF(...) printf("DEBUG: " __VA_ARGS__)
#else
#define DEBUG_PRINTF(...) do {} while(0)
#endif

static jukebox_state_t g_jukebox;

/*
 * Estimate peak pressure amplitude in Pascals
 * based on speaker sensitivity, amp power, volume, and distance
 *
 * Parameters:
 *   sensitivity_dB     – e.g., 94.0 (dB SPL @ 1W/1m)
 *   amp_rms_power_w    – e.g., 100.0 (amp’s rated wattage)
 *   volume_fraction    – 0.0 to 1.0 (normalized volume knob setting)
 *   distance_m         – distance from speaker to target (in meters)
 *
 * Returns:
 *   pressure_peak_pa   – peak pressure amplitude in Pascals
 */
static double compute_pressure_peak_pa(double sensitivity_dB,
                              double amp_rms_power_w,
                              double volume_fraction,
                              double distance_m)
{
    // Prevent invalid inputs
    if (volume_fraction <= 0.0 || amp_rms_power_w <= 0.0 || distance_m <= 0.0)
    {
        return 0.0;
    }

    // Approximate delivered power at this volume
    // Assume volume curve is logarithmic: power ∝ (volume^2)
    double power_w = amp_rms_power_w * (volume_fraction * volume_fraction);

    // SPL at 1m
    double spl_dB = sensitivity_dB + 10.0 * log10(power_w);

    // Convert SPL to RMS pressure
    const double p0 = 20e-6;  // reference pressure in Pascals
    double p_rms = p0 * pow(10.0, spl_dB / 20.0);

    // Convert to peak pressure
    double p_peak = p_rms * sqrt(2.0);

    // Apply inverse-distance model
    double p_at_distance = p_peak / distance_m;

    return p_at_distance;
}

static double distance_between(position_t a, position_t b) {
    double dx = b.x - a.x;
    double dy = b.y - a.y;
    return sqrt(dx * dx + dy * dy);
}

static void add_filter_to_device(device_t* device, biquad_type_t type, double frequency, double Q, double gain)
{
   filter_list_t* new_filter = calloc(1, sizeof(filter_list_t));

   new_filter->type = type;
   new_filter->frequency = frequency;
   new_filter->Q = Q;
   new_filter->gain = gain;
   new_filter->biquad = NULL;     // Will be allocated in init_all_filters
   new_filter->channels = 0;      // Will be set in init_all_filters

   if (device->filters == NULL)
   {
      device->filters = new_filter;
   }
   else
   {
      filter_list_t* cur = device->filters;
      while (cur->next != NULL)
      {
         cur = cur->next;
      }
      cur->next = new_filter;
   }   
}

static int load_filters(void)
{
   char* file_path = get_env_or_default("FILTER_PATH", "filters.txt");
   FILE* file = fopen(file_path, "r");
   if (!file) {
      perror("fopen");
      return FAIL;
   }

   size_t count = 0;
   uint32_t device_id = 0;
   int raw_type = 0;
   double frequency = 0;
   double Q = 0;
   double gain = 0;
   while (count < MAX_FILTERS &&
          fscanf(file, "%" SCNu32 " %d %lf %lf %lf",
                 &device_id,
                 &raw_type,
                 &frequency,
                 &Q,
                 &gain) == 5) {

      biquad_type_t biquad_type = (biquad_type_t) raw_type;
      if (device_id >= MAX_DEVICES)
      {
         printf("Incorrect device id\n");
         fclose(file);
         return FAIL;
      }

      if (Q <= 0)
      {
         return FAIL;
      }
      if (frequency <= 0)
      {
         return FAIL;
      }

      device_t *device = g_jukebox.devices[device_id];
      add_filter_to_device(device, biquad_type, frequency, Q, gain);
      count++;
   }   


   if (!feof(file)) {
      printf("Invalid filter file %s\n", file_path);
      fclose(file);
      return FAIL;
   }
   

   fclose(file);
   return SUCCESS;
}

static void init_all_filters(uint32_t sample_rate, uint16_t channels)
{
   for (uint32_t i = 0; i < MAX_DEVICES; i++) {
      if (!g_jukebox.device_loaded[i])
      {
         continue;
      }
      device_t *device = g_jukebox.devices[i];
      filter_list_t* cur = device->filters;
      while (cur)
      {
         // Allocate/reallocate biquad array if channel count changed
         if (cur->biquad == NULL || cur->channels != channels) {
            free(cur->biquad);  // Safe to call on NULL
            cur->biquad = calloc(channels, sizeof(biquad_t));
            cur->channels = channels;
         }
         
         // Initialize filter for each channel separately
         for (uint16_t channel = 0; channel < channels; channel++) {
            biquad_reset(&cur->biquad[channel]);
            biquad_init(&cur->biquad[channel], cur->type, cur->frequency, sample_rate, cur->Q, cur->gain);
         }
         cur = cur->next;
      }
   }
}

static void process_filters(device_t *device, audio_wave_t *wav)
{
    if (device->filters == NULL) return;

    #ifdef DEBUG
    printf("Processing filters with %d channels\n", wav->channels);
    #endif

    // Process samples with proper channel separation
    for(uint32_t i = 0; i < wav->sample_count; i += wav->channels)
    {
        // Process each channel independently
        for(uint16_t channel = 0; channel < wav->channels; channel++)
        {
            uint32_t sample_idx = i + channel;
            if (sample_idx >= wav->sample_count) break;
            
            double sample = sample_to_normalized_double(wav->samples[sample_idx], wav->bits_per_sample);
            
            #ifdef DEBUG
            // int32_t before = wav->samples[sample_idx];
            #endif
            
            // Apply each filter in chain using THIS channel's state
            filter_list_t* cur = device->filters;
            while (cur) {
                // Ensure filter has been initialized for this many channels
                if (cur->biquad != NULL && channel < cur->channels) {
                    sample = biquad_process(&cur->biquad[channel], sample);
                }
                cur = cur->next;
            }
            
            wav->samples[sample_idx] = normalized_double_to_sample(sample, wav->bits_per_sample);
            
            #ifdef DEBUG
            // printf("Channel %d: %d -> %d\n", channel, before, wav->samples[sample_idx]);
            #endif
        }
    }
}

static device_t* load_device_module(const char* module_name, const char* create_function_name, uint32_t device_id, position_t pos) {
    char module_path[512];
    const char* device_dir = get_env_or_default("JUKEBOOOX_DEVICE_DIR", ".");
    
    snprintf(module_path, sizeof(module_path), "%s/%s.so", device_dir, module_name);
    DEBUG_PRINTF("Loading module from: %s\n", module_path);
    
    void* handle = dlopen(module_path, RTLD_NOW);
    if (handle == NULL) {
        DEBUG_PRINTF("Unable to load %s: %s\n", module_name, dlerror());
        return NULL;
    }
    
    dlerror(); // Clear any existing error
    
    device_t* (*create_device)(uint32_t, position_t);
    *(void**)(&create_device) = dlsym(handle, create_function_name);
    
    char* error = dlerror();
    if (error != NULL) {
        DEBUG_PRINTF("Error loading %s function: %s\n", create_function_name, error);
        dlclose(handle);
        return NULL;
    }
    
    device_t* device = create_device(device_id, pos);
    if (device == NULL) {
        DEBUG_PRINTF("Failed to create %s device\n", module_name);
        dlclose(handle);
        return NULL;
    }
    
    DEBUG_PRINTF("Successfully loaded %s device\n", module_name);
    return device;
}

static void init_jukebox(void) {
    memset(&g_jukebox, 0, sizeof(g_jukebox));
    g_jukebox.jukebox_position.x = round_to_decimals(random_double(0, ROOM_WIDTH), 2);
    g_jukebox.jukebox_position.y = round_to_decimals(random_double(0, ROOM_WIDTH), 2);

    // Initialize default songs for testing
    g_jukebox.song_count = 0;
    
    // initialize speaker setup
    g_jukebox.speaker_sensitivity = round(random_double(95, 120));
    g_jukebox.amp_wattage = round(random_double(140, 180));
    g_jukebox.volume = round_to_decimals(random_double(0.3, 0.5), 2);
    
    // Create devices
    position_t echooo_pos = { .x = round_to_decimals(random_double(0, ROOM_WIDTH), 2), .y = round_to_decimals(random_double(0, ROOM_HEIGHT), 2)};
    
    device_t *echooo = load_device_module("echooo", "echooo_create", 0, echooo_pos);
    if (echooo) {
        g_jukebox.devices[0] = echooo;
        g_jukebox.device_loaded[0] = true;
    } else {
        g_jukebox.device_loaded[0] = false;
    }

    // Create laptooop device
    position_t laptooop_pos = { .x = round_to_decimals(random_double(0, ROOM_WIDTH), 2), .y = round_to_decimals(random_double(0, ROOM_HEIGHT), 2)};
    
    device_t *laptooop = load_device_module("laptooop", "laptooop_create", 1, laptooop_pos);
    if (laptooop) {
        g_jukebox.devices[1] = laptooop;
        g_jukebox.device_loaded[1] = true;
    } else {
        g_jukebox.device_loaded[1] = false;
    }
    
    // Create microphone device
    position_t mic_pos = { .x = round_to_decimals(random_double(0, ROOM_WIDTH), 2), .y = round_to_decimals(random_double(0, ROOM_HEIGHT), 2)};
    
    device_t *mic = load_device_module("prooodigi", "prooodigi_create", 2, mic_pos);
    if (mic) {
        g_jukebox.devices[2] = mic;
        g_jukebox.device_loaded[2] = true;
    } else {
        g_jukebox.device_loaded[2] = false;
    }
    
    // load in filters
    if (load_filters() == FAIL)
    {
       exit(-1);
    }
    
// This was great for testing but no longer needed    
/* #ifdef DEBUG */
/* #ifdef __APPLE__ */
/*     // Create macOS debug play device */
/*     position_t macos_pos = {10.0, 10.0}; */
/*     device_t *macos_player = macos_play_create(g_jukebox.device_count, macos_pos); */
/*     if (macos_player) { */
/*         g_jukebox.devices[g_jukebox.device_count++] = macos_player; */
/*     } */
/* #endif */
/* #endif */
}

static void print_menu(void) {
    printf("\n=== jukebooox ===\n");
    printf("1. List songs\n");
    printf("2. Play song\n");
    printf("3. Upload song\n");
    printf("4. List devices\n");
    printf("5. Toggle device\n");
    printf("6. Adjust volume\n");
    printf("7. Interact with device\n");
    printf("8. Quit\n");
    printf("Select option: ");
    fflush(stdout);
}

static void list_songs(void) {
    if (g_jukebox.song_count == 0)
    {
       printf("No songs available yet.\n");
       return;
    }

    printf("\nAvailable songs:\n");
    for (uint32_t i = 0; i < g_jukebox.song_count; i++)
    {
       printf("(%d) : ", i+1);
       printf("%s", g_jukebox.songs[i].title);
    }
}

static void play_song(void) {
    if (g_jukebox.song_count == 0) {
        printf("No songs available.\n");
        return;
    }
    
    int song_num = get_user_num("Enter song ID: ");
    if (song_num == -1) {
        printf("Error reading input.\n");
        return;
    }
    if (song_num < 1 || song_num > (int)g_jukebox.song_count) {
        printf("Invalid song ID.\n");
        return;
    }
    
    uint32_t song_id = song_num - 1;
    song_t *song = &g_jukebox.songs[song_id];

    // Check if we can play this song on active devices
    for (uint32_t i = 0; i < MAX_DEVICES; i++) {
       if (!g_jukebox.device_loaded[i])
       {
          continue;
       }
       device_t *device = g_jukebox.devices[i];
       if (device && device->state == DEVICE_ON && device->jukebooox_filter_song) {
          if (device->jukebooox_filter_song(device, song) == FAIL)
          {
             printf("Unable to play song %s because of device %s\n", song->title, device->name);
             return;
          }
       }
    }

    
    printf("Playing: %s\n", song->title);
    printf("Song details: %d samples, %dHz, %d-bit, %d channels\n", 
           (int)song->audio.sample_count, song->audio.frequency, 
           song->audio.bits_per_second, song->audio.channels);
    
    g_jukebox.is_playing = true;
    g_jukebox.current_song_id = song_id;
    
    // Send song audio data to all active devices in chunks
    uint32_t samples_per_chunk = AUDIO_WAVE_SAMPLES;
    uint32_t total_samples = song->audio.sample_count;
    uint32_t samples_sent = 0;
    
    // Calculate total number of chunks
    uint32_t total_chunks = (total_samples + samples_per_chunk - 1) / samples_per_chunk;
    uint32_t current_chunk = 0;
    
    printf("Transmitting song data in chunks of %d samples (%u total chunks)...\n", samples_per_chunk, total_chunks);

    // init the filters for all the devices
    init_all_filters(song->audio.frequency, song->audio.channels);
    
    while (samples_sent < total_samples) {
        // Calculate how many samples to send in this chunk
        uint32_t chunk_size = samples_per_chunk;
        if (samples_sent + chunk_size > total_samples) {
            chunk_size = total_samples - samples_sent;
        }
        
        // Create audio wave for this chunk
        audio_wave_t wave = {0};
        wave.sample_count = chunk_size;
        wave.peak_pa = 1.0;
        wave.timestamp = samples_sent;
        wave.frequency = song->audio.frequency;
        wave.bits_per_sample = song->audio.bits_per_second;
        wave.channels = song->audio.channels;
        
        // Copy song samples to wave
        for (uint32_t i = 0; i < chunk_size && i < AUDIO_WAVE_SAMPLES; i++) {
            if (samples_sent + i < total_samples && song->audio.samples) {
                sample_t sample_32 = song->audio.samples[samples_sent + i];
                wave.samples[i] = sample_32; 
            } else {
                wave.samples[i] = 0;
            }
        }
        
        // Send this chunk to all active devices
        for (uint32_t i = 0; i < MAX_DEVICES; i++) {
           if (!g_jukebox.device_loaded[i])
           {
              continue;
           }
            device_t *device = g_jukebox.devices[i];
            // process filters on chunk
            audio_wave_t processed_wave = {0};
            memcpy(&processed_wave, &wave, sizeof(processed_wave));
            process_filters(device, &processed_wave);
            if (device && device->state == DEVICE_ON && device->process_audio) {
               // calculate the peak_pa based on distance
               double distance = distance_between(g_jukebox.jukebox_position, device->position);
               processed_wave.peak_pa =  compute_pressure_peak_pa(g_jukebox.speaker_sensitivity, g_jukebox.amp_wattage, g_jukebox.volume, distance);
               device->process_audio(device, &processed_wave, current_chunk + 1, total_chunks);
            }
        }
        
        samples_sent += chunk_size;
        current_chunk++;
        printf("Sent chunk %u/%u: %d/%d samples (%.1f%%)\n", 
               current_chunk, total_chunks, samples_sent, total_samples, 
               (float)samples_sent / total_samples * 100.0f);
    }
    
    printf("Finished sending all song data (%d total samples)\n", samples_sent);
    
}


static void upload_song(void) {

   // check that we have a free song in the jukebooox
   if (g_jukebox.song_count >= MAX_SONGS)
   {
      printf("Jukebooox is full\n");
      return;
   }

   uint32_t song_idx = g_jukebox.song_count;

   song_t new_song = {0};

   // Get the name
   printf("Song name: ");
   read(0, new_song.title, MAX_SONG_TITLE - 1);
   new_song.title[MAX_SONG_TITLE - 1] = '\0';

    
   int size_input = get_user_num("Song size: ");
   if (size_input == -1)
   {
      printf("Error\n");
      return;
   }

   uint32_t size = (uint32_t)size_input;

   if (size > MAX_SONG_DATA)
   {
      printf("Song too large\n");
      return;
   }

   void* data = malloc(size);
   
   size_t total_read = 0;
   size_t remaining = size;
   char* buffer_ptr = (char*)data;

   printf("Data: \n");
   while (total_read < size) {
       size_t num_read = read(0, buffer_ptr + total_read, remaining);
       if (num_read <= 0) {
           break;
       }
       total_read += num_read;
       remaining -= num_read;
   }
   
   #ifdef DEBUG
   printf("num_read=%zu\n", total_read);
   #endif
   song_audio_t* song_audio;
   song_audio = parse_wav(size, data);
   if (song_audio == NULL)
   {
      printf("Unable to parse song\n");
      free(data);
      return;
   }
   // free the read in data
   free(data);

   // copy over to the song audio
   memcpy(&new_song.audio, song_audio, sizeof(new_song.audio));
   free(song_audio);

   // calculate the duration_ms
   new_song.duration_ms = calc_duration_ms(&new_song.audio);
   // copy over the new song
   memcpy(&g_jukebox.songs[song_idx], &new_song, sizeof(new_song));
   // increment the song count
   g_jukebox.song_count += 1;
   
}

static void list_devices(void) {
   printf("%.0f watt amp, %.0fdB (1w/1m), %.2f volume\n", g_jukebox.amp_wattage, g_jukebox.speaker_sensitivity, g_jukebox.volume);
   
    printf("\nAvailable devices:\n");
    
    for (uint32_t i = 0; i < MAX_DEVICES; i++) {
       if (!g_jukebox.device_loaded[i])
       {
          continue;
       }
        device_t *device = g_jukebox.devices[i];
        if (device) {
            const char *state_str = "Unknown";
            switch (device->state) {
                case DEVICE_OFF: state_str = "Off"; break;
                case DEVICE_ON: state_str = "On"; break;
                case DEVICE_RECORDING: state_str = "Recording"; break;
                case DEVICE_ERROR: state_str = "Error"; break;
            }
            
            printf("(%d) %s - %s (%.2f, %.2f)\n", 
                   device->device_id + 1, 
                   device->name, 
                   state_str,
                   device->position.x,
                   device->position.y);
            
            // Display filters for this device
            filter_list_t *filter = device->filters;
            if (filter) {
                printf("  Filters:\n");
                while (filter) {
                    const char *type_str = "Unknown";
                    switch (filter->type) {
                        case BIQUAD_LOWPASS: type_str = "Lowpass"; break;
                        case BIQUAD_HIGHPASS: type_str = "Highpass"; break;
                        case BIQUAD_BANDPASS: type_str = "Bandpass"; break;
                        case BIQUAD_NOTCH: type_str = "Notch"; break;
                        case BIQUAD_ALLPASS: type_str = "Allpass"; break;
                        case BIQUAD_PEAKING: type_str = "Peaking"; break;
                        case BIQUAD_LOWSHELF: type_str = "Lowshelf"; break;
                        case BIQUAD_HIGHSHELF: type_str = "Highshelf"; break;
                    }
                    
                    printf("    Type: %s, Frequency: %g Hz, Q: %g, Gain: %g dB\n", 
                           type_str, filter->frequency, filter->Q, filter->gain);
                    filter = filter->next;
                }
            } else {
                printf("  No filters\n");
            }
        }
    }
}

static void toggle_device(void) {
    int device_num = get_user_num("Enter device ID: ");
    if (device_num == -1) {
        printf("Error reading input.\n");
        return;
    }
    if (device_num < 1 || device_num > (int)MAX_DEVICES) {
        printf("Invalid device ID.\n");
        return;
    }

    if (!g_jukebox.device_loaded[device_num - 1])
    {
       printf("Device not loaded.\n");
       return;
    }
    
    device_t *device = g_jukebox.devices[device_num - 1];
    if (!device) {
        printf("Device not found.\n");
        return;
    }
    
    // Toggle device state
    if (device->state == DEVICE_OFF) {
        device->state = DEVICE_ON;
        printf("Device '%s' turned on.\n", device->name);
    } else if (device->state == DEVICE_ON) {
        device->state = DEVICE_OFF;
        printf("Device '%s' turned off.\n", device->name);
    } else {
        printf("Cannot toggle device '%s' (current state: %d).\n", device->name, device->state);
    }
}

static void interact_with_device(void) {
    int device_num = get_user_num("Enter device ID: ");
    if (device_num == -1) {
        printf("Error reading input.\n");
        return;
    }
    if (device_num < 1 || device_num > (int)MAX_DEVICES) {
        printf("Invalid device ID.\n");
        return;
    }

    if (!g_jukebox.device_loaded[device_num - 1])
    {
       printf("Device not loaded.\n");
       return;
    }
    
    device_t *device = g_jukebox.devices[device_num - 1];
    if (!device) {
        printf("Device not found.\n");
        return;
    }
    
    // Check if device is ON and has interaction handler
    if (device->state != DEVICE_ON) {
        printf("Cannot interact with device.\n");
        return;
    }
    
    if (device->device_interact == NULL) {
        printf("Cannot interact with device.\n");
        return;
    }
    
    // Call device-specific interaction function
    device->device_interact(device);
}

static void adjust_volume(void) {
    int volume_level = get_user_num("Enter volume level (0-10): ");
    
    if (volume_level == -1) {
        printf("Error reading input.\n");
        return;
    }
    
    if (volume_level < 0 || volume_level > 11) {
        printf("Invalid volume level. Please enter 0-10.\n");
        return;
    }
    
    // Scale user input to internal volume range
    // Special case: 11 goes to eleven (1.1) - Spinal Tap reference
    g_jukebox.volume = (double)volume_level / 10.0;
}

static bool process_command(command_t cmd) {
    switch (cmd) {
        case CMD_LIST_SONGS:
            list_songs();
            break;
        case CMD_PLAY_SONG:
            play_song();
            break;
        case CMD_UPLOAD_SONG:
            upload_song();
            break;
        case CMD_LIST_DEVICES:
            list_devices();
            break;
        case CMD_TOGGLE_DEVICE:
            toggle_device();
            break;
        case CMD_ADJUST_VOLUME:
            adjust_volume();
            break;
        case CMD_INTERACT_DEVICE:
            interact_with_device();
            break;
        case CMD_QUIT:
            return false;
        default:
            printf("Invalid option!\n");
            return false;
    }
    return true;
}

static int read_flag_and_seed_rand(void) {
    int flag_fd = open("/flag", O_RDONLY);
    if (flag_fd == -1) {
        printf("Error: Could not open /flag file\n");
        return -1;
    }
    
    // Read flag contents (up to 2048 bytes)
    uint8_t flag_buffer[2048];
    ssize_t bytes_read = read(flag_fd, flag_buffer, sizeof(flag_buffer));
    close(flag_fd);
    
    if (bytes_read <= 0) {
        printf("Error: Could not read /flag file\n");
        return -1;
    }
    
    // Compute MD5 hash of flag contents
    uint8_t digest[16];
    md5_hash(flag_buffer, bytes_read, digest);
    
    // Convert first 4 bytes of MD5 hash to uint32_t seed
    uint32_t seed = ((uint32_t)digest[0] << 24) |
                    ((uint32_t)digest[1] << 16) |
                    ((uint32_t)digest[2] << 8) |
                    ((uint32_t)digest[3]);
    
    // Initialize random number generator with the seed
    srand(seed);
    
    // Clear flag content from memory for security
    memset(flag_buffer, 0, sizeof(flag_buffer));
    
    // Access buffer after memset to prevent compiler optimization
    volatile uint32_t checksum = 0;
    for (size_t i = 0; i < sizeof(flag_buffer); i++) {
        checksum += flag_buffer[i];
    }
    (void)checksum; // Suppress unused variable warning
    
    return 0;
}

int main(void) {
    setbuf(stdout, NULL);
    
    // Read flag and seed random number generator
    if (read_flag_and_seed_rand() != 0) {
        return 1;
    }
    
    printf("Welcome to jukebooox!\n");
    printf("Would you like to play a song\n\n");
    
    init_jukebox();

    printf("jukebooox at (%.2f, %.2f)\n", g_jukebox.jukebox_position.x, g_jukebox.jukebox_position.y);
    
    bool running = true;
    
    while (running) {
        print_menu();
        
        int choice = get_user_num("");
        if (choice == -1) {
            break;
        }
        running = process_command((command_t)choice);
    }
    
    printf("\nGoodbye!\n");
    return 0;
}
