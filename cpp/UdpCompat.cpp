/*
 * UdpCompat.cpp: cross-platform compatibility superclass for UDP sockets
 *
 * Copyright (C) 2019 Simon D. Levy
 *
 * MIT License
 */

#include "SocketCompat.h"

bool SocketCompat::sendData(void *buf, size_t len)
{
    return (size_t)send(_conn, (const char *)buf, len, 0) == len;
}

bool SocketCompat::receiveData(void *buf, size_t len)
{
    return (size_t)recv(_conn, (char *)buf, len, 0) == len;
}
