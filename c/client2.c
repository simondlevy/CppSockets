/*

   Example client program for sockets.  Loops forever, attempt to connect to serer,
   then communicating once a connection is established

   Adapted from http://web.eecs.utk.edu/~huangj/cs360/360/notes/Sockets/socketfun.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <sys/socket.h>

#include "sockettome.h"

static const float RATE = 1.0; // updates per second

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

    float prevtime = 0;

    int tick = 0;

    while (true) {

        struct timespec ts;
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts);
        float currtime =  ts.tv_sec + ts.tv_nsec / 1.e9f;

        if ((currtime - prevtime) > 1./RATE) {

            printf("tick %d\n", tick++);

            prevtime = currtime;
        }
    }

    /*
    int fd = request_connection(hn, port);

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
    */

    return 0;
}

/*
RATE = 1 # Update frequency in Herz 

import socket
import time
import fcntl
import os

from hostport import hostport

if __name__ == '__main__':

    messages = ['one', 'two', 'three', 'four', 'five']
    messageId = 0

    host, port = hostport()

    sock = socket.socket()

    connected = False

    start = time.time()
    prev = start

    while True:

        curr = time.time()

        if curr - prev > 1./RATE:

            prev = curr

            if connected:

                try:
                    msg = sock.recv(80) # Maximum number of bytes we expect
                    if len(msg) < 1:
                        sock.close()
                        sock = socket.socket()
                        connected = False
                    else:
                        print('Server said: ' + msg.decode('utf-8')) # Python 3 requires decoding

                except:
                    continue

                try:
                    sock.send(messages[messageId].encode('utf-8'))

                except socket.error:
                    continue

                messageId = (messageId + 1) % len(messages)

            else:

                try:
                    sock.connect((host, port)) # Note tuple!
                    fcntl.fcntl(sock, fcntl.F_SETFL, os.O_NONBLOCK)
                    connected = True
                    print('Connected to server %s:%d' % (host, port))
                except socket.error: 
                    continue


    sock.close()
    */
