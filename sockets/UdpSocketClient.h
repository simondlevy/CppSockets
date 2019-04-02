/*
 * UdpSocketClient.h: class for UDP client sockets
 *
 * Copyright (C) 2019 Simon D. Levy
 *
 * MIT License
 */

#pragma once

#include "SocketCompat.h"

class UdpSocketClient : public Socket {

    private:

        struct sockaddr_in _si_other;
        socklen_t _slen = sizeof(_si_other);

        void setHost(const char * host);

    public:

        UdpSocketClient(const char * host, const short port);

        bool sendData(void * buf, size_t len);

        bool receiveData(void * buf, size_t len);
};
