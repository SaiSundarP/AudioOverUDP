#include "audio.h"
#include "protocol.h"
#include "udp.h"

#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    FILE *audio_file;

    int sockfd;

    unsigned char audio_buffer[AUDIO_DATA_SIZE];

    unsigned char packet[
        sizeof(AudioPacketHeader) + AUDIO_DATA_SIZE
    ];

    AudioPacketHeader header;

    WavInfo wav;

    size_t bytes_read;

    uint32_t sequence = 0;

    if (argc != 3)
    {
        printf("Usage: %s <wav_file> <receiver_ip>\n", argv[0]);
        return 1;
    }

    audio_file = fopen(argv[1], "rb");

    if (audio_file == NULL)
    {
        perror("fopen");
        return 1;
    }

    if (wav_read_header(audio_file, &wav) != 0)
    {
        printf("Invalid WAV file\n");
        fclose(audio_file);
        return 1;
    }

    printf("WAV information:\n");
    printf("Channels       : %u\n", wav.channels);
    printf("Sample rate    : %u Hz\n", wav.sample_rate);
    printf("Bits/sample    : %u\n", wav.bits_per_sample);
    printf("Data size      : %u bytes\n", wav.data_size);

    sockfd = udp_createSender(argv[2],AUDIO_PORT);

    if (sockfd < 0)
    {
        fclose(audio_file);
        return 1;
    }

    while ((bytes_read =
            fread(audio_buffer,1,AUDIO_DATA_SIZE,audio_file)) > 0)
    {
        header.magic = htonl(AUDIO_MAGIC);

        header.sequence = htonl(sequence++);

        header.data_size = htons((uint16_t)bytes_read);

        memcpy(packet,&header,sizeof(header));

        memcpy(packet + sizeof(header),audio_buffer,bytes_read);

        if (udp_send(sockfd, packet, sizeof(header) + bytes_read) < 0)
        {
            perror("send");
            udp_close(sockfd);
            fclose(audio_file);
            return 1;
        }

        printf("\rSent packet: %u",sequence);

        fflush(stdout);
    }

    printf("\nTransmission complete.\n");

    udp_close(sockfd);

    fclose(audio_file);

    return 0;
}