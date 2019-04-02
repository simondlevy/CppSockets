/*
 * UdpSocketClient.cpp code for UDP client sockets
 *
 * Copyright (C) 2019 Simon D. Levy
 *
 * MIT License
 */

#include "UdpSocketClient.h"

#ifdef _WIN32
#pragma comment(lib,"ws2_32.lib") 
#endif

UdpSocketClient::UdpSocketClient(const char * host, const short port)
{
    // Initialize Winsock, returning on failure
    if (!initWinsock()) return;

    // Create socket
    if ((_s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == SOCKET_ERROR) {
        sprintf_s(_message, "socket() failed with error code : %d", WSAGetLastError());
        return;
    }

    // Setup address structure
    memset((char *)&_si_other, 0, sizeof(_si_other));
    _si_other.sin_family = AF_INET;
    _si_other.sin_port = htons(port);
    //si_other.sin_addr.S_un.S_addr = inet_addr(SERVER);

    WCHAR wsz[64];
    swprintf_s(wsz, L"%S", host);
    InetPton(AF_INET, wsz, &_si_other.sin_addr.s_addr);
}

bool UdpSocketClient::sendData(void * buf, size_t len)
{
    return sendto(_s, (const char *)buf, len, 0, (struct sockaddr *) &_si_other, _slen) != SOCKET_ERROR;
}

bool UdpSocketClient::receiveData(void * buf, size_t len)
{
    return recvfrom(_s, (char *)buf, len, 0, (struct sockaddr *) &_si_other, &_slen) != SOCKET_ERROR;
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

