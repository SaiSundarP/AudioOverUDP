#include "audio.h"

#include <stdio.h>
#include <string.h>

static uint32_t read_u32_le(const unsigned char *buffer)
{
    return ((uint32_t)buffer[0]) | ((uint32_t)buffer[1] << 8) | ((uint32_t)buffer[2] << 16) | ((uint32_t)buffer[3] << 24);
}

static uint16_t read_u16_le(const unsigned char *buffer)
{
    return ((uint16_t)buffer[0]) | ((uint16_t)buffer[1] << 8);
}

int wav_read_header(FILE *file, WavInfo *info)
{
    unsigned char header[44];

    if (fread(header, 1, sizeof(header), file) != sizeof(header))
    {
        return -1;
    }

    if (memcmp(header, "RIFF", 4) != 0)
    {
        return -1;
    }

    if (memcmp(header + 8, "WAVE", 4) != 0)
    {
        return -1;
    }

    if (memcmp(header + 12, "fmt ", 4) != 0)
    {
        return -1;
    }

    info->audio_format = read_u16_le(&header[20]);

    info->channels = read_u16_le(&header[22]);

    info->sample_rate = read_u32_le(&header[24]);

    info->byte_rate = read_u32_le(&header[28]);

    info->block_align = read_u16_le(&header[32]);

    info->bits_per_sample = read_u16_le(&header[34]);

    if (memcmp(header + 36, "data", 4) != 0)
    {
        return -1;
    }

    info->data_size = read_u32_le(&header[40]);

    return 0;
}