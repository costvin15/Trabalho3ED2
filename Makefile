DEBUG = -g
FLAGS = -W -Wall -std=c99
HEADERS_DIR = headers/
SOURCES_DIR = sources/
OBJ_DIR = obj/

all: linker
linker: $(OBJ_DIR)queue.o $(OBJ_DIR)menu.o $(OBJ_DIR)utils.o $(OBJ_DIR)graph.o $(OBJ_DIR)main.o
	gcc -o main $(OBJ_DIR)queue.o $(OBJ_DIR)menu.o $(OBJ_DIR)utils.o $(OBJ_DIR)graph.o $(OBJ_DIR)main.o
$(OBJ_DIR)queue.o: $(SOURCES_DIR)queue.c
	mkdir obj
	gcc $(DEBUG) -o $(OBJ_DIR)queue.o -c $(SOURCES_DIR)queue.c $(FLAGS)
$(OBJ_DIR)menu.o: $(HEADERS_DIR)graph.h $(HEADERS_DIR)utils.h $(SOURCES_DIR)menu.c
	gcc $(DEBUG) -o $(OBJ_DIR)menu.o -c $(SOURCES_DIR)menu.c $(FLAGS)
$(OBJ_DIR)utils.o: $(SOURCES_DIR)utils.c
	gcc $(DEBUG) -o $(OBJ_DIR)utils.o -c $(SOURCES_DIR)utils.c $(FLAGS)
$(OBJ_DIR)graph.o: $(SOURCES_DIR)graph.c
	gcc $(DEBUG) -o $(OBJ_DIR)graph.o -c $(SOURCES_DIR)graph.c $(FLAGS)
$(OBJ_DIR)main.o: main.c $(HEADERS_DIR)menu.h
	gcc $(DEBUG) -o $(OBJ_DIR)main.o -c main.c $(FLAGS)
clean:
	rm -rf ${OBJ_DIR}
mrproper:
	rm -rf main