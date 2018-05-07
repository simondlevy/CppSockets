/*

   socket utilties, adapted from

   http://web.eecs.utk.edu/~huangj/cs360/360/notes/Sockets/socketfun.c
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <netdb.h>
#include <signal.h>

static char * inadport_decimal(struct sockaddr_in *sad)
{
    static char buf[32];
    int a;

    a = ntohl(0xffffffff & sad->sin_addr.s_addr);
    sprintf(buf, "%d.%d.%d.%d:%d",
            0xff & (a >> 24),
            0xff & (a >> 16),
            0xff & (a >> 8),
            0xff & a,
            0xffff & (int)ntohs(sad->sin_port));
    return buf;
}

int serve_socket(char * hn, int port)
{

    struct sockaddr_in sn;
    int s;
    struct hostent *he;

    if (!(he = gethostbyname(hn))) {
        puts("can't gethostname");
        exit(1);
    }

    bzero((char*)&sn, sizeof(sn));
    sn.sin_family = AF_INET;
    sn.sin_port     = htons((short)port);
    sn.sin_addr = *(struct in_addr*)(he->h_addr_list[0]);

    if ((s = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket()");
        exit(1);
    }
    if (bind(s, (struct sockaddr*)&sn, sizeof(sn)) == -1) {
        perror("bind()");
        exit(1);
    }

    return s;
}

int accept_connection(int s)
{
    int l;
    struct sockaddr_in sn;
    int x;

    sn.sin_family = AF_INET;

    if (listen(s, 1) == -1) {
        perror("listen()");
        exit(1);
    }

    l = sizeof(sn);
    if ((x = accept(s, (struct sockaddr*)&sn, &l)) == -1) {
        perror("accept()");
        exit(1);
    }
    return x;
}

#ifndef	ALB

int request_connection(char * hn, int port)
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
        sn.sin_family = AF_INET;
        sn.sin_port  = htons((short)port);
        sn.sin_addr.s_addr = *(u_long*)(he->h_addr_list[0]);

        if ((s = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
            perror("socket()");
            exit(1);
        }
        ok = (connect(s, (struct sockaddr*)&sn, sizeof(sn)) != -1);
        if (!ok) sleep (1);
    }
    return s;
}

#else	ALB

int request_connection(char * hn, int port)
{
    char easy[BUFSIZ];
    int ok;

    sprintf(easy, "proxy!%s!%d", hn, port);
    while ((ok = ipcopen(easy, "")) < 0)
        sleep(1);
    return ok;
}

#endif	ALB

