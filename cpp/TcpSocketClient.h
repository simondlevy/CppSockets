/*
 * TcpSocketClient.h: TCP socket client class
 *
 * Copyright (C) 2019 Simon D. Levy
 *
 * MIT License
 */

#pragma once

#include "SocketClient.h"

class TcpSocketClient : public SocketClient {

    public:

        TcpSocketClient(const char * host, short port) : SocketClient(host, port, SOCK_STREAM) { }
};
