/*
 * SocketCompat.cpp code for sockets
 *
 * Copyright (C) 2019 Simon D. Levy
 *
 * MIT License
 */

#include "SocketCompat.h"

#ifndef _WIN32
static void WSACleanup(void) { }
static void closesocket(int socket) { close(socket); }
#endif

char * Socket::getMessage(void)
{
    return _message;
}

void Socket::closeConnection(void)
{
    closesocket(_sock);
    WSACleanup();
}

bool Socket::initWinsock(void)
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
