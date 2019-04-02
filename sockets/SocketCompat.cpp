/*
 * SocketCompat.cpp code for sockets
 *
 * Copyright (C) 2019 Simon D. Levy
 *
 * MIT License
 */

#include "SocketCompat.h"

char * Socket::getMessage(void)
{
    return _message;
}

void Socket::closeConnection(void)
{
#ifdef _WIN32
    closesocket(_sock);
#else
    close(_sock);
#endif
}

void Socket::cleanup(void)
{
#ifdef _WIN32
    WSACleanup();
#endif
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
