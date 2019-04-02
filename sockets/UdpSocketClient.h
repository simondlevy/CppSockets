/*
 * UdpSocketClient.h: class for UDP client sockets
 *
 * Copyright (C) 2019 Simon D. Levy
 *
 * MIT License
 */

#pragma once

#include <iostream>
#include<stdio.h>
#include<winsock2.h>
#include <WS2tcpip.h>
#include <tchar.h>

class UdpSocketClient {

    private:

        struct sockaddr_in _si_other;
        int _s;
        int _slen = sizeof(_si_other);

        char _message[100];

        bool initWinsock(void);

    public:

        UdpSocketClient(const char * host, const short port);

        bool sendData(void * buf, size_t len);

        bool receiveData(void * buf, size_t len);

        void closeConnection(void);
};
