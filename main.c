#include <stdio.h>
#include "headers/graph.h"
#include "headers/utils.h"

int main(void){
    int i, j;
    GraphAdjacencyMatrix *graph;
    
    graph = readFileAndPopulateGraphAdjacencyMatrix(0);
    for (i = 0; i < getVertexCountGraphAdjacencyMatrix(graph); i++){
        for (j = 0; j < getVertexCountGraphAdjacencyMatrix(graph); j++)
            printf("%lf ", getVertexGraphAdjacencyMatrix(graph, i, j));
        printf("\n");
    }

    return 0;
}