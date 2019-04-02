/*
 * UdpSocketClient.h: class for UDP client sockets
 *
 * Copyright (C) 2019 Simon D. Levy
 *
 * MIT License
 */

#pragma once

#include "UdpSocket.h"

class UdpSocketClient : public UdpSocket {

    public:

        UdpSocketClient(const char * host, const short port);
};
