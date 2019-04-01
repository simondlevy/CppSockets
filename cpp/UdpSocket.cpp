#include "UdpSocket.h"

UdpSocket::UdpSocket(const char * host, short port)
{
    _sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (_sockfd < 0) {
        error("ERROR opening socket");
    }
}

void UdpSocket::error(const char * msg)
{
    fprintf(stderr, "%s\n", msg);
    exit(1);
}

