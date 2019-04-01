/*
 * SocketServer.h: general-purpose socket server class
 *
 * Copyright (C) 2019 Simon D. Levy
 *
 * MIT License
 */

#pragma once

#include "SocketCompat.h"

class SocketServer : public SocketCompat {

    protected:

        SocketServer(const char * host, short port, int type);

    public:

        void acceptConnection(void);
};
