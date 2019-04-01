/*
 * Test code for UDP socket client
 *
 * Copyright (C) 2019 Simon D. Levy
 *
 * MIT License
 */

#include "UdpSocketClient.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) 
{
    char buf[100];

    if (argc < 3) {
        fprintf(stderr, "Usage:   %s HOST PORT\n", argv[0]);
        fprintf(stderr, "Example: %s localhost 5000\n", argv[0]);
        return 1;
    }

    bzero(buf, 100);
    printf("Please enter msg: ");
    fgets(buf, 100, stdin);

    UdpSocketClient client(argv[1], atoi(argv[2]));

    client.sendData((void *)buf, strlen(buf));

    return 0;
}
