/*
 * TcpSocketClient.cpp: Class for TCP socket clients
 *
 * Copyright (C) 2019 Simon D. Levy
 *
 * MIT License
 */

#include "TcpSocketClient.h"

#ifndef _WIN32
static void closesocket(int socket) { close(socket); }
#endif


// Called once on main thread
TcpSocketClient::TcpSocketClient(const char * host, const short port) : TcpSocketCompat(host, port)
{
}

void TcpSocketClient::openConnection(void)
{
    // Connect to server, returning on failure
    if (connect(_sock, _addressInfo->ai_addr, (int)_addressInfo->ai_addrlen) == SOCKET_ERROR) {
        closesocket(_sock);
        _sock = INVALID_SOCKET;
        sprintf_s(_message, "connect() failed; please make sure server is running");
        return;
    }

    // For a client, the connection is the same as the main socket
    _conn = _sock;

    // Success!
    _connected = true;
}
