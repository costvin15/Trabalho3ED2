#ifndef _UTILS_C_
#define _UTILS_C_

#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    int i, j;
    int numlines;
    char *lines;
    char *linessaveptr;
    char *content;
    char *numbers;
    int **graphedges;
    double *graphweights;
    GraphAdjacencyMatrix *graph;
    
    content = readFile("inputs/test");
    if (!content)
        return NULL;

    lines = __strtok_r(content, "\n", &linessaveptr);
    numlines = atoi(lines);
    lines = __strtok_r(NULL, "\n", &linessaveptr);

    graphedges = (int **) malloc(numlines * sizeof(int *));
    if (!graphedges)
        return NULL;
    graphweights = (double *) malloc(numlines * sizeof(double));
    if (!graphweights)
        return NULL;

    i = 0;
    while (lines){
        j = 0;
        graphedges[i] = (int *) malloc(2 * sizeof(int));
        if (!graphedges[i]){
            for (; j < i; j++)
                free(graphedges[i]);
            return NULL;
        }

        numbers = strtok(lines, " ");
        while (numbers){
            if (j != 2)
                graphedges[i][j++] = atoi(numbers);
            else {
                graphweights[i] = atof(numbers);
            }
            numbers = strtok(NULL, " ");
        }
        lines = __strtok_r(NULL, "\n", &linessaveptr);
        i++;
    }

    graph = createGraphAdjacencyMatrix(numlines);
    if (!graph)
        return NULL;

    for (i = 0; i < numlines; i++)
        if(!insertGraphAdjacencyMatrix(graph, graphedges[i][0] - 1, graphedges[i][1] - 1, graphweights[i], (graphweights[i] < 0.0001) ? 0 : 1))
            return NULL;

    return graph;
}

#endif