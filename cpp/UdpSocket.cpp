/*
 * UDP Socket.cpp: general-purpose UDP socket code
 *
 * Copyright (C) 2019 Simon D. Levy
 *
 * MIT License
 */

#include "UdpSocket.h"

UdpSocket::UdpSocket(const char * host, short port)
{
    *_message = 0;

    _sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (_sockfd < 0) {
        sprintf(_message, "ERROR opening socket");
        return;
    }

    bzero((char *) &_serveraddr, sizeof(_serveraddr));
    _serveraddr.sin_family = AF_INET;
    _serveraddr.sin_port = htons(port);
}

bool UdpSocket::sendData(void * buf, size_t len, struct sockaddr_in * addr, unsigned int addrlen)
{
    return (size_t)sendto(_sockfd, buf, len, 0, (struct sockaddr *)addr, addrlen) == len;
}

bool UdpSocket::receiveData(void * buf, size_t len, struct sockaddr_in * addr, unsigned int * addrlen)
{
    return (size_t)recvfrom(_sockfd, buf, len, 0, (struct sockaddr *)addr, addrlen) == len;
}
