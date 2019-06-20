/*
 * Class for UDP sockets
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

        bool sendData(void * buf, size_t len)
        {
            return sendto(_sock, (const char *)buf, (int)len, 0, (struct sockaddr *) &_si_other, (int)_slen) != SOCKET_ERROR;

        }

        bool receiveData(void * buf, size_t len)
        {
            return recvfrom(_sock, (char *)buf, (int)len, 0, (struct sockaddr *) &_si_other, &_slen) != SOCKET_ERROR;
        }
};
