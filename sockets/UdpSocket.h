/*
 * UDP Socket.h: general-purpose UDP socket code
 *
 * Copyright (C) 2019 Simon D. Levy
 *
 * MIT License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <arpa/inet.h>

class UdpSocket {

    protected:

        char _message[200];

        UdpSocket(const char * host, short port);

        int _sockfd;

        struct sockaddr_in _serveraddr;

        bool sendData(void * buf, size_t len, struct sockaddr_in * addr, unsigned int addrlen);

        bool receiveData(void * buf, size_t len, struct sockaddr_in * addr, unsigned int * addrlen);
};
