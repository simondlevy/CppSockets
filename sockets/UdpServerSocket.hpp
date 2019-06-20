/*
 * UdpServerSocket.h: class for UDP server sockets
 *
 * Copyright (C) 2019 Simon D. Levy
 *
 * MIT License
 */

#pragma once

#include "UdpSocket.hpp"

class UdpServerSocket : public UdpSocket {

    public:

        UdpServerSocket(const short port)
        {
            // Initialize Winsock, returning on failure
            if (!initWinsock()) return;

            // Create socket
            _sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
            if (_sock == INVALID_SOCKET) {
                sprintf_s(_message, "socket() failed");
                return;
            }

            // Prepare the sockaddr_in structure
            struct sockaddr_in server;
            server.sin_family = AF_INET;
            server.sin_addr.s_addr = INADDR_ANY;
            server.sin_port = htons(port);

            // Bind
            if (bind(_sock, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR) {
                sprintf_s(_message, "bind() failed");
                return;
            }
        }
};
