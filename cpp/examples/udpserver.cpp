/*
 * Test code for UDP socket server
 *
 * Copyright (C) 2019 Simon D. Levy
 *
 * MIT License
 */

#include "UdpSocketServer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) 
{
    if (argc < 2) {
        fprintf(stderr, "Usage:   %s PORT\n", argv[0]);
        fprintf(stderr, "Example: %s 5000\n", argv[0]);
        return 1;
    }

    UdpSocketServer server("127.0.0.1", atoi(argv[1]));

    while (true) {

        char buf[100];
        bzero(buf, 100);
        server.receiveData(buf, 100);
        printf("server received: %s\n", buf);
    }
}
