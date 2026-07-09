#ifndef LAPTOOOP_H
#define LAPTOOOP_H

#include "common.h"

#define NUM_PLATTERS 32
#define PLATTER_SIZE 32768
#define HDD_MIN_RPM 5400
#define HDD_MAX_RPM 7200
#define HDD_ACTUATOR_RESONANT_FREQ 5000.0  // Hz, typical actuator resonance
#define HDD_SHOCK_SENSOR_RESONANT_FREQ 1000.0  // Hz, typical shock sensor resonance
#define HDD_SHOCK_PARK_DURATION_MS 100.0   // Duration heads stay parked after shock
#define HDD_MAX_POSITIONING_ERROR 0.1      // Maximum allowable positioning error
#define HDD_POSITIONING_THRESHOLD_M 7.5e-9  // Blue Note paper: 7.5nm positioning threshold
#define HDD_ACTUATOR_STROKE_LENGTH_M 0.05    // Typical actuator stroke length in meters (50mm)

#define HDD_WRITE_ERROR_LIMIT 16

// Laptooop microphone default parameters
#define LAPTOOOP_MIC_ANALOG_GAIN 1.2        // Front-end analog gain (slightly lower than echooo)
#define LAPTOOOP_MIC_NOISE_FLOOR 0.002      // Background noise level (laptop has more noise)
#define LAPTOOOP_MIC_SATURATION_THRESHOLD 0.85  // Saturation point (laptop mic saturates easier)
#define LAPTOOOP_MIC_NONLINEAR_A1 0.94      // Linear coefficient
#define LAPTOOOP_MIC_NONLINEAR_A2 0.04      // Quadratic coefficient  
#define LAPTOOOP_MIC_NONLINEAR_A3 0.02      // Cubic coefficient (more distortion)
#define LAPTOOOP_MIC_LOWPASS_FREQ 20000.0    // Low-pass filter cutoff for music (Hz)
#define LAPTOOOP_MIC_LOWPASS_Q 0.707        // Low-pass filter Q factor
#define LAPTOOOP_MIC_HIGHPASS_FREQ 20.0    // High-pass filter cutoff for music (Hz)
#define LAPTOOOP_MIC_HIGHPASS_Q 0.707       // High-pass filter Q factor

#define LAPTOOOP_MAX_FREQUENCY 192000

typedef struct {
   /* mechanical parameters */
   double f0;          /* Hz   – natural frequency              */
   double Q;           /* –    – quality factor                 */
   double mass;        /* kg   – arbitrary scale                */
   double coupling;    /* N/Pa – pressure → force gain          */

   /* mechanical state */
   double x;           /* m      – displacement                   */
   double v;           /* m/s    – velocity                       */
   double a;           /* m/s^2  – acceleration                   */  

   bool active;  // If this resonance analysis is active (only if the audio input frequency is within nyquist

   /* biquad */
   biquad_t biquad;
} Mode;


typedef struct {
   double position;           // Current head position (0.0 to 1.0 across platter)
   double target_position;    // Target position for seek operations   
   uint64_t last_seek_time;   // Timestamp of last seek operation
   bool is_seeking;           // Currently performing seek operation
#define ARM_RESONANCE_NUM 4
   Mode resonance[ARM_RESONANCE_NUM];         // Actuator arm has about 4 different resonance peaks within the audiable range
} actuator_arm_t;

typedef struct {
   bool head_parked;          // Whether heads are currently parked due to shock
   double remaining_park_duration_ms;   // How much longer heads remain parked after shock
   double park_duration_ms;   // How long heads remain parked after shock
#define SHOCK_RESONANCE_NUM 2
   Mode resonance[SHOCK_RESONANCE_NUM];         // shock sensors cause a loss in the inaudiable range (seems to be roughly two peaks)
} shock_sensor_t;
   

typedef enum {
   HDD_STATUS_IDLE = 0,
   HDD_STATUS_SEEKING,
   HDD_STATUS_READING,
   HDD_STATUS_WRITING,
   HDD_STATUS_ERROR,
   HDD_STATUS_PARKED
} hdd_status_t;

typedef struct {
   uint8_t*  platters[NUM_PLATTERS];
   struct hdd_t* self;
   void (*hdd_clear_data_func)(void *hdd);
   actuator_arm_t arm;        // Single actuator arm for all platters
   shock_sensor_t sensor;     // Shock sensor
   // NOTE: we're not going to do sectors and all that, this is a special hard drive that allows us to write at the byte level
   uint32_t current_platter;   // the idx of the current platter that's free
   uint32_t current_free_byte; // the idx in the platter of the next byte that's free
   uint64_t num_bytes_written; // number of bytes written
   bool powered;
   hdd_status_t status;
   uint32_t write_errors;     // Count of write errors 
} hdd_t;

typedef struct {
   // Analog front-end parameters
   double analog_gain;           // Front-end analog gain multiplier
   double noise_floor;           // Background noise level to add
   
   // Saturation/non-linearity parameters
   double saturation_threshold;  // Point where saturation begins
   double nonlinear_a1;         // Linear coefficient for saturation
   double nonlinear_a2;         // Quadratic coefficient for saturation  
   double nonlinear_a3;         // Cubic coefficient for saturation
   
   // Filter parameters
   double lowpass_freq;         // Low-pass filter cutoff frequency (Hz)
   double lowpass_q;            // Low-pass filter Q factor
   double highpass_freq;        // High-pass filter cutoff frequency (Hz)
   double highpass_q;           // High-pass filter Q factor
   
   // Filter state (dynamic channel support)
   biquad_t *lowpass_filters;   // Low-pass biquad filters per channel (dynamically allocated)
   biquad_t *highpass_filters;  // High-pass biquad filters per channel (dynamically allocated)
   uint16_t num_channels;       // Number of channels currently allocated
   bool filters_initialized;    // Whether filters have been initialized
   uint32_t last_sample_rate;   // Last sample rate used for filter init
   
   // Microphone characteristics
   double sensitivity;          // Overall microphone sensitivity
   bool powered;               // Whether microphone is powered on
} microphone_t;

typedef struct {
   hdd_t* hdd;                   // Pointer to HDD simulation
   microphone_t mic;       // Embedded microphone for audio capture
   bool laptop_powered;          // Overall laptop power state
   double chassis_resonance;     // Chassis resonant frequency
   uint64_t boot_time;          // When laptop was powered on
   char model_name[32];         // Laptop model identifier
   uint16_t recording_bps;
   uint32_t recording_frequency;
   uint16_t recording_channels;
} laptooop_state_t;

// Device management functions
device_t *laptooop_create(uint32_t device_id, position_t pos);
void laptooop_destroy(device_t *device);

#endif
