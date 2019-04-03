/*
 * UdpServerSocket.h: class for UDP server sockets
 *
 * Copyright (C) 2019 Simon D. Levy
 *
 * MIT License
 */

#pragma once

#include "UdpSocket.h"

class UdpServerSocket : public UdpSocket {

    public:

        UdpServerSocket(const short port);
};
