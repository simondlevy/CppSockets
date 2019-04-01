/*
 * Test code for UDP socket client
 *
 * Copyright (C) 2019 Simon D. Levy
 *
 * MIT License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

class UdpSocketClient {

    private:

        int _sockfd;
        struct sockaddr_in _serveraddr;
        unsigned int _serverlen = sizeof(_serveraddr);

        void error(const char * msg)
        {
            fprintf(stderr, "%s\n", msg);
            exit(1);
        }

    public:

        UdpSocketClient(const char * host, short port)
        {
            _sockfd = socket(AF_INET, SOCK_DGRAM, 0);
            if (_sockfd < 0) {
                error("ERROR opening socket");
            }

            struct hostent * server = gethostbyname(host);
            if (server == NULL) {
                fprintf(stderr,"ERROR, no such host as %s\n", host);
                exit(0);
            }

            bzero((char *) &_serveraddr, sizeof(_serveraddr));
            _serveraddr.sin_family = AF_INET;
            bcopy((char *)server->h_addr, (char *)&_serveraddr.sin_addr.s_addr, server->h_length);
            _serveraddr.sin_port = htons(port);
        }

        bool sendData(char *buf, size_t len)
        {
            return (size_t)sendto(_sockfd, buf, strlen(buf), 0, (const sockaddr *)&_serveraddr, _serverlen) == len;
        }

        bool receiveData(char *buf, size_t len)
        {
            return (size_t)recvfrom(_sockfd, buf, strlen(buf), 0, (sockaddr *)&_serveraddr, &_serverlen) == len;
        }
};

int main(int argc, char **argv) 
{
    char buf[100];

    if (argc < 3) {
        fprintf(stderr, "Usage:   %s HOST PORT\n", argv[0]);
        fprintf(stderr, "Example: %s localhost 5000\n", argv[0]);
        return 1;
    }

    bzero(buf, 100);
    printf("Please enter msg: ");
    fgets(buf, 100, stdin);

    UdpSocketClient client(argv[1], atoi(argv[2]));

    client.sendData(buf, strlen(buf));

    client.receiveData(buf, strlen(buf));

    return 0;
}
