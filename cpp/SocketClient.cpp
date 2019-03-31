/*
 * SocketClient.cpp: Class for general socket client in Goshawk project
 *
 * Copyright (C) 2019 Simon D. Levy
 *
 * MIT License
 */

#include "SocketClient.h"

// Called once on main thread
SocketClient::SocketClient(const char * host, const short port) : SocketCompat(host, port)
{
}

void SocketClient::openConnection(void)
{
    // Connect to server, returning on failure
    int iResult = connect(_sock, _addressInfo->ai_addr, (int)_addressInfo->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        closesocket(_sock);
        _sock = INVALID_SOCKET;
        sprintf(_message, "connect() failed; please make sure server is running");
        return;
    }

    // For a client, the connection is the same as the main socket
    _conn = _sock;

    // Success!
    _connected = true;
}
