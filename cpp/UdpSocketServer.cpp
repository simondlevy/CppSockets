/*
 * UDP SocketServer.cpp: general-purpose TCP socket server code
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
        error("ERROR on binding");
    }
}

bool UdpSocketServer::sendData(char * buf, size_t len)
{
    return (size_t)sendto(_sockfd, buf, strlen(buf), 0, (struct sockaddr *) &_clientaddr, _clientlen) == len;
}

bool UdpSocketServer::receiveData(char  * buf, size_t len)
{
    return (size_t)recvfrom(_sockfd, buf, len, 0, (struct sockaddr *) &_clientaddr, &_clientlen) == len;
}


