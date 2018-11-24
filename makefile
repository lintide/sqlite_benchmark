all: main

main: main.o
	gcc main.o -lsqlite3 -o main

main.o: main.c
	gcc -c main.c

clean: main.o