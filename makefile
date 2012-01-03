CC=gcc
all: hashmap

hashmap: hashmap.o main.o 
	$(CC) hashmap.o main.o
main.o: main.c
	$(CC) -c main.c
hashmap.o: hashmap.c
	$(CC) -c hashmap.c
clean:
	rm a.out
	rm *.o
	git rm a.out && git rm *.o