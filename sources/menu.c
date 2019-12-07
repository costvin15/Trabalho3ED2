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