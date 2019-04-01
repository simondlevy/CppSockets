/*
 * TcpSocketServer.h: TCP socket server class
 *
 * Copyright (C) 2019 Simon D. Levy
 *
 * MIT License
 */

#pragma once

#include "SocketServer.h"

class TcpSocketServer : public SocketServer {

    public:

        TcpSocketServer(const char * host, short port) : SocketServer(host, port, SOCK_STREAM) { }
};
