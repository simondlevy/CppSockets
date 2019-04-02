#
# Makefile for C++ socket examples
#
# Copyright (C) 2019 Simon D. Levy
# 
# MIT License
# 

ALL = tcpserver tcpclient udpclient

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

udpclient: udpclient.o  UdpSocketClient.o
	g++ -o udpclient udpclient.o UdpSocketClient.o

udpclient.o: ../examples/udpclient.cpp
	g++ $(CFLAGS) -I../sockets -c ../examples/udpclient.cpp

udpserver.o: ../examples/udpserver.cpp
	g++ $(CFLAGS) -I../sockets -c ../examples/udpserver.cpp

TcpSocketClient.o: ../sockets/TcpSocketClient.cpp ../sockets/TcpSocketClient.h ../sockets/TcpSocketCompat.h
	g++ $(CFLAGS) -c ../sockets/TcpSocketClient.cpp

TcpSocketServer.o: ../sockets/TcpSocketServer.cpp ../sockets/TcpSocketServer.h ../sockets/TcpSocketCompat.h
	g++ $(CFLAGS) -c ../sockets/TcpSocketServer.cpp

TcpSocketCompat.o: ../sockets/TcpSocketCompat.cpp ../sockets/TcpSocketCompat.h
	g++ $(CFLAGS) -c ../sockets/TcpSocketCompat.cpp

UdpSocketClient.o: ../sockets/UdpSocketClient.cpp ../sockets/UdpSocketClient.h
	g++ $(CFLAGS) -c ../sockets/UdpSocketClient.cpp

UdpSocket.o: ../sockets/UdpSocket.cpp ../sockets/UdpSocket.h
	g++ $(CFLAGS) -c ../sockets/UdpSocket.cpp

clean:
	rm -rf $(ALL) *.o *.csv *~ __pycache__
