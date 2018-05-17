/*

   Example program for ThreadedS cketClient
 
   Copyright Simon D. Levy 2018

   MIT License
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "ThreadedSocketServer.h"

static const float RATE = 1.0; // updates per second

int main(int argc, char ** argv)
{
    // Require at a port number on command line
    if (argc < 2) {
        fprintf(stderr, "Usage:   %s <PORT>\n", argv[0]);
        fprintf(stderr, "Example: %s 20000\n", argv[0]);
        exit(1);
    }

    // Disallow low-numbered ports reserved for system services
    int port = atoi(argv[1]);
    if (port < 5000) {
        fprintf(stderr, "       port must be > 5000\n");
        exit(1);
    }

    ThreadedSocketServer server(port);

    server.start();

    // Support periodic checking for client connection
    float prevtime = 0;

    // Loop forever, receiving messages from the client and sending them back
    while (true) {

        struct timespec ts;
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts);
        float currtime =  ts.tv_sec + ts.tv_nsec / 1.e9f;

        if ((currtime - prevtime) > 1./RATE) {

            prevtime = currtime;

            if (server.connected()) {
                char buf[80] = "";
                if (server.recv(buf, 80) > 0) {
                    printf("Client said: %s\n", buf);
                    strcpy(buf, "reply");
                    server.send(buf, strlen(buf));
                }
                else {
                    break;
                }
            }
            else {
                printf("Listening ...\n");
            }
        }
    }

    // Shut down the listening thread
    server.stop();

    return 0;
}
