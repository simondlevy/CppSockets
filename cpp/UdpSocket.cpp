#include "UdpSocket.h"

void UdpSocket::error(const char * msg)
{
    fprintf(stderr, "%s\n", msg);
    exit(1);
}

