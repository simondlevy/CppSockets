/*
 * SocketServer.h: general-purpose socket server class
 *
 * Copyright (C) 2019 Simon D. Levy
 *
 * MIT License
 */

#pragma once

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#undef TEXT
#include <winsock2.h>
#else
typedef int SOCKET;
#include <sys/types.h>
#include <sys/socket.h>
#endif

class SocketServer {

    private:

        char _host[200];
        char _port[10];

        SOCKET _socket;
        SOCKET _conn;

        char _message[200];

        bool initWinsock(void);

    public:

        SocketServer(const char * host, short port);

        void acceptConnection(void);

        bool sendData(void * buf, size_t len);

        bool receiveData(void * buf, size_t len);

        void closeConnection(void);
};
