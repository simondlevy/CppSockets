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

    private:

        unsigned int _serverlen = sizeof(_serveraddr);

    public:

        UdpSocketClient(const char * host, short port);

        bool sendData(void * buf, size_t len);

        bool receiveData(void * buf, size_t len);
};
