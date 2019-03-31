/*
 * SocketServer.h: general-purpose socket server class
 *
 * Copyright (C) 2019 Simon D. Levy
 *
 * MIT License
 */

#pragma once

#include <sys/types.h>

class SocketServer {

    private:

        char _host[200];
        short _port;

        int _sock;
        int _conn;

        char _message[200];

    public:

        SocketServer(const char * host, short port);

        void acceptConnection(void);

        bool sendData(void * buf, size_t len);

        bool receiveData(void * buf, size_t len);

        void closeConnection(void);
};
