/*
 * UDP SocketServer.cpp: general-purpose TCP socket server code
 *
 * Copyright (C) 2019 Simon D. Levy
 *
 * MIT License
 */

#pragma once

#include "UdpSocket.h"

class UdpSocketServer : public UdpSocket {

    private:

        struct sockaddr_in _clientaddr;
        unsigned int _clientlen = sizeof(_clientaddr);

    public:

        UdpSocketServer(const char * host, short port);

        bool receiveData(char  * buf, size_t len);

        bool sendData(char * buf, size_t len);
};
