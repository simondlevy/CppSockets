#
# Makefile for C++ socket examples
#
# Copyright (C) 2019 Simon D. Levy
# 
# MIT License
# 

ALL = udpserver udpclient

all: $(ALL)

CFLAGS = -Wall -std=c++11

all: $(ALL)

udpserver: udpserver.o
	g++ -o udpserver udpserver.o

udpserver.o: udpserver.cpp
	g++ $(CFLAGS) -c udpserver.cpp

udpclient: udpclient.o
	g++ -o udpclient udpclient.o

udpclient.o: udpclient.cpp
	g++ $(CFLAGS) -c udpclient.cpp

clean:
	rm -rf $(ALL) *.o *.csv *~ __pycache__
