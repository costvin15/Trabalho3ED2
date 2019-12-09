/*
 * Copyright 2019 Vinicius Costa Castro
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _UTILS_C_
#define _UTILS_C_

#include "../headers/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int fileContentLines(char *filename){
    FILE *file;
    int filesize;
    char c;

    file = fopen(filename, "r");
    if (!file)
        return 0;
    
    for (c = fgetc(file), filesize = 0; c != EOF; c = fgetc(file))
        if (c == '\n')
            filesize++;

    return filesize;
}

int readFile(char *filename, int **edges, double *weights){
    FILE *file;
    char *content, *numbers, current, *lines, *linessaveptr;
    int i, j, filesize, currentPos = 0;
    
    file = fopen(filename, "r");
    if (!file)
        return false;
    
    filesize = fileContentLines(filename);

    if (filesize < 1)
        return false;
    
    content = (char *) malloc(filesize * sizeof(char));
    if (!content)
        return false;
    
    while (1){
        current = getc(file);
        if (current == EOF){
            content[currentPos] = '\0';
            break;
        }
        content[currentPos++] = current;
    }

    lines = __strtok_r(content, "\n", &linessaveptr);
    lines = __strtok_r(NULL, "\n", &linessaveptr);

    if (!edges){
        free(content);
        return false;
    }

    if (!weights){
        free(content);
        return false;
    }

    i = 0;
    while (lines){
        j = 0;
        edges[i] = (int *) malloc(2 * sizeof(int));
        if (!edges[i]){
            for (; j < i; j++)
                free(edges[i]);
            free(content);
            return false;
        }

        numbers = strtok(lines, " ");
        while (numbers){
            if (j != 2)
                edges[i][j++] = atoi(numbers);
            else {
                weights[i] = atof(numbers);
            }
            numbers = strtok(NULL, " ");
        }
        lines = __strtok_r(NULL, "\n", &linessaveptr);
        i++;
    }

    return true;
}

GraphAdjacencyMatrix *populateGraphAdjacencyMatrix(char *filename, int directioned){
    int i, j, **edges, numlines;
    double *weights;
    GraphAdjacencyMatrix *graph;

    numlines = fileContentLines(filename);
    edges = (int **) malloc(numlines * sizeof(int *));
    if (!edges)
        return NULL;
    weights = (double *) malloc(numlines * sizeof(double));
    if (!weights){
        free(edges);
        return NULL;
    }

    if (!readFile(filename, edges, weights)){
        free(weights);
        free(edges);
        return NULL;
    }

    graph = createGraphAdjacencyMatrix(numlines);
    if (!graph)
        return NULL;

    for (i = 0; i < numlines; i++){
        if(!insertGraphAdjacencyMatrix(graph, edges[i][0] - 1, edges[i][1] - 1, weights[i], directioned)){
            for (j = 0; j < numlines; j++)
                free(edges[i]);
            free(edges);
            free(weights);
            return NULL;
        }
        free(edges[i]);
    }
    
    free(weights);
    free(edges);

    return graph;
}


GraphAdjacencyList *populateGraphAdjacencyList(char *filename, int directioned){
    int i, j, **edges, numlines;
    double *weights;
    GraphAdjacencyList *graph;

    numlines = fileContentLines(filename);
    edges = (int **) malloc(numlines * sizeof(int *));
    if (!edges)
        return NULL;
    weights = (double *) malloc(numlines * sizeof(double));
    if (!weights){
        free(edges);
        return NULL;
    }

    if (!readFile(filename, edges, weights)){
        free(weights);
        free(edges);
        return NULL;
    }

    graph = createGraphAdjacencyList(numlines);
    if (!graph)
        return NULL;

    for (i = 0; i < numlines; i++){
        if (!insertGraphAdjacencyList(graph, edges[i][0] - 1, edges[i][1] - 1, weights[i], directioned)){
            for (j = 0; j < numlines; j++)
                free(edges[i]);
            free(edges);
            free(weights);
            return NULL;
        }
        free(edges[i]);
    }

    free(weights);
    free(edges);
    
    return graph;
}

#endif