#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <stdint.h>

#define audio_port 5000
#define audio_size 1024
#define audio_magic 0x41554450

//Structure that defines the audio header with magic no, sequence, data_size
typedef struct AudioPacketHeader{
    uint32_t magic;
    uint32_t sequence;
    uint32_t data_size;
}AudioPacketHeader;

#endif