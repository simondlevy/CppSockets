#
# Makefile for C socket examples
#
# Copyright Simon D. Levy 2018
# 
# MIT License

all: client server client2 server2

client: client.o sockettome.o
	gcc -o client client.o sockettome.o

client2: client2.o sockettome.o
	gcc -o client2 client2.o sockettome.o

server: server.o sockettome.o
	gcc -o server server.o sockettome.o

server2: server2.o sockettome.o
	gcc -o server2 server2.o sockettome.o

client.o: client.c sockettome.h
	gcc -Wall -c client.c

client2.o: client2.c sockettome.h
	gcc -Wall -c client2.c

server.o: server.c sockettome.h
	gcc -Wall -c server.c

server2.o: server2.c sockettome.h
	gcc -Wall -c server2.c

sockettome.o: sockettome.c sockettome.h
	gcc -Wall -c sockettome.c

serve2: server2
	./server2 20000

clean:
	rm -f client server *.o *~


