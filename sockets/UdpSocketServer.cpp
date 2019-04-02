/*
 * UdpSocketServer.cpp: code for UDP server sockets
 *
 * Copyright (C) 2019 Simon D. Levy
 *
 * MIT License
 */

#include "UdpSocketServer.h"

#ifndef _WIN32
static void WSACleanup(void) { }
static void closesocket(int socket) { close(socket); }
#endif

UdpSocketServer::UdpSocketServer(const short port)
{
    // Initialize Winsock, returning on failure
    if (!initWinsock()) return;

    _s = socket(AF_INET, SOCK_DGRAM, 0);
    if (_s == INVALID_SOCKET) {
        sprintf_s(_message, "socket() failed");
        return;
    }

    // Prepare the sockaddr_in structure
    _server.sin_family = AF_INET;
    _server.sin_addr.s_addr = INADDR_ANY;
    _server.sin_port = htons(port);

    // Bind
    if (bind(_s, (struct sockaddr *)&_server, sizeof(_server)) == SOCKET_ERROR) {
        sprintf_s(_message, "bind() failed");
        return;
    }
}

bool UdpSocketServer::sendData(void * buf, size_t len)
{
    return sendto(_s, (const char *)buf, (int)len, 0, (struct sockaddr *) &_si_other, (int)_slen) != SOCKET_ERROR;
}

bool UdpSocketServer::receiveData(void * buf, size_t len)
{
    return recvfrom(_s, (char *)buf, (int)len, 0, (struct sockaddr *) &_si_other, &_slen) != SOCKET_ERROR;
}

void UdpSocketServer::closeConnection(void)
{
    closesocket(_s);
    WSACleanup();
}

bool UdpSocketServer::initWinsock(void)
{
#ifdef _WIN32
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        sprintf_s(_message, "WSAStartup() failed with error: %d\n", iResult);
        return false;
    }
#endif
    return true;
}


