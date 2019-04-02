/*
 * TcpSocketServer.h: general-purpose socket server class
 *
 * Copyright (C) 2019 Simon D. Levy
 *
 * MIT License
 */

#pragma once

#include "TcpSocket.h"

class TcpSocketServer : public TcpSocket {

    public:

        TcpSocketServer(const char * host, short port);

        void acceptConnection(void);
};
