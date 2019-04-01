/*
 * TcpSocketClient.h: class for TCP sockets
 *
 * Copyright (C) 2019 Simon D. Levy
 *
 * MIT License
 */

#pragma once

#include "TcpSocketCompat.h"

class TcpSocketClient : public TcpSocketCompat {

    public:

        TcpSocketClient(const char * host, const short port);

        void openConnection(void);
};
