DEBUG = -g

all: linker
linker: utils.o graph.o main.o
	gcc -o main utils.o graph.o main.o
utils.o: utils.c
	gcc $(DEBUG) -o utils.o -c utils.c -W -Wall -std=c99
graph.o: graph.c
	gcc $(DEBUG) -o graph.o -c graph.c -W -Wall -std=c99
main.o: main.c graph.h utils.h
	gcc $(DEBUG) -o main.o -c main.c -W -Wall -std=c99
clean:
	rm -rf *.o
mrproper:
	rm -rf main