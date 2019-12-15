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

#ifndef _MENU_C_
#define _MENU_C_

#include <stdio.h>
#include "../headers/graphadjacencylist.h"
#include "../headers/graphadjacencymatrix.h"
#include "../headers/utils.h"

void menu(){

    GraphAdjacencyList *graph;
    // GraphAdjacencyMatrix *graph2;
    // int **prim, i;
    int bfs;

    graph = populateGraphAdjacencyList("inputs/test", 0);
    printGraphAdjacencyList(graph);
    // int *vizinhos = getNeighbourhoodGraphAdjacencyList(graph, 1);
    bfs = breadthFirstSearchGraphAdjacencyList(graph, 0, 1);
    printf("BFS %d\n", bfs);

    // for (i = 0; i < getVertexCountGraphAdjacencyList(graph); i++)
    //     printf("%d\n", vizinhos[i]);

    // graph2 = populateGraphAdjacencyMatrix("inputs/test", 0);
    // printGraphAdjacencyMatrix(graph2);
    // int *vizinhos = getNeighbourhoodGraphAdjacencyMatrix(graph2, 0);
    // printf("%p\n", vizinhos);

    // prim = primAlgorithmGraphAdjacencyMatrix(graph2);
    // for (i = 0; i < getVertexCountGraphAdjacencyMatrix(graph2); i++){
        // printf("%d %d\n", prim[i][0], prim[i][1]);
    // }

    printf("Encerrado.\n");

    /*int i, j;
    GraphAdjacencyMatrix *graph;
    graph = populateGraphAdjacencyMatrix("inputs/test", 0);
    printGraphAdjacencyMatrix(graph);

    for (i = 0; i < getVertexCountGraphAdjacencyMatrix(graph); i++){
        for (j = 0; j < getVertexCountGraphAdjacencyMatrix(graph); j++)
            printf("%lf ", getVertexGraphAdjacencyMatrix(graph, i, j));
        printf("\n");
    }
    int a, b;
    scanf("%d%d", &a, &b);
    printf("BFS: %d\n", breadthFirstSearchGraphAdjacencyMatrix(graph, a, b));*/
}

#endif