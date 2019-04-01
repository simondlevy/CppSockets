/*
 * UdpSocketClient.cpp: Class for UDP socket clients
 *
 * Copyright (C) 2019 Simon D. Levy
 *
 * MIT License
 */

#include "UdpSocketClient.h"

UdpSocketClient::UdpSocketClient(const char * host, short port) : UdpSocket(host, port)
{
    struct hostent * server = gethostbyname(host);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host as %s\n", host);
        exit(0);
    }

    bcopy((char *)server->h_addr, (char *)&_serveraddr.sin_addr.s_addr, server->h_length);
}

bool UdpSocketClient::sendData(void * buf, size_t len)
{
    return UdpSocket::sendData(buf, len, &_serveraddr, _serverlen);
}

bool UdpSocketClient::receiveData(void * buf, size_t len)
{
    return UdpSocket::receiveData(buf, len, &_serveraddr, &_serverlen);
}
