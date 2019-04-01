/*
 * UDP SocketServer.cpp: general-purpose TCP socket server code
 *
 * Copyright (C) 2019 Simon D. Levy
 *
 * MIT License
 */

#include "UdpSocketServer.h"

UdpSocketServer::UdpSocketServer(const char * host, short port)
{
    _sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (_sockfd < 0) {
        error("ERROR opening socket");
    }

    // setsockopt: Handy debugging trick that lets 
    // us rerun the server immediately after we kill it; 
    // otherwise we have to wait about 20 secs. 
    // Eliminates "ERROR on binding: Address already in use" error. 
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

    struct hostent * hostp = gethostbyaddr((const char *)&_clientaddr.sin_addr.s_addr, sizeof(_clientaddr.sin_addr.s_addr), AF_INET);
    if (hostp == NULL) {
        error("ERROR on gethostbyaddr");
    }
    char * hostaddrp = inet_ntoa(_clientaddr.sin_addr);
    if (hostaddrp == NULL) {
        error("ERROR on inet_ntoa");
    }
    printf("server received datagram from %s (%s)\n", hostp->h_name, hostaddrp);
    printf("server received %d/%d bytes: %s\n", (int)strlen(buf), n, buf);
}

void UdpSocketServer::sendData(char * buf, size_t len)
{
    if (sendto(_sockfd, buf, strlen(buf), 0, (struct sockaddr *) &_clientaddr, _clientlen) < 0)  {
        error("ERROR in sendto");
    }
}
