#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "key_detection.h"
#include "kiss_fft.h"
#include "kiss_fftr.h"

/* ---------- constants --------------------------------------------- */
const char *KEY_NAMES[KEY_NUMBERS] = {
    "C Major","C# Major","D Major","Eb Major","E Major","F Major","F# Major",
    "G Major","Ab Major","A Major","Bb Major","B Major",
    "C Minor","C# Minor","D Minor","Eb Minor","E Minor","F Minor","F# Minor",
    "G Minor","Ab Minor","A Minor","Bb Minor","B Minor"
};

/* Krumhansl major/minor profiles (C major / C minor) */
const double KR_MAJOR[12] = {6.35,2.23,3.48,2.33,4.38,4.09,2.52,5.19,2.39,3.66,2.29,2.88};
const double KR_MINOR[12] = {6.33,2.68,3.52,5.38,2.60,3.53,2.54,4.75,3.98,2.69,3.34,3.17};

/* Rotate a 12‑element array by 'shift' steps mod 12 into dest */
void rotate_profile(const double *src, double *dest, int shift)
{
    for (int i = 0; i < 12; ++i)
    {
       dest[(i + shift) % 12] = src[i];
    }
}

/* Cosine similarity between two length‑12 vectors */
double cos_similarity(const double *a, const double *b)
{
    double num = 0.0, da = 0.0, db = 0.0;
    for (int i = 0; i < 12; ++i) {
        num += a[i] * b[i];
        da  += a[i] * a[i];
        db  += b[i] * b[i];
    }
    return (da > 0.0 && db > 0.0) ? num / sqrt(da * db) : 0.0;
}

/* Analysis parameters */
#define FRAME (4096)                /* FFT size ‑ power of 2 */
#define HOP   (FRAME / 2)           /* 50 % overlap          */
#define AMP_THRESH (1e-10)               /* noise floor           */


/* ---------- main detector ----------------------------------------- */
int16_t detect_key(const double *samples,
                       size_t        sample_num,
                       double        sample_rate)
{
    if (!samples || sample_num < 2048 || sample_rate <= 0.0)
        return -1;


    /* Hann window */
    static double hann[FRAME];
    static int    hann_init = 0;
    if (!hann_init) {
        for (unsigned i = 0; i < FRAME; ++i)
        {
            hann[i] = 0.5 * (1.0 - cos(2.0 * M_PI * i / (FRAME - 1)));
        }
        hann_init = 1;
    }

    /* KissFFT setup */
    kiss_fftr_cfg cfg = kiss_fftr_alloc(FRAME, 0, NULL, NULL);
    if (!cfg)
    {
       return -1;
    }
    kiss_fft_scalar *in      = malloc(sizeof(kiss_fft_scalar) * FRAME);
    kiss_fft_cpx    *out     = malloc(sizeof(kiss_fft_cpx)   * (FRAME/2 + 1));

    if (!in || !out)
    {
       free(cfg);
       free(in);
       free(out);
       return -1;
    }

    /* Global chroma accumulator */
    double chroma[12] = {0};

    /* Process frames */
    for (size_t pos = 0; pos + FRAME <= sample_num; pos += HOP) {

        /* 1. Copy & window */
        for (unsigned i = 0; i < FRAME; ++i)
        {
            in[i] = (kiss_fft_scalar)(samples[pos + i] * hann[i]);
        }

        /* 2. FFT */
        kiss_fftr(cfg, in, out);

        /* 3. Map spectral bins to chroma classes */
        for (unsigned k = 1; k <= FRAME/2; ++k) {
            double re = out[k].r;
            double im = out[k].i;
            double mag2 = re*re + im*im;
            if (mag2 < AMP_THRESH)
            {
               continue;          /* ignore tiny bins */
            }

            /* Frequency of this bin */
            double freq = (sample_rate * k) / (double)FRAME;
            if (freq < 30.0 || freq > 5000.0)
            {
               continue;
            }

            /* Convert to MIDI note number */
            int midi = (int)round(12.0 * log2(freq / 440.0) + 69.0);
            int pc   = (midi % 12 + 12) % 12;         /* pitch class 0‑11 */

            chroma[pc] += mag2;
        }
    }

    /* Normalise chroma (unit length) */
    double norm = 0.0;
    for (int i = 0; i < 12; ++i)
    {
       norm += chroma[i] * chroma[i];
    }
    norm = (norm > 0.0) ? sqrt(norm) : 1.0;

    for (int i = 0; i < 12; ++i) {
       chroma[i] /= norm;
    }

    /* 4. Compare to rotated profiles */
    double best_sim   = -1.0;
    int    best_index = -1;
    double profile[12];

    for (int tonic = 0; tonic < 12; ++tonic) {
        /* Major */
        rotate_profile(KR_MAJOR, profile, tonic);
        double sim = cos_similarity(chroma, profile);
        if (sim > best_sim)
        {
           #ifdef DEBUG
           printf("Major key: old_best=%d new_best=%d\n", best_sim, sim);
           #endif

           best_sim = sim;
           best_index = tonic;
        }

        /* Minor */
        rotate_profile(KR_MINOR, profile, tonic);
        sim = cos_similarity(chroma, profile);
        if (sim > best_sim)
        {
           #ifdef DEBUG
           printf("Minor key: old_best=%f new_best=%f\n", best_sim, sim);
           #endif

           best_sim = sim;
           best_index = tonic;

           best_sim = sim;
           best_index = 12 + tonic;
           #ifdef DEBUG
           printf("new best = %s\n", KEY_NAMES[best_index]);
           #endif

        }
    }

    /* Cleanup */
    free(cfg); free(in); free(out);

    /* Confidence threshold (optional) */
    if (best_sim < 0.3)
    {
       return -1;
    }

    return best_index;
}
