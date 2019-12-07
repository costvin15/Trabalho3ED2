#ifndef _MENU_C_
#define _MENU_C_

#include <stdio.h>
#include "../headers/graph.h"
#include "../headers/utils.h"

void menu(){
    int i, j;
    GraphAdjacencyMatrix *graph;
    
    graph = readFileAndPopulateGraphAdjacencyMatrix(0);
    for (i = 0; i < getVertexCountGraphAdjacencyMatrix(graph); i++){
        for (j = 0; j < getVertexCountGraphAdjacencyMatrix(graph); j++)
            printf("%lf ", getVertexGraphAdjacencyMatrix(graph, i, j));
        printf("\n");
    }
    int a, b;
    scanf("%d%d", &a, &b);
    printf("BFS: %d\n", breadthFirstSearchAdjacencyMatrix(graph, a, b));
}

#endif