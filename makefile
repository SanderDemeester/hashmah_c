CC=gcc
all: hashmap

hashmap: hashmap.o main.o 
	$(CC) hashmap.o main.o
main.o: main.c
	$(CC) -c main.c
hashmap.o: hashmap.c
	$(CC) -c hashmap.c
