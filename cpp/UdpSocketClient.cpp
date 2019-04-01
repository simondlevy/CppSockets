/*
 * UdpSocketClient.cpp: Class for UDP socket clients
 *
 * Copyright (C) 2019 Simon D. Levy
 *
 * MIT License
 */

#include "UdpSocketClient.h"

void UdpSocketClient::error(const char * msg)
{
    fprintf(stderr, "%s\n", msg);
    exit(1);
}

UdpSocketClient::UdpSocketClient(const char * host, short port)
{
    _sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (_sockfd < 0) {
        error("ERROR opening socket");
    }

    struct hostent * server = gethostbyname(host);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host as %s\n", host);
        exit(0);
    }

    bzero((char *) &_serveraddr, sizeof(_serveraddr));
    _serveraddr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&_serveraddr.sin_addr.s_addr, server->h_length);
    _serveraddr.sin_port = htons(port);
}

bool UdpSocketClient::sendData(char *buf, size_t len)
{
    return (size_t)sendto(_sockfd, buf, strlen(buf), 0, (const sockaddr *)&_serveraddr, _serverlen) == len;
}

bool UdpSocketClient::receiveData(char *buf, size_t len)
{
    return (size_t)recvfrom(_sockfd, buf, strlen(buf), 0, (sockaddr *)&_serveraddr, &_serverlen) == len;
}
