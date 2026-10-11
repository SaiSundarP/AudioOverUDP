#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <stdint.h>

#define AUDIO_PORT 5000
#define AUDIO_DATA_SIZE 1024
#define AUDIO_MAGIC 0x41554450

///@brief Structure that defines the audio header with magic no, sequence, data_size
typedef struct AudioPacketHeader{
    uint32_t magic;
    uint32_t sequence;
    uint32_t data_size;
}AudioPacketHeader;

#endif