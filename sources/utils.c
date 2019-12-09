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

GraphAdjacencyMatrix *readFileAndPopulateGraphAdjacencyMatrix(int directioned){
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
    if (!graphedges){
        free(content);
        return NULL;
    }

    graphweights = (double *) malloc(numlines * sizeof(double));
    if (!graphweights){
        free(content);
        free(graphedges);
        return NULL;
    }

    i = 0;
    while (lines){
        j = 0;
        graphedges[i] = (int *) malloc(2 * sizeof(int));
        if (!graphedges[i]){
            for (; j < i; j++)
                free(graphedges[i]);
            free(content);
            free(graphedges);
            free(graphweights);
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

    for (i = 0; i < numlines; i++){
        if(!insertGraphAdjacencyMatrix(graph, graphedges[i][0] - 1, graphedges[i][1] - 1, graphweights[i], directioned)){
            for (j = 0; j < numlines; j++)
                free(graphedges[i]);
            free(content);
            free(graphedges);
            free(graphweights);
            return NULL;
        }
        free(graphedges[i]);
    }
    
    free(content);
    free(graphedges);
    free(graphweights);
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