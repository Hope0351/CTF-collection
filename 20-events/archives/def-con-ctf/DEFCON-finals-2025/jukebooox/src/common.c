#include "common.h"
#include <math.h>
#include <stdlib.h>

uint32_t calc_duration_ms(const song_audio_t* song) {
    if (!song || song->frequency == 0) {
        return 0;
    }
    
    // Duration in milliseconds = (sample_count / frequency) * 1000
    uint64_t duration_ms = (song->sample_count * 1000) / song->frequency;
    
    // Return as uint32_t, capping at max value if needed
    return (uint32_t)(duration_ms > UINT32_MAX ? UINT32_MAX : duration_ms);
}

sample_t clip_sample(sample_t sample, uint16_t bps)
{
   if (bps != 8)
   {
      int64_t max = (1LL << (bps - 1)) - 1;
      int64_t min = -(1LL << (bps - 1));
   
      if (sample > max)
      {
         return (sample_t)max;
      }
      else if (sample < min)
      {
         return (sample_t)min;
      }
      else
      {
         return sample;
      }
   }
   else
   {
      return sample;
   }
}

void* convert_from_internal_to_wav_samples(const sample_t* samples, uint32_t sample_count, uint16_t current_bits_per_sample, uint16_t desired_bits_per_sample)
{
   size_t desired_convert_bytes = sample_count * (desired_bits_per_sample / 8);
   void* to_return = calloc(1, desired_convert_bytes);

   for(uint32_t i = 0; i < sample_count; i++)
   {
      sample_t clipped_sample = clip_sample(samples[i], current_bits_per_sample);
      if (current_bits_per_sample == 8 && desired_bits_per_sample != 8)
      {
         clipped_sample = (uint8_t)clipped_sample - 128;
      }

      // Scale sample from current_bits_per_sample to desired_bits_per_sample
      sample_t scaled_sample = clipped_sample;
      if (current_bits_per_sample != desired_bits_per_sample) {
         if (current_bits_per_sample < desired_bits_per_sample) {
            // Upscaling: shift left by the difference in bits
            uint16_t shift = desired_bits_per_sample - current_bits_per_sample;
            scaled_sample = clipped_sample << shift;
         } else {
            // Downscaling: shift right by the difference in bits
            uint16_t shift = current_bits_per_sample - desired_bits_per_sample;
            scaled_sample = clipped_sample >> shift;
         }
      }

      if (desired_bits_per_sample == 8)
      {
         if (current_bits_per_sample != 8)
         {
            ((uint8_t*)to_return)[i] = (uint8_t)scaled_sample + 128;
         }
         else
         {
            ((uint8_t*)to_return)[i] = (uint8_t)scaled_sample;
         }
      }
      else if (desired_bits_per_sample == 16)
      {
         // printf("%d to %d to %d\n", samples[i], clipped_sample, (int16_t)scaled_sample);
         ((int16_t*)to_return)[i] = (int16_t)scaled_sample;
      }
      else if (desired_bits_per_sample == 32)
      {
         ((int32_t*)to_return)[i] = scaled_sample;
      }
   }

   return to_return;
}

void biquad_lowpass(biquad_t* filter, double frequency, double sample_rate, double Q) {
    double omega = 2.0 * M_PI * frequency / sample_rate;
    double sin_omega = sin(omega);
    double cos_omega = cos(omega);
    double alpha = sin_omega / (2.0 * Q);
    
    double a0 = 1.0 + alpha;
    filter->b0 = (1.0 - cos_omega) / 2.0 / a0;
    filter->b1 = (1.0 - cos_omega) / a0;
    filter->b2 = (1.0 - cos_omega) / 2.0 / a0;
    filter->a1 = -2.0 * cos_omega / a0;
    filter->a2 = (1.0 - alpha) / a0;
    
    biquad_reset(filter);
}

void biquad_highpass(biquad_t* filter, double frequency, double sample_rate, double Q) {
    double omega = 2.0 * M_PI * frequency / sample_rate;
    double sin_omega = sin(omega);
    double cos_omega = cos(omega);
    double alpha = sin_omega / (2.0 * Q);
    
    double a0 = 1.0 + alpha;
    filter->b0 = (1.0 + cos_omega) / 2.0 / a0;
    filter->b1 = -(1.0 + cos_omega) / a0;
    filter->b2 = (1.0 + cos_omega) / 2.0 / a0;
    filter->a1 = -2.0 * cos_omega / a0;
    filter->a2 = (1.0 - alpha) / a0;
    
    biquad_reset(filter);
}

void biquad_bandpass(biquad_t* filter, double frequency, double sample_rate, double Q) {
    double omega = 2.0 * M_PI * frequency / sample_rate;
    double sin_omega = sin(omega);
    double cos_omega = cos(omega);
    double alpha = sin_omega / (2.0 * Q);
    
    double a0 = 1.0 + alpha;
    filter->b0 = alpha / a0;
    filter->b1 = 0.0;
    filter->b2 = -alpha / a0;
    filter->a1 = -2.0 * cos_omega / a0;
    filter->a2 = (1.0 - alpha) / a0;
    
    biquad_reset(filter);
}

void biquad_notch(biquad_t* filter, double frequency, double sample_rate, double Q) {
    double omega = 2.0 * M_PI * frequency / sample_rate;
    double sin_omega = sin(omega);
    double cos_omega = cos(omega);
    double alpha = sin_omega / (2.0 * Q);
    
    double a0 = 1.0 + alpha;
    filter->b0 = 1.0 / a0;
    filter->b1 = -2.0 * cos_omega / a0;
    filter->b2 = 1.0 / a0;
    filter->a1 = -2.0 * cos_omega / a0;
    filter->a2 = (1.0 - alpha) / a0;
    
    biquad_reset(filter);
}

void biquad_allpass(biquad_t* filter, double frequency, double sample_rate, double Q) {
    double omega = 2.0 * M_PI * frequency / sample_rate;
    double sin_omega = sin(omega);
    double cos_omega = cos(omega);
    double alpha = sin_omega / (2.0 * Q);
    
    double a0 = 1.0 + alpha;
    filter->b0 = (1.0 - alpha) / a0;
    filter->b1 = -2.0 * cos_omega / a0;
    filter->b2 = (1.0 + alpha) / a0;
    filter->a1 = -2.0 * cos_omega / a0;
    filter->a2 = (1.0 - alpha) / a0;
    
    biquad_reset(filter);
}

void biquad_peaking(biquad_t* filter, double frequency, double sample_rate, double Q, double gain) {
    double omega = 2.0 * M_PI * frequency / sample_rate;
    double sin_omega = sin(omega);
    double cos_omega = cos(omega);
    double alpha = sin_omega / (2.0 * Q);
    double A = pow(10.0, gain / 40.0);
    
    double a0 = 1.0 + alpha / A;
    filter->b0 = (1.0 + alpha * A) / a0;
    filter->b1 = -2.0 * cos_omega / a0;
    filter->b2 = (1.0 - alpha * A) / a0;
    filter->a1 = -2.0 * cos_omega / a0;
    filter->a2 = (1.0 - alpha / A) / a0;
    
    biquad_reset(filter);
}

void biquad_lowshelf(biquad_t* filter, double frequency, double sample_rate, double Q, double gain) {
    double omega = 2.0 * M_PI * frequency / sample_rate;
    double sin_omega = sin(omega);
    double cos_omega = cos(omega);
    double A = pow(10.0, gain / 40.0);
    double beta = sqrt(A) / Q;
    
    double a0 = (A + 1.0) + (A - 1.0) * cos_omega + beta * sin_omega;
    filter->b0 = (A * ((A + 1.0) - (A - 1.0) * cos_omega + beta * sin_omega)) / a0;
    filter->b1 = (2.0 * A * ((A - 1.0) - (A + 1.0) * cos_omega)) / a0;
    filter->b2 = (A * ((A + 1.0) - (A - 1.0) * cos_omega - beta * sin_omega)) / a0;
    filter->a1 = (-2.0 * ((A - 1.0) + (A + 1.0) * cos_omega)) / a0;
    filter->a2 = ((A + 1.0) + (A - 1.0) * cos_omega - beta * sin_omega) / a0;
    
    biquad_reset(filter);
}

void biquad_highshelf(biquad_t* filter, double frequency, double sample_rate, double Q, double gain) {
    double omega = 2.0 * M_PI * frequency / sample_rate;
    double sin_omega = sin(omega);
    double cos_omega = cos(omega);
    double A = pow(10.0, gain / 40.0);
    double beta = sqrt(A) / Q;
    
    double a0 = (A + 1.0) - (A - 1.0) * cos_omega + beta * sin_omega;
    filter->b0 = (A * ((A + 1.0) + (A - 1.0) * cos_omega + beta * sin_omega)) / a0;
    filter->b1 = (-2.0 * A * ((A - 1.0) + (A + 1.0) * cos_omega)) / a0;
    filter->b2 = (A * ((A + 1.0) + (A - 1.0) * cos_omega - beta * sin_omega)) / a0;
    filter->a1 = (2.0 * ((A - 1.0) - (A + 1.0) * cos_omega)) / a0;
    filter->a2 = ((A + 1.0) - (A - 1.0) * cos_omega - beta * sin_omega) / a0;
    
    biquad_reset(filter);
}


double biquad_process(biquad_t* filter, double input) {
    double output = filter->b0 * input + filter->b1 * filter->x1 + filter->b2 * filter->x2 
                   - filter->a1 * filter->y1 - filter->a2 * filter->y2;
    
    // Update delay lines
    filter->x2 = filter->x1;
    filter->x1 = input;
    filter->y2 = filter->y1;
    filter->y1 = output;
    
    return output;
}

void biquad_reset(biquad_t* filter) {
    filter->x1 = filter->x2 = 0.0;
    filter->y1 = filter->y2 = 0.0;
}

void biquad_init(biquad_t* filter, biquad_type_t type, double frequency, double sample_rate, double Q, double gain)
{
    switch (type) {
        case BIQUAD_LOWPASS:
            biquad_lowpass(filter, frequency, sample_rate, Q);
            break;
        case BIQUAD_HIGHPASS:
            biquad_highpass(filter, frequency, sample_rate, Q);
            break;
        case BIQUAD_BANDPASS:
            biquad_bandpass(filter, frequency, sample_rate, Q);
            break;
        case BIQUAD_NOTCH:
            biquad_notch(filter, frequency, sample_rate, Q);
            break;
        case BIQUAD_ALLPASS:
            biquad_allpass(filter, frequency, sample_rate, Q);
            break;
        case BIQUAD_PEAKING:
            biquad_peaking(filter, frequency, sample_rate, Q, gain);
            break;
        case BIQUAD_LOWSHELF:
            biquad_lowshelf(filter, frequency, sample_rate, Q, gain);
            break;
        case BIQUAD_HIGHSHELF:
            biquad_highshelf(filter, frequency, sample_rate, Q, gain);
            break;
        default:
            biquad_reset(filter);
            break;
    }
}

double sample_to_normalized_double(sample_t sample, uint16_t bits_per_sample) {
    if (bits_per_sample == 8) {
        // 8-bit samples are unsigned (0-255), convert to signed range (-1 to 1)
        return ((double)(uint8_t)sample - 128.0) / 128.0;
    } else {
        // 16-bit and 32-bit samples are signed, normalize to (-1 to 1)
        return (double)sample / (double)(1LL << (bits_per_sample - 1));
    }
}

sample_t normalized_double_to_sample(double normalized_sample, uint16_t bits_per_sample) {
    if (bits_per_sample == 8) {
        // Convert back to 8-bit unsigned (0-255)
        double unsigned_sample = normalized_sample * 128.0 + 128.0;
        if (unsigned_sample > 255.0) unsigned_sample = 255.0;
        if (unsigned_sample < 0.0) unsigned_sample = 0.0;
        return (sample_t)(uint8_t)unsigned_sample;
    } else {
        // Convert back to signed format for 16-bit and 32-bit
        sample_t output_sample = (sample_t)(normalized_sample * (double)(1LL << (bits_per_sample - 1)));
        
        // Clamp to valid range for signed samples
        sample_t max_val = (1LL << (bits_per_sample - 1)) - 1;
        sample_t min_val = -(1LL << (bits_per_sample - 1));
        
        if (output_sample > max_val) output_sample = max_val;
        if (output_sample < min_val) output_sample = min_val;
        
        return output_sample;
    }
}


char* get_env_or_default(const char* env_var, const char* default_value) {
    char* value = getenv(env_var);
    return value ? value : (char*)default_value;
}

int get_user_num(const char* prompt) {
    char input[32];
    printf("%s", prompt);
    fflush(stdout);
    
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return -1;
    }
    
    return atoi(input);
}

double microphone_apply_analog_gain(double sample, double gain) {
    return sample * gain;
}

double microphone_add_noise_floor(double sample, double noise_floor) {
    double noise = ((double)rand() / RAND_MAX - 0.5) * noise_floor;
    return sample + noise;
}

double microphone_apply_saturation(double sample, double threshold, double a1, double a2, double a3) {
    if (fabs(sample) > threshold) {
        return (sample > 0) ? threshold : -threshold;
    } else {
        return a1 * sample + a2 * sample * sample + a3 * sample * sample * sample;
    }
}

double round_to_decimals(double value, int decimals) {
    double factor = pow(10.0, decimals);
    return round(value * factor) / factor;
}

double random_double(double min, double max) {
    if (min >= max) return min;  // edge case: return min if range is invalid
    return min + (max - min) * ((double)rand() / (RAND_MAX + 1.0));
}
