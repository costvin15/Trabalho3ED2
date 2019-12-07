#ifndef _GRAPH_C_
#define _GRAPH_C_

#include "../headers/queue.h"
#include "../headers/graph.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

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
    int i, *currentNode, *vertexVisited, *neighbours;

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

    for (i = 0; i < getVertexCountGraphAdjacencyMatrix(graph); i++)
        vertexVisited[i] = false;

    *currentNode = root;
    pushQueue(queue, (void *) currentNode);
    vertexVisited[root] = true;
    
    while (!emptyQueue(queue)){
        currentNode = (int *) popQueue(queue);

        neighbours = getNeighbourhoodGraphAdjacencyMatrix(graph, *currentNode);
        free(currentNode);

        for (i = 0; i < getVertexCountGraphAdjacencyMatrix(graph); i++){
            if (neighbours[i] == -1)
                break;
            if (vertexVisited[neighbours[i]])
                continue;
            currentNode = (int *) malloc(sizeof(int));
            *currentNode = neighbours[i];
            pushQueue(queue, (void *) currentNode);
            vertexVisited[neighbours[i]] = true;
        }
    }

    destroyQueue(queue);
    free(neighbours);
    free(vertexVisited);

    return 0;
}

#endif