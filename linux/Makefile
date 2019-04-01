#
# Makefile for C++ socket examples
#
# Copyright (C) 2019 Simon D. Levy
# 
# MIT License
# 

ALL = tcpserver tcpclient udpserver udpclient

all: $(ALL)

CFLAGS = -Wall -std=c++11

all: $(ALL)

tcpserver: tcpserver.o TcpSocketServer.o TcpSocketCompat.o 
	g++ -o tcpserver tcpserver.o TcpSocketServer.o TcpSocketCompat.o 

tcpserver.o: tcpserver.cpp
	g++ $(CFLAGS) -I../sockets -c tcpserver.cpp

tcpclient: tcpclient.o TcpSocketClient.o TcpSocketCompat.o 
	g++ -o tcpclient tcpclient.o TcpSocketClient.o TcpSocketCompat.o 

tcpclient.o: tcpclient.cpp
	g++ $(CFLAGS) -I../sockets -c tcpclient.cpp

udpserver: udpserver.o UdpSocketServer.o UdpSocket.o
	g++ -o udpserver udpserver.o UdpSocketServer.o UdpSocket.o

udpserver.o: udpserver.cpp 
	g++ $(CFLAGS) -I../sockets -c udpserver.cpp

udpclient: udpclient.o  UdpSocketClient.o UdpSocket.o
	g++ -o udpclient udpclient.o UdpSocketClient.o UdpSocket.o

udpclient.o: udpclient.cpp
	g++ $(CFLAGS) -I../sockets -c udpclient.cpp

TcpSocketClient.o: ../sockets/TcpSocketClient.cpp ../sockets/TcpSocketClient.h ../sockets/TcpSocketCompat.h
	g++ $(CFLAGS) -c ../sockets/TcpSocketClient.cpp

TcpSocketServer.o: ../sockets/TcpSocketServer.cpp ../sockets/TcpSocketServer.h ../sockets/TcpSocketCompat.h
	g++ $(CFLAGS) -c ../sockets/TcpSocketServer.cpp

TcpSocketCompat.o: ../sockets/TcpSocketCompat.cpp ../sockets/TcpSocketCompat.h
	g++ $(CFLAGS) -c ../sockets/TcpSocketCompat.cpp

UdpSocketServer.o: ../sockets/UdpSocketServer.cpp ../sockets/UdpSocketServer.h
	g++ $(CFLAGS) -c ../sockets/UdpSocketServer.cpp

UdpSocketClient.o: ../sockets/UdpSocketClient.cpp ../sockets/UdpSocketClient.h
	g++ $(CFLAGS) -c ../sockets/UdpSocketClient.cpp

UdpSocket.o: ../sockets/UdpSocket.cpp ../sockets/UdpSocket.h
	g++ $(CFLAGS) -c ../sockets/UdpSocket.cpp

clean:
	rm -rf $(ALL) *.o *.csv *~ __pycache__
