#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>  
#include <unistd.h>
#include "udp.h"



int udp_createSender(const char *IP, uint16_t port){
    int sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    struct sockaddr_in address;

    if (sockfd < 0)
    {
        perror("socket");
        return -1;
    }

    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_port = htons(port);

    if (inet_pton(AF_INET, IP, &address.sin_addr) != 1)
    {
        fprintf(stderr, "Invalid IPv4 address: %s\n", IP);
        close(sockfd);
        return -1;
    }

    if (connect(sockfd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("connect");
        close(sockfd);
        return -1;
    }

    return sockfd;
}

int udp_send(int sockfd, const void *data, size_t size){
    return (int)send(sockfd, data,size, 0);
}

int udp_createReceiver(uint16_t port){
    int sockfd;
    struct sockaddr_in address;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    if (sockfd < 0)
    {
        perror("socket");
        return -1;
    }

    memset(&address, 0, sizeof(address));

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(sockfd,
             (struct sockaddr *)&address,sizeof(address)) < 0)
    {
        perror("bind");
        close(sockfd);
        return -1;
    }

    return sockfd;
}

int udp_receive(int sockfd,void *buffer,size_t buffer_size)
{
    return (int)recv(sockfd, buffer, buffer_size, 0);
}

void udp_close(int sockfd)
{
    close(sockfd);
}
