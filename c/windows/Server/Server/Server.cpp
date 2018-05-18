// See https://msdn.microsoft.com/en-us/library/windows/desktop/ms737593(v=vs.85).aspx

#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "ThreadedSocketServer.h"

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")

static const int PORT = 20000;

int __cdecl main(void)
{
	ThreadedSocketServer server(PORT);

	printf("Listening for client on port %d...", PORT);

	if (!server.start()) {
		printf("Listen faled\n");
		return 1;
	}
	printf(" client connected\n");

	// Receive until the peer shuts down the connection
	while (true) {

		char recvbuf[ThreadedSocketServer::BUFLEN] = "";

		int iResult = server.receiveBuffer(recvbuf, ThreadedSocketServer::BUFLEN);

		if (iResult > 0) {

			printf("Received: %s\n", recvbuf);

			strcat_s(recvbuf, " is what you said, client!");

			iResult = server.sendBuffer(recvbuf, strlen(recvbuf));
		}

		else {

			break;
		}
	} 

	server.stop();

	return 0;
}

