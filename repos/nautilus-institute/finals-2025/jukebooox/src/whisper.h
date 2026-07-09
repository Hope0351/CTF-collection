#ifndef WHISPER_H
#define WHISPER_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#include "common.h"

char** whisper_transcribe(const char* wav_data, size_t size);

#endif // WHISPER_H
