#
# Makefile for C socket examples
#
# Copyright Simon D. Levy 2018
# 
# MIT License

all: client server client2

client: client.o sockettome.o
	gcc -o client client.o sockettome.o

client2: client2.o sockettome.o
	gcc -o client2 client2.o sockettome.o

server: server.o sockettome.o
	gcc -o server server.o sockettome.o

client.o: client.c sockettome.h
	gcc -Wall -c client.c

client2.o: client2.c sockettome.h
	gcc -Wall -c client2.c

server.o: server.c sockettome.h
	gcc -Wall -c server.c

sockettome.o: sockettome.c sockettome.h
	gcc -Wall -c sockettome.c

clean:
	rm -f client server *.o *~


