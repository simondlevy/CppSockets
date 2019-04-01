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

int main(int argc, char ** argv)
{
    if (argc < 2) {
        fprintf(stderr, "Usage:   %s PORT\n", argv[0]);
        fprintf(stderr, "Example: %s 5000\n", argv[0]);
        return 1;
    }

    return 0;
}


