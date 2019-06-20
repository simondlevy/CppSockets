/*
 * Cross-platform compatibility superclass for sockets
 *
 * Copyright (C) 2019 Simon D. Levy
 *
 * MIT License
 */

#pragma once

// Windows
#ifdef _WIN32
#pragma comment(lib,"ws2_32.lib")
#define WIN32_LEAN_AND_MEAN
#undef TEXT
#include <winsock2.h>
#include <ws2tcpip.h>

// Linux
#else
#define sprintf_s sprintf
typedef int SOCKET;
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
static const int INVALID_SOCKET = -1;
static const int SOCKET_ERROR   = -1;
#endif

#include <stdio.h>

class Socket {

    protected:

        SOCKET _sock;

        char _message[200];

        bool initWinsock(void)
        {
#ifdef _WIN32
            WSADATA wsaData;
            int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
            if (iResult != 0) {
                sprintf_s(_message, "WSAStartup() failed with error: %d\n", iResult);
                return false;
            }
#endif
            return true;
        }

        void cleanup(void)
        {
#ifdef _WIN32
            WSACleanup();
#endif
        }

        void inetPton(const char * host, struct sockaddr_in & saddr_in)
        {
#ifdef _WIN32
            WCHAR wsz[64];
            swprintf_s(wsz, L"%S", host);
            InetPton(AF_INET, wsz,   &(saddr_in.sin_addr.s_addr));
#else
            inet_pton(AF_INET, host, &(saddr_in.sin_addr));
#endif
        }

    public:

        void closeConnection(void)
        {
#ifdef _WIN32
            closesocket(_sock);
#else
            close(_sock);
#endif
        }

        char * getMessage(void)
        {
            return _message;
        }
};
