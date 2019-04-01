#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <arpa/inet.h>

class UdpSocket {

    protected:

        UdpSocket(const char * host, short port);

        int _sockfd;

        struct sockaddr_in _serveraddr;

        void error(const char * msg);
};
