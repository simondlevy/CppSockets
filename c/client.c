/*

   Example client program for sockets

   Adapted from http://web.eecs.utk.edu/~huangj/cs360/360/notes/Sockets/socketfun.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

#include "sockettome.h"

int main(int argc, char ** argv)
{
    if (argc < 3) {
        fprintf(stderr, "Usage:   %s <HOST> <PORT>\n", argv[0]);
        fprintf(stderr, "Example: %s 137.113.118.3 20000\n", argv[0]);
        exit(1);
    }

    return 0;
}
