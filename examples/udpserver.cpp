/*
 * udpserver.cpp test code for UDP server sockets
 *
 * Copyright (C) 2019 Simon D. Levy
 *
 * MIT License
 */

#include <UdpSocketServer.h>

#include <string.h>

const short  PORT = 8888;

static const short BUFLEN = 512;

int main()
{
    char buf[BUFLEN];

    UdpSocketServer server(PORT);

    while (true) {

        printf("Waiting for data...");
        fflush(stdout);

        memset(buf, 0, BUFLEN);

        server.receiveData(buf, BUFLEN);

        printf("Data: %s\n", buf);

        server.sendData(buf, strlen(buf));
    }

    server.closeConnection();

    return 0;
}
