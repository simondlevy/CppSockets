/*
 * TcpSocketClient.h: class for TCP client sockets
 *
 * Copyright (C) 2019 Simon D. Levy
 *
 * MIT License
 */

#pragma once

#include "TcpSocket.h"

class TcpSocketClient : public TcpSocket {

    public:

        TcpSocketClient(const char * host, const short port);

        void openConnection(void);
};
