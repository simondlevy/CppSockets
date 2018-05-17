/*

   Example threaded server program for sockets
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <stdbool.h>
#include <time.h>

static int serve_socket(int port)
{
    int s;
    struct sockaddr_in sn;
    struct hostent *he;

    if (!(he = gethostbyname("localhost"))) {
        puts("can't gethostname");
        exit(1);
    }

    bzero((char*)&sn, sizeof(sn));
    sn.sin_family = AF_INET;
    sn.sin_port = htons((short)port);
    sn.sin_addr.s_addr = htonl(INADDR_ANY);

    if ((s = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket()");
        exit(1);
    }

    if (bind(s, (struct sockaddr *)&sn, sizeof(sn)) == -1) {
        perror("bind()");
        exit(1);
    }

    return s;
}

static int accept_connection(int s)
{
    int x;
    struct sockaddr_in sn;

    if(listen(s, 1) == -1) {
        perror("listen()");
        exit(1);
    }

    bzero((char *)&sn, sizeof(sn));
    if((x = accept(s, (struct sockaddr *)NULL, NULL)) == -1) {
        perror("accept()");
        exit(1);
    }
    return x;
}


static const float RATE = 1.0; // updates per second

typedef struct {

    int fd;
    int sock;

} socket_info_t;

void * threadfunc(void * arg)
{
    socket_info_t * sockinfo = (socket_info_t *)arg;

    sockinfo->fd = accept_connection(sockinfo->sock);

    return NULL;
}

int main(int argc, char ** argv)
{
    // Require at least a port number on command line (host defaults to "localhost")
    
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

    // We'll use this structure to communicate with the listening thread
    socket_info_t sockinfo;

    // Serve the socket 
    sockinfo.sock = serve_socket(port);

    // Launch the listening thread
    pthread_t tcb;
    if (pthread_create(&tcb, NULL, threadfunc, &sockinfo) != 0) {
        perror("pthread_create");
    }

    // Support periodic checking for client connection
    float prevtime = 0;

    // Loop forever, receiving messages from the client and sending them back
    while (true) {

        struct timespec ts;
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts);
        float currtime =  ts.tv_sec + ts.tv_nsec / 1.e9f;

        if ((currtime - prevtime) > 1./RATE) {

            prevtime = currtime;

            if (sockinfo.fd > 0) {
                char buf[80] = "";
                read(sockinfo.fd, buf, 80);
                printf("Client said: %s\n", buf);
                strcpy(buf, "reply");
                write(sockinfo.fd, buf, strlen(buf));
            }
            else {
                printf("Listening ...\n");
            }
        }
    }

    // Shut down the listening thread
    void * status;
    if (pthread_join(tcb, &status) != 0) { 
        perror("pthread_join"); 
    }

    return 0;
}
