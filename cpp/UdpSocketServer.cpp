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

    bzero((char *) &_serveraddr, sizeof(_serveraddr));
    _serveraddr.sin_family = AF_INET;
    _serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    _serveraddr.sin_port = htons(port);

    if (bind(_sockfd, (struct sockaddr *) &_serveraddr, sizeof(_serveraddr)) < 0) {
        error("ERROR on binding");
    }
}

void UdpSocketServer::receiveData(char  * buf, size_t len)
{
    int n = recvfrom(_sockfd, buf, len, 0, (struct sockaddr *) &_clientaddr, &_clientlen);
    printf("server received %d/%d bytes: %s\n", (int)strlen(buf), n, buf);
}

void UdpSocketServer::sendData(char * buf, size_t len)
{
    if (sendto(_sockfd, buf, strlen(buf), 0, (struct sockaddr *) &_clientaddr, _clientlen) < 0)  {
        error("ERROR in sendto");
    }
}
