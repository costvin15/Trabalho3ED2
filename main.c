#include <stdio.h>
#include "graph.h"
#include "utils.h"

int main(void){
    int i, j;
    GraphAdjacencyMatrix *graph;
    
    graph = readFileAndPopulateGraphAdjacencyMatrix();
    for (i = 0; i < getVertexCountGraphAdjacencyMatrix(graph); i++){
        for (j = 0; j < getVertexCountGraphAdjacencyMatrix(graph); j++)
            printf("%d ", getVertexGraphAdjacencyMatrix(graph, i, j));
        printf("\n");
    }

    return 0;
}