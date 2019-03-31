/*
 * SocketServer.cpp: general-purpose socket server code
 *
 * Copyright (C) 2019 Simon D. Levy
 *
 * MIT License
 */

#include "SocketServer.h"

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

SocketServer::SocketServer(const char * host, short port)
{
    // acceptConnection() will use these for reporting
    sprintf(_host, "%s", host);
    sprintf(_port, "%d", port);

    // No connections yet
    _socket = INVALID_SOCKET;
    _conn = INVALID_SOCKET;
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

    // Bind socket to address, exiting on failure
    iResult = bind(_socket, addressInfo->ai_addr, (int)addressInfo->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        closesocket(_socket);
        _socket = INVALID_SOCKET;
        sprintf(_message, "bind() failed");
        return;
    }
}

void SocketServer::acceptConnection(void)
{
    // Listen for a connection, exiting on failure
    if (listen(_socket, 1)  == -1) {
        sprintf(_message, "listen() failed");
        return;
    }

    // Accept connection, exiting on failure
    printf("Waiting for client to connect on %s:%s ... ", _host, _port);
    fflush(stdout);
    _conn = accept(_socket, (struct sockaddr *)NULL, NULL);
    if (_conn == SOCKET_ERROR) {
        sprintf(_message, "accept() failed");
        return;
    }
    printf("connected\n");
    fflush(stdout);
}

bool SocketServer::sendData(void * buf, size_t len)
{
    return (size_t)send(_conn, (const char *)buf, len, 0) == len;
}

bool SocketServer::receiveData(void * buf, size_t len)
{
    return (size_t)recv(_conn, (char *)buf, len, 0) == len;
}

void SocketServer::closeConnection(void)
{
    closesocket(_conn);
}

bool SocketServer::initWinsock(void)
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

