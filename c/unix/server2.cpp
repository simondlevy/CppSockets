/*

   Example threaded server program for sockets
 */

#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <stdbool.h>
#include <time.h>


typedef struct {

    int fd;
    int sock;

} socket_info_t;

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

void * threadfunc(void * arg)
{
    socket_info_t * sockinfo = (socket_info_t *)arg;

    sockinfo->fd = accept_connection(sockinfo->sock);

    return NULL;
}

class ThreadedSocketServer {

    private:

        socket_info_t _sockinfo;
        pthread_t _thread;

    public:

        ThreadedSocketServer(int port) 
        {
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

            if ((_sockinfo.sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
                perror("socket()");
                exit(1);
            }

            if (bind(_sockinfo.sock, (struct sockaddr *)&sn, sizeof(sn)) == -1) {
                perror("bind()");
                exit(1);
            }
            
            _sockinfo.fd = 0;
        }

        void start(void)
        {
            if (pthread_create(&_thread, NULL, threadfunc, &_sockinfo) != 0) {
                perror("pthread_create");
            }

        }

        void stop(void)
        {
            void * status;
            if (pthread_join(_thread, &status) != 0) { 
                perror("pthread_join"); 
            }
        }

        bool connected(void)
        {
            return _sockinfo.fd > 0;
        }

        int send(char * buf, int len)
        {
            return write(_sockinfo.fd, buf, len);
        }

        int recv(char * buf, int len)
        {
            return read(_sockinfo.fd, buf, len);
        }

};

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
                server.recv(buf, 80);
                printf("Client said: %s\n", buf);
                strcpy(buf, "reply");
                server.send(buf, strlen(buf));
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
