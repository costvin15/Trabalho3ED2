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

/**
 * @file graph.c
 * @author Vinicius Costa Castro
 * @date 6 Dec 2019
 * @brief File containing the implementation of ADT Graph
 **/

#ifndef _GRAPH_C_
#define _GRAPH_C_

#include "../headers/queue.h"
#include "../headers/graph.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

/**
 * @brief Representation of an adjacency matrix graph
 **/
struct _adjacency_matrix_ {
    int vertices;
    double **matriz;
};

GraphAdjacencyMatrix *createGraphAdjacencyMatrix(int vertices){
    int i, j;
    GraphAdjacencyMatrix *graph;
    
    if (vertices <= 0)
        return NULL;

    graph = (GraphAdjacencyMatrix *) malloc(sizeof(GraphAdjacencyMatrix));
    if (!graph)
        return NULL;
    graph->vertices = vertices;
    graph->matriz = (double **) malloc(graph->vertices * sizeof(double *));
    if (!graph->matriz){
        free(graph);
        return NULL;
    }
    
    for (i = 0; i < graph->vertices; i++){
        graph->matriz[i] = (double *) malloc(graph->vertices * sizeof(double));
        if (!graph->matriz[i]){
            for (j = 0; j < i; j++)
                free(graph->matriz[j]);
            free(graph->matriz);
            free(graph);
            return NULL;
        }
    }

    for (i = 0; i < graph->vertices; i++){
        for (j = 0; j < graph->vertices; j++)
            graph->matriz[i][j] = __INT_MAX__;
    }

    return graph;
}

int destroyGraphAdjacencyMatrix(GraphAdjacencyMatrix *graph){
    int i;

    if (!graph)
        return false;

    for (i = 0; i < graph->vertices; i++)
        free(graph->matriz[i]);
    free(graph->matriz);
    free(graph);

    return true;
}

int insertGraphAdjacencyMatrix(GraphAdjacencyMatrix *graph, int vertexA, int vertexB, double weight, int directioned){
    if (!graph)
        return false;
    if (vertexA < 0)
        return false;
    if (vertexA < 0)
        return false;
    
    graph->matriz[vertexA][vertexB] = weight;
    if (!directioned)
        graph->matriz[vertexB][vertexA] = weight;

    return true;
}

double getVertexGraphAdjacencyMatrix(GraphAdjacencyMatrix *graph, int vertexA, int vertexB){
    if (!graph)
        return (double) __INT_MAX__;
    if (vertexA < 0)
        return (double) __INT_MAX__;
    if (vertexB < 0)
        return (double) __INT_MAX__;

    return graph->matriz[vertexA][vertexB];
}

int getVertexCountGraphAdjacencyMatrix(GraphAdjacencyMatrix *graph){
    if (!graph)
        return 0;
    return graph->vertices;
}

int *getNeighbourhoodGraphAdjacencyMatrix(GraphAdjacencyMatrix *graph, int vertex){
    int i, j, *neighbourhoods;

    if (!graph)
        return NULL;
    if (vertex < 0)
        return NULL;
    
    neighbourhoods = (int *) malloc(getVertexCountGraphAdjacencyMatrix(graph) * sizeof(int));
    if (!neighbourhoods)
        return NULL;

    for (i = 0, j = 0; i < getVertexCountGraphAdjacencyMatrix(graph); i++)
        if (!((double) __INT_MAX__ - getVertexGraphAdjacencyMatrix(graph, vertex, i) < 0.001))
            neighbourhoods[j++] = i;
    
    neighbourhoods[j] = -1;

    return neighbourhoods;
}

int breadthFirstSearchAdjacencyMatrix(GraphAdjacencyMatrix *graph, int root, int value){
    Queue *queue;
    int i, distance, *currentNode, *currentNeighbour, *vertexVisited, *neighbours, *distances;

    if (root < 0 || root > getVertexCountGraphAdjacencyMatrix(graph))
        return 0;
    if (value < 0 || root > getVertexCountGraphAdjacencyMatrix(graph))
        return 0;

    queue = createQueue();
    if (!queue)
        return 0;
    
    currentNode = (int *) malloc(sizeof(int));
    if (!currentNode){
        destroyQueue(queue);
        return 0;
    }
    
    vertexVisited = (int *) malloc(getVertexCountGraphAdjacencyMatrix(graph) * sizeof(int));
    if (!vertexVisited){
        free(currentNode);
        destroyQueue(queue);
        return 0;
    }

    distances = (int *) malloc(getVertexCountGraphAdjacencyMatrix(graph) * sizeof(int));
    if (!distances){
        free(vertexVisited);
        free(currentNode);
        destroyQueue(queue);
        return 0;
    }

    for (i = 0; i < getVertexCountGraphAdjacencyMatrix(graph); i++){
        vertexVisited[i] = false;
        distances[i] = 0;
    }

    *currentNode = root;
    pushQueue(queue, (void *) currentNode);
    vertexVisited[root] = true;
    
    while (!emptyQueue(queue)){
        currentNode = (int *) popQueue(queue);

        neighbours = getNeighbourhoodGraphAdjacencyMatrix(graph, *currentNode);

        for (i = 0; i < getVertexCountGraphAdjacencyMatrix(graph); i++){
            if (neighbours[i] == -1)
                break;
            if (vertexVisited[neighbours[i]])
                continue;
            
            distances[neighbours[i]] = distances[*currentNode] + 1;
            currentNeighbour = (int *) malloc(sizeof(int));
            *currentNeighbour = neighbours[i];
            pushQueue(queue, (void *) currentNeighbour);
            vertexVisited[neighbours[i]] = true;
        }

        free(currentNode);
    }

    distance = distances[value];

    destroyQueue(queue);
    free(neighbours);
    free(vertexVisited);
    free(distances);

    return distance;
}

void printGraphAdjacencyMatrix(GraphAdjacencyMatrix *graph){
    int i, j;
    double vertex;

    if (!graph)
        return;

    for (i = 0; i < getVertexCountGraphAdjacencyMatrix(graph); i++){
        printf("%d: ", i + 1);
        for (j = 0; j < getVertexCountGraphAdjacencyMatrix(graph); j++){
            vertex = getVertexGraphAdjacencyMatrix(graph, i, j);
            if ((double) __INT_MAX__ - vertex > 0.001)
                printf("%d ", j + 1);
        }
        putchar('\n');
    }
}

#endif