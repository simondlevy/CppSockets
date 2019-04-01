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
	g++ $(CFLAGS) -I../src -c tcpserver.cpp

tcpclient: tcpclient.o TcpSocketClient.o TcpSocketCompat.o 
	g++ -o tcpclient tcpclient.o TcpSocketClient.o TcpSocketCompat.o 

tcpclient.o: tcpclient.cpp
	g++ $(CFLAGS) -I../src -c tcpclient.cpp

udpserver: udpserver.o UdpSocketServer.o UdpSocket.o
	g++ -o udpserver udpserver.o UdpSocketServer.o UdpSocket.o

udpserver.o: udpserver.cpp 
	g++ $(CFLAGS) -I../src -c udpserver.cpp

udpclient: udpclient.o  UdpSocketClient.o UdpSocket.o
	g++ -o udpclient udpclient.o UdpSocketClient.o UdpSocket.o

udpclient.o: udpclient.cpp
	g++ $(CFLAGS) -I../src -c udpclient.cpp

TcpSocketClient.o: ../src/TcpSocketClient.cpp ../src/TcpSocketClient.h ../src/TcpSocketCompat.h
	g++ $(CFLAGS) -c ../src/TcpSocketClient.cpp

TcpSocketServer.o: ../src/TcpSocketServer.cpp ../src/TcpSocketServer.h ../src/TcpSocketCompat.h
	g++ $(CFLAGS) -c ../src/TcpSocketServer.cpp

TcpSocketCompat.o: ../src/TcpSocketCompat.cpp ../src/TcpSocketCompat.h
	g++ $(CFLAGS) -c ../src/TcpSocketCompat.cpp

UdpSocketServer.o: ../src/UdpSocketServer.cpp ../src/UdpSocketServer.h
	g++ $(CFLAGS) -c ../src/UdpSocketServer.cpp

UdpSocketClient.o: ../src/UdpSocketClient.cpp ../src/UdpSocketClient.h
	g++ $(CFLAGS) -c ../src/UdpSocketClient.cpp

UdpSocket.o: ../src/UdpSocket.cpp ../src/UdpSocket.h
	g++ $(CFLAGS) -c ../src/UdpSocket.cpp

clean:
	rm -rf $(ALL) *.o *.csv *~ __pycache__
