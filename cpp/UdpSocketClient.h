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

        int _sockfd;
        struct sockaddr_in _serveraddr;
        unsigned int _serverlen = sizeof(_serveraddr);

    public:

        UdpSocketClient(const char * host, short port);

        bool sendData(char *buf, size_t len);

        bool receiveData(char *buf, size_t len);
};
