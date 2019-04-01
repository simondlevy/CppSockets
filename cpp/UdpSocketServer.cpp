/*
 * UDP SocketServer.cpp: general-purpose UDP socket server code
 *
 * Copyright (C) 2019 Simon D. Levy
 *
 * MIT License
 */

#include "UdpSocketServer.h"

UdpSocketServer::UdpSocketServer(const char * host, short port) : UdpSocket(host, port)
{
    int optval = 1;
    setsockopt(_sockfd, SOL_SOCKET, SO_REUSEADDR, (const void *)&optval , sizeof(int));

    _serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(_sockfd, (struct sockaddr *) &_serveraddr, sizeof(_serveraddr)) < 0) {
        sprintf(_message, "ERROR on binding");
    }
}

bool UdpSocketServer::sendData(void * buf, size_t len)
{
    return UdpSocket::sendData(buf, len, &_clientaddr, _clientlen);
}

bool UdpSocketServer::receiveData(void * buf, size_t len)
{
    return UdpSocket::receiveData(buf, len, &_clientaddr, &_clientlen);
}
