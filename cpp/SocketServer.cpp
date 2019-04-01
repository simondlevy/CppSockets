/*
 * SocketServer.cpp: general-purpose socket server code
 *
 * Copyright (C) 2019 Simon D. Levy
 *
 * MIT License
 */

#include "SocketServer.h"

#ifndef _WIN32
static void closesocket(int socket) { close(socket); }
#endif

SocketServer::SocketServer(const char * host, short port) : SocketCompat(host, port)
{
    // Bind socket to address, exiting on failure
    int iResult = bind(_sock, _addressInfo->ai_addr, (int)_addressInfo->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        closesocket(_sock);
        _sock = INVALID_SOCKET;
        sprintf_s(_message, "bind() failed");
        return;
    }
}

void SocketServer::acceptConnection(void)
{
    // Listen for a connection, exiting on failure
    if (listen(_sock, 1)  == -1) {
        sprintf_s(_message, "listen() failed");
        return;
    }

    // Accept connection, exiting on failure
    printf("Waiting for client to connect on %s:%s ... ", _host, _port);
    fflush(stdout);
    _conn = accept(_sock, (struct sockaddr *)NULL, NULL);
    if (_conn == SOCKET_ERROR) {
        sprintf_s(_message, "accept() failed");
        return;
    }
    printf("connected\n");
    fflush(stdout);
}
