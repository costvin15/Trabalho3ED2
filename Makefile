DEBUG = -g
HEADERS_DIR = headers/
SOURCES_DIR = sources/

all: linker
linker: queue.o menu.o utils.o graph.o main.o
	gcc -o main queue.o menu.o utils.o graph.o main.o
queue.o: $(SOURCES_DIR)queue.c
	gcc $(DEBUG) -o queue.o -c $(SOURCES_DIR)queue.c -W -Wall -std=c99
menu.o: $(HEADERS_DIR)graph.h $(HEADERS_DIR)utils.h $(SOURCES_DIR)menu.c
	gcc $(DEBUG) -o menu.o -c $(SOURCES_DIR)menu.c -W -Wall -std=c99
utils.o: $(SOURCES_DIR)utils.c
	gcc $(DEBUG) -o utils.o -c $(SOURCES_DIR)utils.c -W -Wall -std=c99
graph.o: $(SOURCES_DIR)graph.c
	gcc $(DEBUG) -o graph.o -c $(SOURCES_DIR)graph.c -W -Wall -std=c99
main.o: main.c $(HEADERS_DIR)menu.h
	gcc $(DEBUG) -o main.o -c main.c -W -Wall -std=c99
clean:
	rm -rf *.o
mrproper:
	rm -rf main