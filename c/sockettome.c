// Adapted from http://web.eecs.utk.edu/~plank/plank/classes/cs360/360/notes/Sockets/sockettome.c

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <netdb.h>
#include <signal.h>
#include <strings.h>

#include "sockettome.h"

int serve_socket(int port)
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

int accept_connection(int s)
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

int request_connection(char *hn, int port)
{
    struct sockaddr_in sn;
    int s, ok;
    struct hostent *he;

    if (!(he = gethostbyname(hn))) {
        puts("can't gethostname");
        exit(1);
    } 
    ok = 0;
    while (!ok) {
        bzero((char *)&sn,sizeof(sn));
        sn.sin_family = AF_INET;
        sn.sin_port  = htons((short)port);
        sn.sin_addr = *(struct in_addr *)(he->h_addr_list[0]);

        if ((s = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
            perror("socket()");
            exit(1);
        }
        ok = (connect(s, (struct sockaddr*)&sn, sizeof(sn)) != -1);
        if (!ok) { sleep (1); perror("connect():"); }
    }
    return s;
}
