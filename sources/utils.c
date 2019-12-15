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

int fileGetEdgesCount(char *filename){
    FILE *file;
    int filesize;

    file = fopen(filename, "r");
    if (!file)
        return 0;
    fscanf(file, "%d\n", &filesize);

    return filesize;
}

int fileGetLinesCount(char *filename){
    FILE *file;
    char c;
    int linecount;

    linecount = 1;
    file = fopen(filename, "r");
    if (!file)
        return 0;

    while (!feof(file)){
        c = fgetc(file);
        if (c == '\n')
            linecount++;
    }

    return linecount;
}

long fileGetCharCount(char *filename){
    FILE *file;
    fpos_t position;
    long filesize;

    file = fopen(filename, "r");
    if (!file)
        return 0;
    
    fgetpos(file, &position);
    if (fseek(file, 0, SEEK_END) || (filesize = ftell(file)) == -1)
        perror("File lenght unknow");
    fsetpos(file, &position);

    return filesize;
}

int readFile(char *filename, int **edges, double *weights){
    FILE *file;
    char *content, *numbers, current, *lines, *linessaveptr;
    int i, j, currentPos = 0;
    long filesize;
    
    file = fopen(filename, "r");
    if (!file)
        return false;
    
    filesize = fileGetCharCount(filename);

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
        fclose(file);
        return false;
    }

    if (!weights){
        free(content);
        fclose(file);
        return false;
    }

    i = 0;
    while (lines){
        j = 0;
        edges[i] = (int *) malloc(2 * sizeof(int));
        if (!edges[i]){
            free(content);
            fclose(file);
            return false;
        }

        numbers = strtok(lines, " ");
        while (numbers){
            if (j != 2)
                edges[i][j++] = atoi(numbers);
            else
                weights[i] = atof(numbers);
            numbers = strtok(NULL, " ");
        }
        lines = __strtok_r(NULL, "\n", &linessaveptr);
        i++;
    }

    free(content);
    fclose(file);

    return true;
}

GraphAdjacencyMatrix *populateGraphAdjacencyMatrix(char *filename, int directioned){
    int i, j, **edges, numEdges, numLines;
    double *weights;
    GraphAdjacencyMatrix *graph;

    numEdges = fileGetEdgesCount(filename);
    numLines = fileGetLinesCount(filename);
    edges = (int **) malloc((numLines - 1) * sizeof(int *));
    if (!edges)
        return NULL;
    weights = (double *) malloc((numLines - 1) * sizeof(double));
    if (!weights){
        free(edges);
        return NULL;
    }

    if (!readFile(filename, edges, weights)){
        free(weights);
        free(edges);
        return NULL;
    }

    graph = createGraphAdjacencyMatrix(numEdges);
    if (!graph){
        for (j = 0; j < numEdges; j++)
            free(edges[j]);
        free(edges);
        free(weights);
        return NULL;
    }

    for (i = 0; i < (numLines - 1); i++){
        if(!insertGraphAdjacencyMatrix(graph, edges[i][0] - 1, edges[i][1] - 1, weights[i], directioned)){
            for (j = 0; j < numEdges; j++)
                free(edges[j]);
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
    int i, j, **edges, numEdges, numLines;
    double *weights;
    GraphAdjacencyList *graph;

    numEdges = fileGetEdgesCount(filename);
    numLines = fileGetLinesCount(filename);
    edges = (int **) malloc((numLines - 1) * sizeof(int *));
    if (!edges)
        return NULL;
    weights = (double *) malloc((numLines - 1) * sizeof(double));
    if (!weights){
        free(edges);
        return NULL;
    }

    if (!readFile(filename, edges, weights)){
        free(weights);
        free(edges);
        return NULL;
    }

    graph = createGraphAdjacencyList(numEdges, directioned);
    if (!graph){
        for (j = 0; j < numEdges; j++)
            free(edges[j]);
        free(edges);
        free(weights);
        return NULL;
    }

    for (i = 0; i < (numLines - 1); i++){
        if (!insertGraphAdjacencyList(graph, edges[i][0] - 1, edges[i][1] - 1, weights[i], directioned)){
            for (j = 0; j < numEdges; j++)
                free(edges[j]);
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