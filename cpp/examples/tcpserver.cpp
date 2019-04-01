/*
 * Test code for TCP server
 *
 * Copyright (C) 2019 Simon D. Levy
 *
 * MIT License
 */

#include "SocketServer.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char ** argv)
{
    if (argc < 2) {
        fprintf(stderr, "Usage:   %s PORT\n", argv[0]);
        fprintf(stderr, "Example: %s 5000\n", argv[0]);
        return 1;
    }

    SocketServer server("127.0.0.1", atoi(argv[1]));

    server.acceptConnection();

    server.closeConnection();

    return 0;
}


