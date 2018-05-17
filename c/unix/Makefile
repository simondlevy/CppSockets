#
# Makefile for C socket examples
#
# Copyright Simon D. Levy 2018
# 
# MIT License

CC = g++

all: client server client2 server2

client: client.o sockettome.o
	$(CC) -o client client.o sockettome.o

client2: client2.o sockettome.o
	$(CC) -o client2 client2.o sockettome.o

server: server.o sockettome.o
	$(CC) -o server server.o sockettome.o

server2: server2.o sockettome.o
	$(CC) -o server2 server2.o sockettome.o -lpthread

client.o: client.c sockettome.h
	$(CC) -Wall -c client.c

client2.o: client2.c sockettome.h
	$(CC) -Wall -c client2.c

server.o: server.c sockettome.h
	$(CC) -Wall -c server.c

server2.o: server2.cpp sockettome.h
	$(CC) -Wall -c server2.cpp

sockettome.o: sockettome.c sockettome.h
	$(CC) -Wall -c sockettome.c

serve2: server2
	./server2 20000

clean:
	rm -f client server *.o *~


