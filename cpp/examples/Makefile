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

tcpserver.o: tcpserver.cpp ../TcpSocketServer.h ../TcpSocketCompat.h
	g++ $(CFLAGS) -I.. -c tcpserver.cpp

tcpclient: tcpclient.o TcpSocketClient.o TcpSocketCompat.o 
	g++ -o tcpclient tcpclient.o TcpSocketClient.o TcpSocketCompat.o 

tcpclient.o: tcpclient.cpp
	g++ $(CFLAGS) -I.. -c tcpclient.cpp

udpserver: udpserver.o
	g++ -o udpserver udpserver.o

udpserver.o: udpserver.cpp
	g++ $(CFLAGS) -c udpserver.cpp

udpclient: udpclient.o
	g++ -o udpclient udpclient.o

udpclient.o: udpclient.cpp
	g++ $(CFLAGS) -c udpclient.cpp

TcpSocketClient.o: ../TcpSocketClient.cpp ../TcpSocketClient.h ../TcpSocketCompat.h
	g++ $(CFLAGS) -c ../TcpSocketClient.cpp

TcpSocketServer.o: ../TcpSocketServer.cpp ../TcpSocketServer.h ../TcpSocketCompat.h
	g++ $(CFLAGS) -c ../TcpSocketServer.cpp

TcpSocketCompat.o: ../TcpSocketCompat.cpp ../TcpSocketCompat.h
	g++ $(CFLAGS) -c ../TcpSocketCompat.cpp

clean:
	rm -rf $(ALL) *.o *.csv *~ __pycache__
