/*
 * Test code for TCP server
 *
 * Copyright (C) 2019 Simon D. Levy
 *
 * MIT License
 */

#include "TcpServerSocket.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char ** argv)
{
    if (argc < 2) {
        fprintf(stderr, "Usage:   %s PORT\n", argv[0]);
        fprintf(stderr, "Example: %s 5000\n", argv[0]);
        return 1;
    }

    TcpServerSocket server("127.0.0.1", atoi(argv[1]));

    server.acceptConnection();

    char message[100];

    server.receiveData(message, 100);

    printf("Client said: %s\n", message);

    strcpy(message, "Hello from server!");

    server.sendData(message, 100);

    server.closeConnection();

    return 0;
}


