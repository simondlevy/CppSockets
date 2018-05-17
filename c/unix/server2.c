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

typedef struct {

    int fd;
    int sock;

} socket_info_t;

void * threadfunc(void * arg)
{
    socket_info_t * sockinfo = (socket_info_t *)arg;

    // Wait for a connection
    printf("Waiting for a client ...");
    fflush(stdout);
    sockinfo->fd = accept_connection(sockinfo->sock);
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
    socket_info_t sockinfo;

    // Serve the socket 
    sockinfo.sock = serve_socket(port);

    if (pthread_create(&tcb, NULL, threadfunc, &sockinfo) != 0) {
        perror("pthread_create");
    }

    // Loop forever, receiving messages from the client and sending them back
    while (true) {

        if (sockinfo.fd > 0) {
            char buf[80] = "";
            read(sockinfo.fd, buf, 80);
            printf("Client said: %s\n", buf);
            strcpy(buf, "reply");
            write(sockinfo.fd, buf, strlen(buf));
        }
    }

    void * status;
    if (pthread_join(tcb, &status) != 0) { 
        perror("pthread_join"); 
    }

    return 0;
}
