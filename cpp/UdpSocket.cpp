#include "UdpSocket.h"

UdpSocket::UdpSocket(const char * host, short port)
{
    _sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (_sockfd < 0) {
        error("ERROR opening socket");
    }

    bzero((char *) &_serveraddr, sizeof(_serveraddr));
    _serveraddr.sin_family = AF_INET;
    _serveraddr.sin_port = htons(port);
}

void UdpSocket::error(const char * msg)
{
    fprintf(stderr, "%s\n", msg);
    exit(1);
}

