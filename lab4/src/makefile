all : parallel_min_max mem

mem : process_memory.c
	gcc -o -I process_memory process_memory.c

parallel_min_max : utils.o find_min_max.o 
	gcc -o -I parallel_min_max utils.o find_min_max.o parallel_min_max.c
