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

class UdpSocketServer {

    private:

        struct sockaddr_in _si_other;
        int _s;
        int _slen = sizeof(_si_other);
        char buf[BUFLEN];
        char message[BUFLEN];

        char _message[100];

    public:

        UdpSocketServer(const char * host, short port)
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
    struct sockaddr_in si_other;
    int s, slen = sizeof(si_other);
    char buf[BUFLEN];
    char message[BUFLEN];
    WSADATA wsa;

    //Initialise winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        printf("Failed. Error Code : %d", WSAGetLastError());
        exit(EXIT_FAILURE);
    }

    //create socket
    if ((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == SOCKET_ERROR)
    {
        printf("socket() failed with error code : %d", WSAGetLastError());
        exit(EXIT_FAILURE);
    }

    //setup address structure
    memset((char *)&si_other, 0, sizeof(si_other));
    si_other.sin_family = AF_INET;
    si_other.sin_port = htons(PORT);
    //si_other.sin_addr.S_un.S_addr = inet_addr(SERVER);
    InetPton(AF_INET, _T(SERVER), &si_other.sin_addr.s_addr);

    //start communication
    while (true)
    {
        printf("Enter message : ");
        gets_s(message);

        //send the message
        if (sendto(s, message, strlen(message), 0, (struct sockaddr *) &si_other, slen) == SOCKET_ERROR)
        {
            printf("sendto() failed with error code : %d", WSAGetLastError());
            exit(EXIT_FAILURE);
        }

        //receive a reply and print it
        //clear the buffer by filling null, it might have previously received data
        memset(buf, '\0', BUFLEN);
        //try to receive some data, this is a blocking call
        if (recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen) == SOCKET_ERROR)
        {
            printf("recvfrom() failed with error code : %d", WSAGetLastError());
            exit(EXIT_FAILURE);
        }

        puts(buf);
    }

    closesocket(s);
    WSACleanup();

    return 0;
}
