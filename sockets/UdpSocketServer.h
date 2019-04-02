/*
 * UdpSocketServer.h: class for UDP server sockets
 *
 * Copyright (C) 2019 Simon D. Levy
 *
 * MIT License
 */

#pragma once

#include "SocketCompat.h"

class UdpSocketServer : public Socket {

    private:

        struct sockaddr_in _si_other;
        socklen_t _slen = sizeof(_si_other);

        struct sockaddr_in _server;
        socklen_t _recv_len;

    public:

        UdpSocketServer(const short port);

        bool sendData(void * buf, size_t len);

        bool receiveData(void * buf, size_t len);
};
