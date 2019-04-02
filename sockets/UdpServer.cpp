#include <iostream>
#include<stdio.h>
#include<winsock2.h>

#pragma comment(lib,"ws2_32.lib") //Winsock Library

#define BUFLEN 512	//Max length of buffer
#define PORT 8888	//The port on which to listen for incoming data

class UdpSocketServer {

    private:

        SOCKET _s;
        struct sockaddr_in _server;
        struct sockaddr_in _si_other;
        int _recv_len;
        int _slen = sizeof(_si_other);
        char _message[100];

    public:

        UdpSocketServer(const short port)
        {
            WSADATA wsa;
            if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
                sprintf_s(_message, "Failed. Error Code : %d", WSAGetLastError());
                return;
            }

            _s = socket(AF_INET, SOCK_DGRAM, 0);
            if (_s == INVALID_SOCKET) {
                sprintf_s(_message, "socket() failed");
                return;
            }

            // Prepare the sockaddr_in structure
            _server.sin_family = AF_INET;
            _server.sin_addr.s_addr = INADDR_ANY;
            _server.sin_port = htons(port);

            // Bind
            if (bind(_s, (struct sockaddr *)&_server, sizeof(_server)) == SOCKET_ERROR) {
                sprintf_s(_message, "bind() failed");
                return;
            }
        }

        bool sendData(void * buf, size_t len)
        {
            return sendto(_s, (const char *)buf, (int)len, 0, (struct sockaddr *) &_si_other, (int)_slen) != SOCKET_ERROR;
        }

        bool receiveData(void * buf, size_t len)
        {
            return recvfrom(_s, (char *)buf, (int)len, 0, (struct sockaddr *) &_si_other, &_slen) != SOCKET_ERROR;
        }

        void closeConnection(void)
        {
            closesocket(_s);
            WSACleanup();
        }
};

int main()
{
    char buf[BUFLEN];

    UdpSocketServer server(PORT);

    while (true) {

        printf("Waiting for data...");
        fflush(stdout);

        memset(buf, 0, BUFLEN);

        server.receiveData(buf, BUFLEN);

        printf("Data: %s\n", buf);

        server.sendData(buf, strlen(buf));
    }

    server.closeConnection();

    return 0;
}
