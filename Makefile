DEBUG = -g
HEADERS_DIR = headers/
SOURCES_DIR = sources/

all: linker
linker: utils.o graph.o main.o
	gcc -o main utils.o graph.o main.o
utils.o: $(SOURCES_DIR)utils.c
	gcc $(DEBUG) -o utils.o -c $(SOURCES_DIR)utils.c -W -Wall -std=c99
graph.o: $(SOURCES_DIR)graph.c
	gcc $(DEBUG) -o graph.o -c $(SOURCES_DIR)graph.c -W -Wall -std=c99
main.o: main.c $(HEADERS_DIR)graph.h $(HEADERS_DIR)utils.h
	gcc $(DEBUG) -o main.o -c main.c -W -Wall -std=c99
clean:
	rm -rf *.o
mrproper:
	rm -rf main