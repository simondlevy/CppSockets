/*
 * UDP SocketServer.cpp: general-purpose TCP socket server code
 *
 * Copyright (C) 2019 Simon D. Levy
 *
 * MIT License
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

class UdpSocketServer {

    private:

        int _sockfd;
        struct sockaddr_in _serveraddr; 
        struct sockaddr_in _clientaddr;
        unsigned int _clientlen = sizeof(_clientaddr);

        static void error(const char * msg);

    public:

        UdpSocketServer(const char * host, short port);

        void receiveData(char  * buf, size_t len);

        void sendData(char * buf, size_t len);
};
