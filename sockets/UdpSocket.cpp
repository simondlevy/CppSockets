/*
 * UdpSocket.cpp code for UDP sockets
 *
 * Copyright (C) 2019 Simon D. Levy
 *
 * MIT License
 */

#include "UdpSocket.h"

bool UdpSocket::sendData(void * buf, size_t len)
{
    return sendto(_sock, (const char *)buf, (int)len, 0, (struct sockaddr *) &_si_other, (int)_slen) != SOCKET_ERROR;
}

bool UdpSocket::receiveData(void * buf, size_t len)
{
    return recvfrom(_sock, (char *)buf, (int)len, 0, (struct sockaddr *) &_si_other, &_slen) != SOCKET_ERROR;
}
