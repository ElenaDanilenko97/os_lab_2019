CC=gcc
CFLAGS=-I.

all: mem parallel_min_max par_sum

mem: process_memory.c
	$(CC) -o mem process_memory.c $(CFLAGS)

parallel_min_max: utils.o find_min_max.o utils.h find_min_max.h
	$(CC) -o parallel_min_max utils.o find_min_max.o parallel_min_max.c $(CFLAGS)

par_sum: parallel_sum.o utils.o libsum.a
	$(CC) -o par_sum parallel_sum.o utils.o -L. -lsum -lpthread

utils.o: utils.h
	$(CC) -o utils.o -c utils.c $(CFLAGS)

find_min_max.o: utils.h find_min_max.h
	$(CC) -o find_min_max.o -c find_min_max.c $(CFLAGS)

libsum.a: sum.o
	ar cr libsum.a sum.o

sum.o: sum.c
	$(CC) -o sum.o -c sum.c


clean:
	rm utils.o find_min_max.o parallel_min_max

