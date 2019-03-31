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

    public:

        SocketServer(const char * host, short port);

        void acceptConnection(void);
};
