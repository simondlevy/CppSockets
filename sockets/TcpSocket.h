/*
 * TcpSocket.h: cross-platform compatibility superclass for sockets
 *
 * Copyright (C) 2019 Simon D. Levy
 *
 * MIT License
 */

#pragma once

#include "SocketCompat.h"

class TcpSocket : public Socket {

    protected:

        char _host[200];
        char _port[10];

        SOCKET _conn;

        struct addrinfo * _addressInfo;

        bool _connected;

        TcpSocket(const char * host, const short port);

    public:

        bool sendData(void *buf, size_t len);

        bool receiveData(void *buf, size_t len);

        bool isConnected();
};
