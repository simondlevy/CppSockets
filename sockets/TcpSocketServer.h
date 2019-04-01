/*
 * TcpSocketServer.h: general-purpose socket server class
 *
 * Copyright (C) 2019 Simon D. Levy
 *
 * MIT License
 */

#pragma once

#include "TcpSocketCompat.h"

class TcpSocketServer : public TcpSocketCompat {

    public:

        TcpSocketServer(const char * host, short port);

        void acceptConnection(void);
};
