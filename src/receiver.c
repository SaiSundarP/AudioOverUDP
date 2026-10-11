#include "protocol.h"
#include "udp.h"

#include <arpa/inet.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

int main(void)
{
    int sockfd;

    FILE *output;

    unsigned char packet[
        sizeof(AudioPacketHeader) + AUDIO_DATA_SIZE
    ];

    sockfd = udp_createReceiver(AUDIO_PORT);

    if (sockfd < 0)
    {
        return 1;
    }

    output = fopen("audio/output.pcm", "wb");

    if (output == NULL)
    {
        perror("fopen");
        udp_close(sockfd);
        return 1;
    }

    printf("Waiting for UDP audio...\n");

    while (1)
    {
        int bytes_received;

        AudioPacketHeader header;

        bytes_received =udp_receive(sockfd,packet,sizeof(packet));

        if (bytes_received < 0)
        {
            perror("recv");
            break;
        }

        if (bytes_received <
            (int)sizeof(AudioPacketHeader))
        {
            continue;
        }

        memcpy(&header,packet,sizeof(header));

        header.magic =ntohl(header.magic);

        header.sequence =ntohl(header.sequence);

        header.data_size =ntohs(header.data_size);

        if (header.magic != AUDIO_MAGIC)
        {
            printf("Invalid packet\n");
            continue;
        }

        printf("\rReceived packet: %u",header.sequence);

        fflush(stdout);

        fwrite(packet + sizeof(AudioPacketHeader),1,header.data_size,output);
    }

    fclose(output);

    udp_close(sockfd);

    return 0;
}