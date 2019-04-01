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

tcpserver: tcpserver.o SocketServer.o SocketCompat.o
	g++ -o tcpserver tcpserver.o SocketServer.o SocketCompat.o

tcpserver.o: tcpserver.cpp ../SocketServer.h ../SocketCompat.h
	g++ $(CFLAGS) -I.. -c tcpserver.cpp

tcpclient: tcpclient.o
	g++ -o tcpclient tcpclient.o

tcpclient.o: tcpclient.cpp
	g++ $(CFLAGS) -c tcpclient.cpp

udpserver: udpserver.o
	g++ -o udpserver udpserver.o

udpserver.o: udpserver.cpp
	g++ $(CFLAGS) -c udpserver.cpp

udpclient: udpclient.o
	g++ -o udpclient udpclient.o

udpclient.o: udpclient.cpp
	g++ $(CFLAGS) -c udpclient.cpp

SocketServer.o: ../SocketServer.cpp ../SocketServer.h ../SocketCompat.h
	g++ $(CFLAGS) -c ../SocketServer.cpp

SocketCompat.o: ../SocketCompat.cpp ../SocketCompat.h
	g++ $(CFLAGS) -c ../SocketCompat.cpp

clean:
	rm -rf $(ALL) *.o *.csv *~ __pycache__
