#ifndef _UTILS_H_
#define _UTILS_H_

#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

char *readFile(char *filename){
    FILE *file;
    char *str, current;
    int filesize, currentPos = 0;
    
    file = fopen(filename, "r");
    if (!file)
        return NULL;
    
    fseek(file, 0, SEEK_END);
    filesize = ftell(file);
    fseek(file, 0, SEEK_SET);

    if (filesize < 1)
        return NULL;
    
    str = (char *) malloc(filesize * sizeof(char));
    if (!str)
        return NULL;
    
    while (1){
        current = getc(file);
        if (current == EOF){
            str[currentPos] = '\0';
            break;
        }
        str[currentPos++] = current;
    }

    return str;
}

GraphAdjacencyMatrix *readFileAndPopulateGraphAdjacencyMatrix(){
    printf("%s\n", readFile("inputs/test"));
}

#endif