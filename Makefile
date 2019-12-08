DEBUG = -g
FLAGS = -W -Wall -std=c99
HEADERS_DIR = headers/
SOURCES_DIR = sources/
OBJ_DIR = obj/

all: linker
linker: $(OBJ_DIR)linkedlist.o $(OBJ_DIR)queue.o $(OBJ_DIR)menu.o $(OBJ_DIR)utils.o $(OBJ_DIR)graphadjacencylist.o $(OBJ_DIR)graphadjacencymatrix.o $(OBJ_DIR)main.o
	gcc -o main $(OBJ_DIR)linkedlist.o $(OBJ_DIR)queue.o $(OBJ_DIR)menu.o $(OBJ_DIR)utils.o $(OBJ_DIR)graphadjacencylist.o $(OBJ_DIR)graphadjacencymatrix.o $(OBJ_DIR)main.o
$(OBJ_DIR)linkedlist.o: $(SOURCES_DIR)linkedlist.c
	mkdir -p obj
	gcc $(DEBUG) -o $(OBJ_DIR)linkedlist.o -c $(SOURCES_DIR)linkedlist.c $(FLAGS)
$(OBJ_DIR)queue.o: $(SOURCES_DIR)queue.c
	gcc $(DEBUG) -o $(OBJ_DIR)queue.o -c $(SOURCES_DIR)queue.c $(FLAGS)
$(OBJ_DIR)menu.o: $(HEADERS_DIR)graphadjacencymatrix.h $(HEADERS_DIR)utils.h $(SOURCES_DIR)menu.c
	gcc $(DEBUG) -o $(OBJ_DIR)menu.o -c $(SOURCES_DIR)menu.c $(FLAGS)
$(OBJ_DIR)utils.o: $(SOURCES_DIR)utils.c
	gcc $(DEBUG) -o $(OBJ_DIR)utils.o -c $(SOURCES_DIR)utils.c $(FLAGS)
$(OBJ_DIR)graphadjacencylist.o: $(SOURCES_DIR)graphadjacencylist.c
	gcc $(DEBUG) -o $(OBJ_DIR)graphadjacencylist.o -c $(SOURCES_DIR)graphadjacencylist.c $(FLAGS)
$(OBJ_DIR)graphadjacencymatrix.o: $(SOURCES_DIR)graphadjacencymatrix.c
	gcc $(DEBUG) -o $(OBJ_DIR)graphadjacencymatrix.o -c $(SOURCES_DIR)graphadjacencymatrix.c $(FLAGS)
$(OBJ_DIR)main.o: main.c $(HEADERS_DIR)menu.h
	gcc $(DEBUG) -o $(OBJ_DIR)main.o -c main.c $(FLAGS)
clean:
	rm -rf ${OBJ_DIR}
mrproper:
	rm -rf main