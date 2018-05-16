/*

   Example client program for sockets.  

   Adapted from https://msdn.microsoft.com/en-us/library/windows/desktop/ms737591(v=vs.85).aspx

   Copyright Simon D. Levy 2018

   MIT License
 */

#include "stdafx.h"

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>


// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

static const int BUFLEN = 80;

static const char * HOST = "localhost";
static const char * PORT = "20000";

static const float RATE = 1.0; // updates per second

static void error(const char * fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    char buf[200];
    vsnprintf(buf, 200, fmt, ap);
    puts(buf);
    va_end(ap);

    while (true);
}


class SocketClient {


    private:

        SOCKET _sock; 
        bool _ready;

    public:

        SocketClient(void)
        {
            _sock = INVALID_SOCKET;
            _ready = false;
        }

        bool connected(void)
        {
            return _sock != INVALID_SOCKET;
        }

        bool ready(void)
        {
            return _ready;
        }

        void setNonblocking(void)
        {

            unsigned long iMode = 1; // non-blocking
            int iResult = ioctlsocket(_sock, FIONBIO, &iMode);
            if (iResult != NO_ERROR) {
                error("ioctlsocket failed with error: %ld\n", iResult);
            }
            else {
                _ready = true;
            }
        }

        bool talk(void)
        {
            char s[BUFLEN] = "";

            if (recv(_sock, s, BUFLEN, 0) > 0) {

                printf("Server said: %s\n", s);

                strcat_s(s, " is what you said!");
                if (send(_sock, s, (int)strlen(s), 0) == SOCKET_ERROR) {
                    closesocket(_sock);
                    WSACleanup();
                    error("send failed with error: %d\n", WSAGetLastError());
                }
            }

            // Server exited
            else if (WSAGetLastError() == WSAECONNRESET) {
                return false;
            }

            return true;
        }

        void close(void)
        {
            if (shutdown(_sock, SD_SEND) == SOCKET_ERROR) {
                closesocket(_sock);
                WSACleanup();
                error("shutdown failed with error: %d\n", WSAGetLastError());
            }
        }

        void tryConnect(void)
        {
            _sock = INVALID_SOCKET;

            // Initialize Winsock
            WSADATA wsaData;
            int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
            if (iResult != 0) {
                error("WSAStartup failed with error: %d\n", iResult);
            }

            struct addrinfo hints;
            ZeroMemory(&hints, sizeof(hints));
            hints.ai_family = AF_UNSPEC;
            hints.ai_socktype = SOCK_STREAM;
            hints.ai_protocol = IPPROTO_TCP;

            // Resolve the server address and port
            struct addrinfo *result = NULL;
            iResult = getaddrinfo(HOST, PORT, &hints, &result);
            if (iResult != 0) {
                WSACleanup();
                error("getaddrinfo failed with error: %d\n", iResult);
            }

            // Attempt to connect to an address until one succeeds
            for (struct addrinfo * ptr = result; ptr != NULL; ptr = ptr->ai_next) {

                // Create a SOCKET for connecting to server
                _sock = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
                if (_sock == INVALID_SOCKET) {
                    WSACleanup();
                    error("socket failed with error: %ld\n", WSAGetLastError());
                }

                // Connect to server.
                iResult = connect(_sock, ptr->ai_addr, (int)ptr->ai_addrlen);
                if (iResult == SOCKET_ERROR) {
                    closesocket(_sock);
                    _sock = INVALID_SOCKET;
                    continue;
                }
                break;
            }

            freeaddrinfo(result);

        }

}; // class SocketClient


int __cdecl main(int argc, char **argv)
{

    SocketClient client;

    float prevtime = 0;

    while (true) {

        SYSTEMTIME st;
        GetSystemTime(&st);
        float currtime = st.wSecond + st.wMilliseconds / 1000.;

        if ((currtime - prevtime) > 1./RATE) {

            prevtime = currtime;

            // not connected; keep trying
            if (!client.connected()) {

                printf("Attempting connection to server %s:%s\n", HOST, PORT);

                client.tryConnect();
            }

            else if (!client.ready()) {

                printf("Connected!\n");

                client.setNonblocking();
            }

            else {

                if (!client.talk()) {
                    break;
                }

            }
        }
    }

    // cleanup
    client.close();
    return 0;
}
