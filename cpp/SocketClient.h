/*
 * SocketClient.h: class for general socket clients in Goshawk project
 *
 * Copyright (C) 2019 Simon D. Levy
 *
 * MIT License
 */

#pragma once

#define WIN32_LEAN_AND_MEAN

#undef TEXT
#include <winsock2.h>

class SocketClient {

    private:

        SOCKET _socket;

        char _message[200];

        bool _connected;

        char _host[200];
        char _port[10];

    public:

        SocketClient(const char * host, const short port);

        ~SocketClient();

        void openConnection(void);

        void closeConnection(void);

        bool sendData(void *buf, size_t len);

        bool receiveData(void *buf, size_t len);

        bool isConnected();

        char * getMessage(void);
};
