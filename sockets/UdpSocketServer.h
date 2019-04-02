/*
 * UdpSocketServer.h: class for UDP server sockets
 *
 * Copyright (C) 2019 Simon D. Levy
 *
 * MIT License
 */

#pragma once

#include <iostream>
#include <stdio.h>
#include <winsock2.h>

#pragma comment(lib,"ws2_32.lib") //Winsock Library

class UdpSocketServer {

    private:

        SOCKET _s;
        struct sockaddr_in _server;
        struct sockaddr_in _si_other;
        int _recv_len;
        int _slen = sizeof(_si_other);
        char _message[100];

    public:

        UdpSocketServer(const short port);

        bool sendData(void * buf, size_t len);

        bool receiveData(void * buf, size_t len);

        void closeConnection(void);
};
