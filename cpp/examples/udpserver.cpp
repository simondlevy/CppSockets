/* 
 * udpserver.c - A simple UDP echo server 
 * usage: udpserver <port>
 * https://www.cs.cmu.edu/afs/cs/academic/class/15213-f99/www/class26/udpserver.c
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUFSIZE 1024

class UdpSocketServer {

    private:

        int _sockfd;
        struct sockaddr_in _serveraddr; 
        struct sockaddr_in _clientaddr;
        unsigned int _clientlen = sizeof(_clientaddr);

        static void error(const char * msg)
        {
            fprintf(stderr, "%s\n", msg);
            exit(1);
        }

    public:

        UdpSocketServer(const char * host, short port)
        {
            _sockfd = socket(AF_INET, SOCK_DGRAM, 0);
            if (_sockfd < 0) {
                error("ERROR opening socket");
            }

            // setsockopt: Handy debugging trick that lets 
            // us rerun the server immediately after we kill it; 
            // otherwise we have to wait about 20 secs. 
            // Eliminates "ERROR on binding: Address already in use" error. 
            int optval = 1;
            setsockopt(_sockfd, SOL_SOCKET, SO_REUSEADDR, (const void *)&optval , sizeof(int));

            bzero((char *) &_serveraddr, sizeof(_serveraddr));
            _serveraddr.sin_family = AF_INET;
            _serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
            _serveraddr.sin_port = htons(port);

            if (bind(_sockfd, (struct sockaddr *) &_serveraddr, sizeof(_serveraddr)) < 0) {
                error("ERROR on binding");
            }
        }

        void receiveData(char  * buf, size_t len)
        {
            int n = recvfrom(_sockfd, buf, len, 0, (struct sockaddr *) &_clientaddr, &_clientlen);

            struct hostent * hostp = gethostbyaddr((const char *)&_clientaddr.sin_addr.s_addr, sizeof(_clientaddr.sin_addr.s_addr), AF_INET);
            if (hostp == NULL) {
                error("ERROR on gethostbyaddr");
            }
            char * hostaddrp = inet_ntoa(_clientaddr.sin_addr);
            if (hostaddrp == NULL) {
                error("ERROR on inet_ntoa");
            }
            printf("server received datagram from %s (%s)\n", hostp->h_name, hostaddrp);
            printf("server received %d/%d bytes: %s\n", (int)strlen(buf), n, buf);
        }

        void sendData(char * buf, size_t len)
        {
            if (sendto(_sockfd, buf, strlen(buf), 0, (struct sockaddr *) &_clientaddr, _clientlen) < 0)  {
                error("ERROR in sendto");
            }
        }
};

int main(int argc, char **argv) 
{
    if (argc < 2) {
        fprintf(stderr, "Usage:   %s PORT\n", argv[0]);
        fprintf(stderr, "Example: %s 5000\n", argv[0]);
        return 1;
    }

    UdpSocketServer server("127.0.0.1", atoi(argv[1]));

    while (true) {

        char buf[BUFSIZE];

        bzero(buf, BUFSIZE);

        server.receiveData(buf, BUFSIZE);

        server.sendData(buf, BUFSIZE);

    }
}
