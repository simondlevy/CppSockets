/*
 * udpserver.cpp test code for UDP server sockets
 *
 * Copyright (C) 2019 Simon D. Levy
 *
 * MIT License
 */

#include <UdpServerSocket.hpp>

#include <string.h>
#include <unistd.h>

const short           PORT         = 8888;
static const short    BUFLEN       = 512;
static const uint32_t TIMEOUT_MSEC = 1000;

int main()
{
    char buf[BUFLEN];

    UdpServerSocket server(PORT, TIMEOUT_MSEC);

    while (true) {

        printf("Waiting for data...");
        fflush(stdout);

        memset(buf, 0, BUFLEN);

        *buf = 0;

        server.receiveData(buf, BUFLEN);

        if (*buf) {
            printf("Data: %s\n", buf);
            server.sendData(buf, strlen(buf));
        }

        else {
            printf("\n");
            sleep(1);
        }

    }

    server.closeConnection();

    return 0;
}
