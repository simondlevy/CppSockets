/*
 * SocketClient.cpp: Class for general socket client in Goshawk project
 *
 * Copyright (C) 2019 Simon D. Levy
 *
 * MIT License
 */

#include "SocketClient.h"

// Windows
#ifdef _WIN32
#include <ws2tcpip.h>

// Linux
#else
#include <netdb.h>
#include <unistd.h>
static const int INVALID_SOCKET = -1;
static const int SOCKET_ERROR   = -1;
static void closesocket(int socket) { close(socket); }
static void WSACleanup(void) { }
#endif

#include <stdio.h>

// Called once on main thread
SocketClient::SocketClient(const char * host, const short port) 
{
    sprintf(_host, "%s", host);
    sprintf(_port, "%d", port);
}

void SocketClient::openConnection(void)
{
    // No connection yet
    _socket = INVALID_SOCKET;
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
    struct addrinfo * addressInfo = NULL;
    iResult = getaddrinfo(_host, _port, &hints, &addressInfo);
    if ( iResult != 0 ) {
        sprintf(_message, "getaddrinfo() failed with error: %d", iResult);
        WSACleanup();
        return;
    }

    // Create a SOCKET for connecting to server, returning on failure
    _socket = socket(addressInfo->ai_family, addressInfo->ai_socktype, addressInfo->ai_protocol);
    if (_socket == INVALID_SOCKET) {
        sprintf(_message, "socket() failed");
        WSACleanup();
        return;
    }

    // Connect to server, returning on failure
    iResult = connect(_socket, addressInfo->ai_addr, (int)addressInfo->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        closesocket(_socket);
        _socket = INVALID_SOCKET;
        sprintf(_message, "connect() failed; please make sure server is running");
        return;
    }

    // Success!
    _connected = true;
}

void SocketClient::closeConnection(void)
{
    closesocket(_socket);
}

SocketClient::~SocketClient()
{
}

bool SocketClient::sendData(void *buf, size_t len)
{
    return (size_t)send(_socket, (const char *)buf, len, 0) == len;
}

bool SocketClient::receiveData(void *buf, size_t len)
{
    return (size_t)recv(_socket, (char *)buf, len, 0) == len;
}

bool SocketClient::isConnected(void)
{
    return _connected;
}

char * SocketClient::getMessage(void)
{
    return _message;
}

bool SocketClient::initWinsock(void)
{
#ifdef _WIN32
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        sprintf(_message, "WSAStartup() failed with error: %d\n", iResult);
        return false;
    }
#endif
    return true;
}
