/*

   Example server program for sockets
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

    // Serve the socket and accept the connection.

    int sock = serve_socket(port);
    int fd = accept_connection(sock);

    // Send the username along the socket.

    char * un = getenv("USER");
    printf("Connection established.  Sending `Server: %s'\n", un);
    char s[100];
    sprintf(s, "Server: %s\n", un);
    write(fd, s, strlen(s));

    // Read a line of text, one character at a time.
    printf("Receiving:\n\n");
    char c = 0;
    do {
        if (read(fd, &c, 1) != 1) {
            printf("Socket Closed Prematurely\n");
            exit(0);
        } else putchar(c);
    } while (c != '\n');


    return 0;
}
