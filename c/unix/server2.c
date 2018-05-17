/*

   Example threaded server program for sockets
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <stdbool.h>
#include <time.h>

#include "sockettome.h"

static const float RATE = 1.0; // updates per second

// XXX should pass these to threadfunc
static int fd;
static int sock;

void * threadfunc(void * arg)
{
    // Wait for a connection
    printf("Waiting for a client ...");
    fflush(stdout);
    fd = accept_connection(sock);
    printf(" Connected!\n");

    return NULL;
}

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

    pthread_t tcb;

    // Serve the socket 
    sock = serve_socket(port);

    if (pthread_create(&tcb, NULL, threadfunc, NULL) != 0) {
        perror("pthread_create");
    }

    // Loop forever, receiving messages from the client and sending them back
    while (true) {

        if (fd > 0) {
            char buf[80] = "";
            read(fd, buf, 80);
            printf("Client said: %s\n", buf);
            strcpy(buf, "reply");
            write(fd, buf, strlen(buf));
        }
    }

    void * status;
    if (pthread_join(tcb, &status) != 0) { 
        perror("pthread_join"); 
    }

    return 0;
}
