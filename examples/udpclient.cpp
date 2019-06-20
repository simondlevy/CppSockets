/*
 * udpclient.cpp test code for UDP client sockets
 *
 * Copyright (C) 2019 Simon D. Levy
 *
 * MIT License
 */

#include <UdpClientSocket.hpp>

#include <stdio.h>
#include <string.h>

const char * HOST = "127.0.0.1";
const short  PORT = 8888;

static const short BUFLEN = 512;

int main(void)
{
    char messageIn[BUFLEN];
    char messageOut[BUFLEN];

    UdpClientSocket client(HOST, PORT);

    while (true)
    {
        printf("Enter message : ");
        fgets(messageOut, BUFLEN, stdin);

        client.sendData(messageOut, strlen(messageOut));

		memset(messageIn, 0, BUFLEN);

        client.receiveData(messageIn, BUFLEN);

        printf("%s\n", messageIn);
    }

    client.closeConnection();

    return 0;
}
