/*

   Example non-blocking client program for sockets.  Loops forever, attempt to
   connect to serer, then communicating once a connection is established

   Adapted from http://web.eecs.utk.edu/~huangj/cs360/360/notes/Sockets/socketfun.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <fcntl.h>
#include <sys/socket.h>

#include "sockettome.h"

#define NMESSAGES 5

static const float RATE = 1.0; // updates per second

static const char * messages[NMESSAGES] = {"one", "two", "three", "four", "five"};
static int  messageId = 0;

int main(int argc, char ** argv)
{
    if (argc < 2) {
        fprintf(stderr, "Usage:   %s <PORT>\n", argv[0]);
        fprintf(stderr, "Usage:   %s <HOST> <PORT>\n", argv[0]);
        fprintf(stderr, "Example: %s 20000\n", argv[0]);
        fprintf(stderr, "Example: %s 137.113.118.3 20000\n", argv[0]);
        exit(1);
    }

    char * hn = (argc > 2) ? argv[1] : (char *)"localhost";
    int port = atoi(argc > 2 ? argv[2] : argv[1]);

    float prevtime = 0;

    int sockfd = 0;

    FILE * fin = NULL;
    FILE * fout = NULL;

    while (true) {

        struct timespec ts;
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts);
        float currtime =  ts.tv_sec + ts.tv_nsec / 1.e9f;

        if ((currtime - prevtime) > 1./RATE) {

            // not connected; keep trying
            if (sockfd == 0) {

                printf("Attempting connection to server %s:%d\n", hn, port);

                // false = no retry
                sockfd = request_connection(hn, port, false);
            }

            else if (fin == 0) {

                printf("Connected!\n");
                int flags = fcntl(sockfd, F_GETFL, 0);
                fcntl(sockfd, F_SETFL, flags|O_NONBLOCK);
                fin  = fdopen(sockfd, "r");
                fout = fdopen(sockfd, "w");
            }

            // connected
            else {

                char s[80];
                if (fgets(s, 80, fin) != NULL) {
                    printf("Server said: %s\n", s);
                    fprintf(fout, "%s", messages[messageId]);
                    fflush(fout);
                    messageId = (messageId + 1) % NMESSAGES;
                }
            }

            prevtime = currtime;
        }
    }

    return 0;
}
