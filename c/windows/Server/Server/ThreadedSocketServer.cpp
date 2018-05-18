/*

Windows implementation of threaded socket server

Copyright Simon D. Levy 2018

MIT License
*/

#include "stdafx.h"

#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "ThreadedSocketServer.h"

typedef struct {

	SOCKET ListenSocket;
	SOCKET ClientSocket;

} socket_info_t;

ThreadedSocketServer::ThreadedSocketServer(int port)
{
	socket_info_t * sockinfo = new socket_info_t;
	sockinfo->ListenSocket = INVALID_SOCKET;
	sockinfo->ClientSocket = INVALID_SOCKET;
	_sockinfo = (void *)sockinfo;

	WSADATA wsaData;
	int iResult;

	SOCKET ClientSocket = INVALID_SOCKET;

	struct addrinfo *result = NULL;
	struct addrinfo hints;

	int iSendResult;
	int recvbuflen = BUFLEN;

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed with error: %d\n", iResult);
		return;
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	// Resolve the server address and port
	char portstr[20];
	sprintf_s(portstr, "%d", port);
	iResult = getaddrinfo(NULL, portstr, &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed with error: %d\n", iResult);
		WSACleanup();
	}

	// Create a SOCKET for connecting to server
	sockinfo->ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (sockinfo->ListenSocket == INVALID_SOCKET) {
		printf("socket failed with error: %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		return;
	}

	// Setup the TCP listening socket
	iResult = bind(sockinfo->ListenSocket, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		printf("bind failed with error: %d\n", WSAGetLastError());
		freeaddrinfo(result);
		closesocket(sockinfo->ListenSocket);
		WSACleanup();
		return;
	}

	freeaddrinfo(result);
}

bool ThreadedSocketServer::start(void)
{
	socket_info_t * sockinfo = (socket_info_t *)_sockinfo;

	int iResult = listen(sockinfo->ListenSocket, SOMAXCONN);
	if (iResult == SOCKET_ERROR) {
		printf("listen failed with error: %d\n", WSAGetLastError());
		closesocket(sockinfo->ListenSocket);
		WSACleanup();
		return false;
	}

	// Accept a client socket
	sockinfo->ClientSocket = accept(sockinfo->ListenSocket, NULL, NULL);
	if (sockinfo->ClientSocket == INVALID_SOCKET) {
		printf("accept failed with error: %d\n", WSAGetLastError());
		closesocket(sockinfo->ListenSocket);
		WSACleanup();
		return false;
	}

	// No longer need server socket
	closesocket(sockinfo->ListenSocket);

	return true;
}

void ThreadedSocketServer::stop(void)
{
	socket_info_t * sockinfo = (socket_info_t *)_sockinfo;

	int iResult = shutdown(sockinfo->ClientSocket, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		printf("shutdown failed with error: %d\n", WSAGetLastError());
		closesocket(sockinfo->ClientSocket);
		WSACleanup();
		return;
	}

	// cleanup
	closesocket(sockinfo->ClientSocket);
	WSACleanup();
}

bool ThreadedSocketServer::connected(void)
{
	return true;
}

int ThreadedSocketServer::sendBuffer(char * buf, int len)
{
	socket_info_t * sockinfo = (socket_info_t *)_sockinfo;

	// Echo the buffer back to the sender
	int iSendResult = send(sockinfo->ClientSocket, buf, len, 0);
	if (iSendResult == SOCKET_ERROR) {
		closesocket(sockinfo->ClientSocket);
		WSACleanup();
		return 0;
	}
	return iSendResult;
}

int ThreadedSocketServer::receiveBuffer(char * buf, int len)
{
	socket_info_t * sockinfo = (socket_info_t *)_sockinfo;

	return recv(sockinfo->ClientSocket, buf, len, 0);

}