/*
	Simple udp client
	Silver Moon (m00n.silv3r@gmail.com)
*/

#include "pch.h"
#include <iostream>
#include<stdio.h>
#include<winsock2.h>
#include <WS2tcpip.h>
#include <tchar.h>

#pragma comment(lib,"ws2_32.lib") //Winsock Library

#define SERVER "127.0.0.1"	//ip address of udp server
#define BUFLEN 512	//Max length of buffer
#define PORT 8888	//The port on which to listen for incoming data

class UdpSocketClient {

    public:

        struct sockaddr_in _si_other;
        int _s;
        int _slen = sizeof(_si_other);

        char _message[100];

    public:

        UdpSocketClient(void)
        {
            // Initialise winsock
            WSADATA wsa;
            if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
                sprintf_s(_message, "Failed. Error Code : %d", WSAGetLastError());
                return;
            }

            // Create socket
            if ((_s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == SOCKET_ERROR) {
                sprintf_s(_message, "socket() failed with error code : %d", WSAGetLastError());
                return;
            }

            // Setup address structure
            memset((char *)&_si_other, 0, sizeof(_si_other));
            _si_other.sin_family = AF_INET;
            _si_other.sin_port = htons(PORT);
            //si_other.sin_addr.S_un.S_addr = inet_addr(SERVER);
            InetPton(AF_INET, _T(SERVER), &_si_other.sin_addr.s_addr);
        }

        bool sendData(void * buf, size_t len)
        {
            return sendto(_s, (const char *)buf, len, 0, (struct sockaddr *) &_si_other, _slen) != SOCKET_ERROR;
        }

        bool receiveData(void * buf, size_t len)
        {
            return recvfrom(_s, (char *)buf, len, 0, (struct sockaddr *) &_si_other, &_slen) != SOCKET_ERROR;
        }
};

int main(void)
{
    char buf[BUFLEN];
    char message[BUFLEN];

    UdpSocketClient client;

    //start communication
    while (true)
    {
        printf("Enter message : ");
        gets_s(message);

        client.sendData(message, strlen(message));

        memset(buf, '\0', BUFLEN);

        client.receiveData(buf, BUFLEN);

        puts(buf);
    }

    closesocket(client._s);
    WSACleanup();

    return 0;
}
