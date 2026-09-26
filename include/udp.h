#ifndef UDP_H
#define UDP_H

#include <stdint.h>
#include <stddef.h>


//Creates a sender 
int udp_createSender(const char *IP, uint16_t port);

//Sends the data to particular port 
int udp_send(int sockfd, const void *data,size_t size);

//Creates a receiver
int udp_createReceiver(uint16_t port);

//Receives the data from other end
int udp_receive(int sockfd, void *buffer, size_t buffer_size);

//Closes the socket file descriptor
void udp_close(int sockfd);

#endif