#ifndef AUDIO_H
#define AUDIO_H

#include <stdint.h>
#include <stdio.h>

/// @brief Structure that defines the WAV file header information
typedef struct
{
    uint16_t audio_format;
    uint16_t channels;
    uint32_t sample_rate;
    uint32_t byte_rate;
    uint16_t block_align;
    uint16_t bits_per_sample;
    uint32_t data_size;
} WavInfo;

int wav_read_header(FILE *file, WavInfo *info);

#endif