/*
 * UdpClient.cpp test code for UDP client sockets
 *
 * Copyright (C) 2019 Simon D. Levy
 *
 * MIT License
 */

#include <UdpSocketClient.h>

#include <stdio.h>
#include <string.h>

const char * HOST = "127.0.0.1";
const short  PORT = 8888;

#define BUFLEN 512	//Max length of buffer

int main(void)
{
    char messageIn[BUFLEN];
    char messageOut[BUFLEN];

    UdpSocketClient client(HOST, PORT);

    while (true)
    {
        printf("Enter message : ");
        gets_s(messageOut);

        client.sendData(messageOut, strlen(messageOut));

		memset(messageIn, 0, BUFLEN);

        client.receiveData(messageIn, BUFLEN);

        puts(messageIn);
    }

    client.closeConnection();

    return 0;
}
