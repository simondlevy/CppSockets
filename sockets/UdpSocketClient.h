/*
 * UdpSocketClient.h: class for UDP client sockets
 *
 * Copyright (C) 2019 Simon D. Levy
 *
 * MIT License
 */

#pragma once

// Windows
#ifdef _WIN32
#pragma comment(lib,"ws2_32.lib") 
#define WIN32_LEAN_AND_MEAN
#undef TEXT
#include <winsock2.h>
#include <ws2tcpip.h>

// Linux
#else
#define sprintf_s sprintf
typedef int SOCKET;
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
static const int INVALID_SOCKET = -1;
static const int SOCKET_ERROR   = -1;
#endif

#include <stdio.h>

class UdpSocketClient {

    private:

        struct sockaddr_in _si_other;
        int _s;
        int _slen = sizeof(_si_other);

        char _message[100];

        bool initWinsock(void);

        void setHost(const char * host);

    public:

        UdpSocketClient(const char * host, const short port);

        bool sendData(void * buf, size_t len);

        bool receiveData(void * buf, size_t len);

        void closeConnection(void);
};
