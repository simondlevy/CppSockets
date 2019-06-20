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

tcpserver: tcpserver.o SocketCompat.o
	g++ -o tcpserver tcpserver.o SocketCompat.o

tcpserver.o: ../examples/tcpserver.cpp
	g++ $(CFLAGS) -I../sockets -c ../examples/tcpserver.cpp

tcpclient: tcpclient.o TcpClientSocket.o SocketCompat.o
	g++ -o tcpclient tcpclient.o TcpClientSocket.o SocketCompat.o

tcpclient.o: ../examples/tcpclient.cpp
	g++ $(CFLAGS) -I../sockets -c ../examples/tcpclient.cpp

udpclient: udpclient.o SocketCompat.o 
	g++ -o udpclient udpclient.o SocketCompat.o

udpclient.o: ../examples/udpclient.cpp
	g++ $(CFLAGS) -I../sockets -c ../examples/udpclient.cpp

udpserver: udpserver.o  SocketCompat.o 
	g++ -o udpserver udpserver.o SocketCompat.o

udpserver.o: ../examples/udpserver.cpp
	g++ $(CFLAGS) -I../sockets -c ../examples/udpserver.cpp

TcpClientSocket.o: ../sockets/TcpClientSocket.cpp ../sockets/TcpClientSocket.h ../sockets/TcpSocket.hpp
	g++ $(CFLAGS) -c ../sockets/TcpClientSocket.cpp

SocketCompat.o: ../sockets/SocketCompat.cpp ../sockets/SocketCompat.h
	g++ $(CFLAGS) -c ../sockets/SocketCompat.cpp

clean:
	rm -rf $(ALL) *.o *.csv *~ __pycache__
