CC=gcc
FLAGS=-I.

.PHONY: all clean

all: server client

server: multmodulo.o multmodulo.h
	$(CC) multmodulo.o server.c -o server -lpthread $(FLAGS)

client: multmodulo.o multmodulo.h
	$(CC) multmodulo.o client.c -o client $(FLAGS)

MultModulo.o: multmodulo.h
	$(CC) -c multmodulo.c -o multmodulo.o $(FLAGS)

clean:
	rm server client ports_list.txt multmodulo.o