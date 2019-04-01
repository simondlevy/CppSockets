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

        int _sockfd;
        struct sockaddr_in _serveraddr; 
        struct sockaddr_in _clientaddr;
        unsigned int _clientlen = sizeof(_clientaddr);

    public:

        UdpSocketServer(const char * host, short port);

        void receiveData(char  * buf, size_t len);

        void sendData(char * buf, size_t len);
};
