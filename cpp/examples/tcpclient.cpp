/*
 * Test code for TCP server
 *
 * Copyright (C) 2019 Simon D. Levy
 *
 * MIT License
 */

#include "SocketClient.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char ** argv)
{
    if (argc < 3) {
        fprintf(stderr, "Usage:   %s HOST PORT\n", argv[0]);
        fprintf(stderr, "Example: %s localhost 5000\n", argv[0]);
        return 1;
    }

    SocketClient client(argv[1], atoi(argv[2]));

    client.openConnection();

    char message[100] = "Hello from client!";

    client.sendData(message, strlen(message));

    return 0;
}


