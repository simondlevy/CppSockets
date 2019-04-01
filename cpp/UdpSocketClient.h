/*
 * UdpSocketClient.h: class for UDP client sockets
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

class UdpSocketClient {

    private:

        int _sockfd;
        struct sockaddr_in _serveraddr;
        unsigned int _serverlen = sizeof(_serveraddr);

        void error(const char * msg);

    public:

        UdpSocketClient(const char * host, short port);

        bool sendData(char *buf, size_t len);

        bool receiveData(char *buf, size_t len);
};
