#ifndef KEY_DETECTION_H
#define KEY_DETECTION_H

#define KEY_NUMBERS 24

extern const char* KEY_NAMES[KEY_NUMBERS];

int16_t detect_key(const double *samples,
                       size_t        sample_num,
                       double        sample_rate);

#endif /* KEY_DETECTION */
