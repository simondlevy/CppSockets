/*

   Example threaded server program for sockets
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "sockettome.h"

int main(int argc, char ** argv)
{
    if (argc < 2) {
        fprintf(stderr, "Usage:   %s <PORT>\n", argv[0]);
        fprintf(stderr, "Example: %s 20000\n", argv[0]);
        exit(1);
    }

    int port = atoi(argv[1]);
    if (port < 5000) {
        fprintf(stderr, "       port must be > 5000\n");
        exit(1);
    }

    // Serve the socket 
    int sock = serve_socket(port);

    // Wait for a connection
    printf("Waiting for a client ...");
    int fd = accept_connection(sock);

    // Send the username along the socket.

    printf(" Connected!\n");

    while (1) {

        char buf[80] = "";
        read(fd, buf, 80);
        printf("Client said: %s\n", buf);
        strcpy(buf, "reply");
        write(fd, buf, strlen(buf));
    }

    return 0;
}
