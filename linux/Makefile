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

tcpserver: tcpserver.o 
	g++ -o tcpserver tcpserver.o 

tcpserver.o: ../examples/tcpserver.cpp
	g++ $(CFLAGS) -I../sockets -c ../examples/tcpserver.cpp

tcpclient: tcpclient.o 
	g++ -o tcpclient tcpclient.o 

tcpclient.o: ../examples/tcpclient.cpp
	g++ $(CFLAGS) -I../sockets -c ../examples/tcpclient.cpp

udpclient: udpclient.o 
	g++ -o udpclient udpclient.o 

udpclient.o: ../examples/udpclient.cpp
	g++ $(CFLAGS) -I../sockets -c ../examples/udpclient.cpp

udpserver: udpserver.o  
	g++ -o udpserver udpserver.o 

udpserver.o: ../examples/udpserver.cpp
	g++ $(CFLAGS) -I../sockets -c ../examples/udpserver.cpp

clean:
	rm -rf $(ALL) *.o *.csv *~ __pycache__
