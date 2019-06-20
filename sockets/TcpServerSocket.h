/*
 * TcpServerSocket.h: general-purpose socket server class
 *
 * Copyright (C) 2019 Simon D. Levy
 *
 * MIT License
 */

#pragma once

#include "TcpSocket.hpp"

class TcpServerSocket : public TcpSocket {

    public:

        TcpServerSocket(const char * host, short port);

        void acceptConnection(void);
};
