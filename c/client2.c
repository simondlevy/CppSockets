/*

   Example client program for sockets.  Loops forever, attempt to connect to serer,
   then communicating once a connection is established

   Adapted from http://web.eecs.utk.edu/~huangj/cs360/360/notes/Sockets/socketfun.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <fcntl.h>
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

    float prevtime = 0;

    int sockfd = 0;

    FILE * fin = NULL;
    //FILE * fout = NULL;

    while (true) {

        struct timespec ts;
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts);
        float currtime =  ts.tv_sec + ts.tv_nsec / 1.e9f;

        if ((currtime - prevtime) > 1./RATE) {

            // not connected; keep trying
            if (sockfd == 0) {

                // false = non-blocking
                sockfd = request_connection(hn, port, false);
            }

            else if (fin == 0) {
                int flags = fcntl(sockfd, F_GETFL, 0);
                fcntl(sockfd, F_SETFL, flags|O_NONBLOCK);
                fin  = fdopen(sockfd, "r");
                //fout = fdopen(sockfd, "w");
            }

            // connected
            else {

                char s[80];
                if (fgets(s, 80, fin) != NULL) {
                    printf("Server said: %s\n", s);
                }
            }

            prevtime = currtime;
        }
    }

    return 0;
}
