/*
 * SocketClient.cpp: Class for general socket client in Goshawk project
 *
 * Copyright (C) 2019 Simon D. Levy
 *
 * MIT License
 */

#include "SocketClient.h"

#include <ws2tcpip.h>
#include <stdio.h>

// Called once on main thread
SocketClient::SocketClient(const char * host, const short port) 
{
    sprintf_s(_host, "%s", host);
    sprintf_s(_port, "%d", port);
}

void SocketClient::openConnection(void)
{
    // No connection yet
    _socket = INVALID_SOCKET;
    _connected = false;
    *_message = 0;

    // Adapted from https://docs.microsoft.com/en-us/windows/desktop/winsock/complete-client-code

    // Initialize Winsock, returning on failure
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        sprintf_s(_message, "WSAStartup() failed with error: %d\n", iResult);
        return;
    }

    // Set up client address info
    struct addrinfo hints = {0};
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    
    // Resolve the server address and port, returning on failure
    struct addrinfo * addressInfo = NULL;
    iResult = getaddrinfo(_host, _port, &hints, &addressInfo);
    if ( iResult != 0 ) {
        sprintf_s(_message, "getaddrinfo() failed with error: %d", iResult);
        WSACleanup();
        return;
    }

    // Create a SOCKET for connecting to server, returning on failure
    _socket = socket(addressInfo->ai_family, addressInfo->ai_socktype, addressInfo->ai_protocol);
    if (_socket == INVALID_SOCKET) {
        sprintf_s(_message, "socket() failed with error: %d\n", WSAGetLastError());
        WSACleanup();
        return;
    }

    // Connect to server, returning on failure
    iResult = connect(_socket, addressInfo->ai_addr, (int)addressInfo->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        closesocket(_socket);
        _socket = INVALID_SOCKET;
        sprintf_s(_message, "connect() failed; please make sure server is running");
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
    return send(_socket, (const char *)buf, len, 0) == len;
}

bool SocketClient::receiveData(void *buf, size_t len)
{
    return recv(_socket, (char *)buf, len, 0) == len;
}

bool SocketClient::isConnected(void)
{
    return _connected;
}

char * SocketClient::getMessage(void)
{
    return _message;
}
