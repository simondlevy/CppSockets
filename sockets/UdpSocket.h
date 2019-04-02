/*
 * UdpSocket.h: class for UDP sockets
 *
 * Copyright (C) 2019 Simon D. Levy
 *
 * MIT License
 */

#pragma once

#include "SocketCompat.h"

class UdpSocket : public Socket {

    protected:

        struct sockaddr_in _si_other;
        socklen_t _slen = sizeof(_si_other);

    public:

        bool sendData(void * buf, size_t len);

        bool receiveData(void * buf, size_t len);
};
