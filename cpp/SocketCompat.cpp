/*
 * SocketCompat.cpp: cross-platform compatibility superclass for sockets
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

// Called once on main thread
SocketCompat::SocketCompat(const char * host, const short port) 
{
    sprintf_s(_host, "%s", host);
    sprintf_s(_port, "%d", port);

    // No connection yet
    _sock = INVALID_SOCKET;
    _connected = false;
    *_message = 0;

    int iResult = 0;

    // Initialize Winsock, returning on failure
    if (!initWinsock()) return;

    // Set up client address info
    struct addrinfo hints = {0};
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    
    // Resolve the server address and port, returning on failure
    _addressInfo = NULL;
    iResult = getaddrinfo(_host, _port, &hints, &_addressInfo);
    if ( iResult != 0 ) {
        sprintf_s(_message, "getaddrinfo() failed with error: %d", iResult);
        WSACleanup();
        return;
    }

    // Create a SOCKET for connecting to server, returning on failure
    _sock = socket(_addressInfo->ai_family, _addressInfo->ai_socktype, _addressInfo->ai_protocol);
    if (_sock == INVALID_SOCKET) {
        sprintf_s(_message, "socket() failed");
        WSACleanup();
        return;
    }
}

void SocketCompat::closeConnection(void)
{
    closesocket(_conn);
}

bool SocketCompat::sendData(void *buf, size_t len)
{
    return (size_t)send(_conn, (const char *)buf, len, 0) == len;
}

bool SocketCompat::receiveData(void *buf, size_t len)
{
    return (size_t)recv(_conn, (char *)buf, len, 0) == len;
}

bool SocketCompat::isConnected(void)
{
    return _connected;
}

char * SocketCompat::getMessage(void)
{
    return _message;
}

bool SocketCompat::initWinsock(void)
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
