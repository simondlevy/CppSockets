/*
 * UdpSocketClient.h: class for UDP client sockets
 *
 * Copyright (C) 2019 Simon D. Levy
 *
 * MIT License
 */

#include <iostream>
#include<stdio.h>
#include<winsock2.h>
#include <WS2tcpip.h>
#include <tchar.h>

#pragma comment(lib,"ws2_32.lib") //Winsock Library

#define SERVER "127.0.0.1"	//ip address of udp server
#define PORT 8888	//The port on which to listen for incoming data

class UdpSocketClient {

    private:

        struct sockaddr_in _si_other;
        int _s;
        int _slen = sizeof(_si_other);

        char _message[100];

    public:

        UdpSocketClient(void);

        bool sendData(void * buf, size_t len);

        bool receiveData(void * buf, size_t len);

        void closeConnection(void);
};
