/*
 * SocketServer.cpp: general-purpose socket server code
 *
 * Copyright (C) 2019 Simon D. Levy
 *
 * MIT License
 */

#include "SocketServer.h"

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#ifndef _WIN32
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>

SocketServer::SocketServer(const char * host, short port)
{
    // acceptConnection() will use these for reporting
    strcpy(_host, host);
    _port = port;

    // Set up to work on localhost, exiting on failure
    struct hostent *he = gethostbyname(_host);
    if (!he) {
        sprintf(_message, "gethostbyname() failed");
        return;
    }

    // Create socket, exiting on failure
    _sock = socket(AF_INET, SOCK_STREAM, 0);
    if (_sock == -1) {
        sprintf(_message, "socket() failed");
        return;
    }

    // Set up socket address
    struct sockaddr_in sn = {0};
    sn.sin_family = AF_INET;
    sn.sin_port   = htons(_port);
    sn.sin_addr = *(struct in_addr*)(he->h_addr_list[0]);

    // Bind socket to address, exiting on failure
    if (bind(_sock, (struct sockaddr*)&sn, sizeof(sn)) == -1) {
        sprintf(_message, "bind() failed");
    }
}

void SocketServer::acceptConnection(void)
{
    // Listen for a connection, exiting on failure
    if (listen(_sock, 1)  == -1) {
        sprintf(_message, "listen() failed");
        return;
    }

    // Accept connection, exiting on failure
    printf("Waiting for client to connect on %s:%d ... ", _host, _port);
    fflush(stdout);
    _conn = accept(_sock, (struct sockaddr *)NULL, NULL);
    if (_conn == -1) {
        sprintf(_message, "accept() failed");
        return;
    }
    printf("connected\n");
    fflush(stdout);
}

bool SocketServer::sendData(void * buf, size_t len)
{
    return (size_t)send(_conn, buf, len, 0)  == len;
}

bool SocketServer::receiveData(void * buf, size_t len)
{
    size_t got = (size_t)recv(_conn, buf, len, 0);
    //printf("%ld bytes received\n", got);
    //fflush(stdout);
    return got == len;
}

void SocketServer::closeConnection(void)
{
    close(_conn);
}

#endif
