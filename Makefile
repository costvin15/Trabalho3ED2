DEBUG = -g
FLAGS = -W -Wall -std=c99
HEADERS_DIR = headers/
SOURCES_DIR = sources/

all: linker
linker: queue.o menu.o utils.o graph.o main.o
	gcc -o main queue.o menu.o utils.o graph.o main.o
queue.o: $(SOURCES_DIR)queue.c
	gcc $(DEBUG) -o queue.o -c $(SOURCES_DIR)queue.c $(FLAGS)
menu.o: $(HEADERS_DIR)graph.h $(HEADERS_DIR)utils.h $(SOURCES_DIR)menu.c
	gcc $(DEBUG) -o menu.o -c $(SOURCES_DIR)menu.c $(FLAGS)
utils.o: $(SOURCES_DIR)utils.c
	gcc $(DEBUG) -o utils.o -c $(SOURCES_DIR)utils.c $(FLAGS)
graph.o: $(SOURCES_DIR)graph.c
	gcc $(DEBUG) -o graph.o -c $(SOURCES_DIR)graph.c $(FLAGS)
main.o: main.c $(HEADERS_DIR)menu.h
	gcc $(DEBUG) -o main.o -c main.c $(FLAGS)
clean:
	rm -rf *.o
mrproper:
	rm -rf main