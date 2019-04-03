/*
 * UdpClientSocket.h: class for UDP client sockets
 *
 * Copyright (C) 2019 Simon D. Levy
 *
 * MIT License
 */

#pragma once

#include "UdpSocket.h"

class UdpClientSocket : public UdpSocket {

    public:

        UdpClientSocket(const char * host, const short port);
};
