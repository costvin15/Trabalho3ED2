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

#ifndef _GRAPH_ADJACENCY_LIST_C_
#define _GRAPH_ADJACENCY_LIST_C_

#include <stdlib.h>
#include <stdbool.h>
#include "../headers/graphadjacencylist.h"
#include "../headers/linkedlist.h"

struct _adjacency_list_node_ {
    int vertex;
    double weight;
};

struct _adjacency_list_ {
    int vertex;
    LinkedList **list;
};

GraphAdjacencyList *createGraphAdjacencyList(int vertex){
    int i, j;
    GraphAdjacencyList *graph;

    graph = (GraphAdjacencyList *) malloc(sizeof(GraphAdjacencyList));
    if (!graph)
        return NULL;

    graph->vertex = vertex;
    graph->list = (LinkedList **) malloc(graph->vertex * sizeof(LinkedList *));
    if (!graph->list){
        free(graph);
        return NULL;
    }

    for (i = 0; i < graph->vertex; i++){
        graph->list[i] = createLinkedList();
        if (!graph->list[i]){
            for (j = 0; j < i; j++)
                destroyLinkedList(graph->list[j]);
            return NULL;
        }
    }

    return graph;
}

GraphAdjacencyListNode *createGraphAdjacencyListNode(int vertex, double weight){
    GraphAdjacencyListNode *node;

    node = (GraphAdjacencyListNode *) malloc(sizeof(GraphAdjacencyListNode));
    if (!node)
        return NULL;
    
    node->vertex = vertex;
    node->weight = weight;
    return node;
}

int compareGraphAdjacencyListNode(GraphAdjacencyListNode *nodeA, GraphAdjacencyListNode *nodeB){
    if (!nodeA)
        return false;
    if (!nodeB)
        return false;
    
    if (nodeA->weight == nodeB->weight)
        return 0;
    if (nodeA->weight > nodeB->weight)
        return 1;
    return -1;
}

int insertGraphAdjacencyList(GraphAdjacencyList *graph, int vertexA, int vertexB, double weight){
    GraphAdjacencyListNode *node;

    if (!graph)
        return false;
    if (vertexA < 0)
        return false;
    if (vertexB < 0)
        return false;

    node = createGraphAdjacencyListNode(vertexB, weight);
    if (!node)
        return false;
    
    if (!insertSortedLinkedList(graph->list[vertexA], (void *) node, compareGraphAdjacencyListNode)){
        free(node);
        return false;
    }

    return true;
}

#endif