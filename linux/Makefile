#
# Makefile for C++ socket examples
#
# Copyright (C) 2019 Simon D. Levy
# 
# MIT License
# 

ALL = tcpserver tcpclient udpclient udpserver

all: $(ALL)

CFLAGS = -Wall -std=c++11

all: $(ALL)

tcpserver: tcpserver.o TcpSocketServer.o TcpSocketCompat.o 
	g++ -o tcpserver tcpserver.o TcpSocketServer.o TcpSocketCompat.o 

tcpserver.o: ../examples/tcpserver.cpp
	g++ $(CFLAGS) -I../sockets -c ../examples/tcpserver.cpp

tcpclient: tcpclient.o TcpSocketClient.o TcpSocketCompat.o 
	g++ -o tcpclient tcpclient.o TcpSocketClient.o TcpSocketCompat.o 

tcpclient.o: ../examples/tcpclient.cpp
	g++ $(CFLAGS) -I../sockets -c ../examples/tcpclient.cpp

udpclient: udpclient.o UdpSocketClient.o SocketCompat.o
	g++ -o udpclient udpclient.o UdpSocketClient.o SocketCompat.o

udpclient.o: ../examples/udpclient.cpp
	g++ $(CFLAGS) -I../sockets -c ../examples/udpclient.cpp

udpserver: udpserver.o  UdpSocketServer.o SocketCompat.o
	g++ -o udpserver udpserver.o UdpSocketServer.o SocketCompat.o

udpserver.o: ../examples/udpserver.cpp
	g++ $(CFLAGS) -I../sockets -c ../examples/udpserver.cpp

TcpSocketClient.o: ../sockets/TcpSocketClient.cpp ../sockets/TcpSocketClient.h ../sockets/TcpSocketCompat.h
	g++ $(CFLAGS) -c ../sockets/TcpSocketClient.cpp

TcpSocketServer.o: ../sockets/TcpSocketServer.cpp ../sockets/TcpSocketServer.h ../sockets/TcpSocketCompat.h
	g++ $(CFLAGS) -c ../sockets/TcpSocketServer.cpp

TcpSocketCompat.o: ../sockets/TcpSocketCompat.cpp ../sockets/TcpSocketCompat.h
	g++ $(CFLAGS) -c ../sockets/TcpSocketCompat.cpp

UdpSocketClient.o: ../sockets/UdpSocketClient.cpp ../sockets/UdpSocketClient.h ../sockets/SocketCompat.h
	g++ $(CFLAGS) -c ../sockets/UdpSocketClient.cpp

UdpSocketServer.o: ../sockets/UdpSocketServer.cpp ../sockets/UdpSocketServer.h ../sockets/SocketCompat.h
	g++ $(CFLAGS) -c ../sockets/UdpSocketServer.cpp

UdpSocket.o: ../sockets/UdpSocket.cpp ../sockets/UdpSocket.h
	g++ $(CFLAGS) -c ../sockets/UdpSocket.cpp

SocketCompat.o: ../sockets/SocketCompat.cpp ../sockets/SocketCompat.h
	g++ $(CFLAGS) -c ../sockets/SocketCompat.cpp

clean:
	rm -rf $(ALL) *.o *.csv *~ __pycache__
