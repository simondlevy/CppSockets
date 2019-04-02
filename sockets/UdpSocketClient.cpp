/*
 * UdpSocketClient.cpp code for UDP client sockets
 *
 * Copyright (C) 2019 Simon D. Levy
 *
 * MIT License
 */

#include "UdpSocketClient.h"

#include <string.h>

#ifndef _WIN32
static void WSACleanup(void) { }
static void closesocket(int socket) { close(socket); }
#endif

UdpSocketClient::UdpSocketClient(const char * host, const short port)
{
    // Initialize Winsock, returning on failure
    if (!initWinsock()) return;

    // Create socket
    _s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (_s == SOCKET_ERROR) {
        sprintf_s(_message, "socket() failed");
        return;
    }

    // Setup address structure
    memset((char *)&_si_other, 0, sizeof(_si_other));
    _si_other.sin_family = AF_INET;
    _si_other.sin_port = htons(port);
    setHost(host);
}

bool UdpSocketClient::sendData(void * buf, size_t len)
{
    return sendto(_s, (const char *)buf, (int)len, 0, (struct sockaddr *) &_si_other, (int)_slen) != SOCKET_ERROR;
}

bool UdpSocketClient::receiveData(void * buf, size_t len)
{
    return recvfrom(_s, (char *)buf, (int)len, 0, (struct sockaddr *) &_si_other, &_slen) != SOCKET_ERROR;
}

void UdpSocketClient::closeConnection(void)
{
    closesocket(_s);
    WSACleanup();
}

bool UdpSocketClient::initWinsock(void)
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

void UdpSocketClient::setHost(const char * host)
{
 #ifdef _WIN32
    WCHAR wsz[64];
    swprintf_s(wsz, L"%S", host);
    InetPton(AF_INET, wsz, &(_si_other.sin_addr.s_addr));
#else
    inet_pton(AF_INET, host, &(_si_other.sin_addr));
#endif
}
