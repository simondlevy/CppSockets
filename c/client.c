/*

   Example client program for sockets

   Adapted from http://web.eecs.utk.edu/~huangj/cs360/360/notes/Sockets/socketfun.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/socket.h>

#include "sockettome.h"

int main(int argc, char ** argv)
{
    if (argc < 3) {
        fprintf(stderr, "Usage:   %s <HOST> <PORT>\n", argv[0]);
        fprintf(stderr, "Example: %s 137.113.118.3 20000\n", argv[0]);
        exit(1);
    }

    char * hn = argv[1];
    int port = atoi(argv[2]);
    char * un = getenv("USER");

    // true = retry till success
    int fd = request_connection(hn, port, true);

    printf("Connection established.  Receiving:\n\n");

    FILE * fin = fdopen(fd, "r");
    FILE * fout = fdopen(fd, "w");

    // Read from the server.

    char s[100];
    if (fgets(s, 1000, fin) == NULL) {
        printf("Server closed prematurely\n");
        exit(0);
    }
    printf("Received: %s", s);

    // And send a line to the server.

    printf("Sending `Client: %s' to the server\n", un);
    fprintf(fout, "Client: %s\n", un);

    return 0;
}
