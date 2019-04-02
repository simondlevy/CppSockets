/*
 * UdpSocketServer.cpp: code for UDP server sockets
 *
 * Copyright (C) 2019 Simon D. Levy
 *
 * MIT License
 */

#include "UdpSocketServer.h"

UdpSocketServer::UdpSocketServer(const short port)
{
    // Initialize Winsock, returning on failure
    if (!initWinsock()) return;

    // Create socket
    _sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (_sock == INVALID_SOCKET) {
        sprintf_s(_message, "socket() failed");
        return;
    }

    // Prepare the sockaddr_in structure
    _server.sin_family = AF_INET;
    _server.sin_addr.s_addr = INADDR_ANY;
    _server.sin_port = htons(port);

    // Bind
    if (bind(_sock, (struct sockaddr *)&_server, sizeof(_server)) == SOCKET_ERROR) {
        sprintf_s(_message, "bind() failed");
        return;
    }
}

bool UdpSocketServer::sendData(void * buf, size_t len)
{
    return sendto(_sock, (const char *)buf, (int)len, 0, (struct sockaddr *) &_si_other, (int)_slen) != SOCKET_ERROR;
}

bool UdpSocketServer::receiveData(void * buf, size_t len)
{
    return recvfrom(_sock, (char *)buf, (int)len, 0, (struct sockaddr *) &_si_other, &_slen) != SOCKET_ERROR;
}
