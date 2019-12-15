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

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../headers/graphadjacencylist.h"
#include "../headers/linkedlist.h"
#include "../headers/queue.h"

struct _adjacency_list_node_ {
    int vertex;
    double weight;
};

struct _adjacency_list_ {
    int vertex;
    int directioned;
    LinkedList **list;
};

GraphAdjacencyList *createGraphAdjacencyList(int vertex, int directioned){
    int i, j;
    GraphAdjacencyList *graph;

    graph = (GraphAdjacencyList *) malloc(sizeof(GraphAdjacencyList));
    if (!graph)
        return NULL;

    graph->directioned = directioned;
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

int getVertexCountGraphAdjacencyList(GraphAdjacencyList *graph){
    if (!graph)
        return 0;
    return graph->vertex;
}

int getEdgesCountGraphAdjacencyList(GraphAdjacencyList *graph){
    int i, c;
    LinkedList *list;
    LinkedListNode *listNode;

    if (!graph)
        return 0;

    for (i = 0, c = 0; i < getVertexCountGraphAdjacencyList(graph); i++){
        list = graph->list[i];
        if (!list)
            return 0;
        listNode = getHeadLinkedList(list);
        while (listNode){
            listNode = getNextLinkedListNode(listNode);
            c++;
        }
    }

    if (!graph->directioned)
        c /= 2;
        
    return c;
}

void printGraphAdjacencyList(GraphAdjacencyList *graph){
    int i, j;
    LinkedList *list;
    LinkedListNode *listNode;
    GraphAdjacencyListNode *graphNode;
    int *vertex;

    if (!graph)
        return;
    
    vertex = (int *) malloc(getVertexCountGraphAdjacencyList(graph) * sizeof(int));
    if (!vertex)
        return;

    printf("%d vertices; %d arestas\n", getVertexCountGraphAdjacencyList(graph), getEdgesCountGraphAdjacencyList(graph));
    for (i = 0; i < getVertexCountGraphAdjacencyList(graph); i++){
        printf("%d: ", i + 1);
        list = graph->list[i];
        listNode = getHeadLinkedList(list);
        j = 0;
        while (listNode){
            graphNode = (GraphAdjacencyListNode *) getDataLinkedListNode(listNode);
            if (graphNode)
                vertex[j++] = graphNode->vertex + 1; 
            listNode = getNextLinkedListNode(listNode);
        }
        for (; j > 0; j--)
            printf("%d ", vertex[j - 1]);
        putchar('\n');
    }
}

int compareGraphAdjacencyListNode(void *nodeA, void *nodeB){
    GraphAdjacencyListNode *vertexA, *vertexB;
    
    if (!nodeA)
        return false;
    if (!nodeB)
        return false;
    
    vertexA = (GraphAdjacencyListNode *) nodeA;
    vertexB = (GraphAdjacencyListNode *) nodeB;

    if (vertexA->vertex == vertexB->vertex)
        return 0;
    if (vertexA->vertex > vertexB->vertex)
        return 1;
    return -1;
}

int insertGraphAdjacencyList(GraphAdjacencyList *graph, int vertexA, int vertexB, double weight, int directioned){
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
    if (!directioned){
        node = createGraphAdjacencyListNode(vertexA, weight);
        if (!insertSortedLinkedList(graph->list[vertexB], (void *) node, compareGraphAdjacencyListNode)){
            free(node);
            return false;
        }
    }

    return true;
}

double getVertexGraphAdjacencyList(GraphAdjacencyList *graph, int vertexA, int vertexB){
    LinkedList *list;
    LinkedListNode *listNode;
    void *data;

    if (!graph)
        return (double) __INT_MAX__;
    if (vertexA < 0)
        return (double) __INT_MAX__;
    if (vertexB < 0)
        return (double) __INT_MAX__;
    
    data = NULL;
    list = graph->list[vertexA];
    if (!list)
        return (double) __INT_MAX__;
    listNode = getHeadLinkedList(list);
    if (!listNode)
        return (double) __INT_MAX__;
    
    while (listNode){
        if (compareGraphAdjacencyListNode((void *) &vertexB, getDataLinkedListNode(listNode)) == 0){
            data = getDataLinkedListNode(listNode);
            break;
        }

        listNode = getNextLinkedListNode(listNode);
    }

    if (!data)
        return (double) __INT_MAX__;
    return *((double *) data);
}

int *getNeighbourhoodGraphAdjacencyList(GraphAdjacencyList *graph, int vertex){
    int i, j, *neighbourhoods;

    if (!graph)
        return NULL;
    if (vertex < 0)
        return NULL;

    neighbourhoods = (int *) malloc(getVertexCountGraphAdjacencyList(graph) * sizeof(int));
    if (!neighbourhoods)
        return NULL;
    
    for (i = 0, j = 0; i < getVertexCountGraphAdjacencyList(graph); i++)
        if ((double) __INT_MAX__ - getVertexGraphAdjacencyList(graph, vertex, i) > 0.001)
            neighbourhoods[j++] = i;
    neighbourhoods[j] = -1;
    return neighbourhoods;
}

int breadthFirstSearchGraphAdjacencyList(GraphAdjacencyList *graph, int root, int value){
    Queue *queue;
    int i, *currentNode, *vertexVisited, *distances, *neighbours, *currentNeighbour, distance;

    if (!graph)
        return 0;
    if (root < 0 || root > getVertexCountGraphAdjacencyList(graph))
        return 0;
    if (value < 0 || value > getVertexCountGraphAdjacencyList(graph))
        return 0;
    
    queue = createQueue();
    if (!queue)
        return 0;
    
    currentNode = (int *) malloc(sizeof(int));
    if (!currentNode){
        destroyQueue(queue);
        return 0;
    }

    vertexVisited = (int *) malloc(getVertexCountGraphAdjacencyList(graph) * sizeof(int));
    if (!vertexVisited){
        free(currentNode);
        destroyQueue(queue);
        return 0;
    }

    distances = (int *) malloc(getVertexCountGraphAdjacencyList(graph) * sizeof(int));
    if (!distances){
        free(vertexVisited);
        free(currentNode);
        destroyQueue(queue);
        return 0;
    }

    for (i = 0; i < getVertexCountGraphAdjacencyList(graph); i++){
        vertexVisited[i] = false;
        distances[i] = 0;
    }

    *currentNode = root;
    pushQueue(queue, (void *) currentNode);
    vertexVisited[root] = true;

    while (!emptyQueue(queue)){
        currentNode = (int *) popQueue(queue);
        neighbours = getNeighbourhoodGraphAdjacencyList(graph, *currentNode);
        for (i = 0; i < getVertexCountGraphAdjacencyList(graph); i++){
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

int minimunValuePrimGraphAdjacencyList(double *distances, int *mst, int vertexCount){
    int i, minimum;
    if (!distances)
        return -1;
    if (!mst)
        return -1;
    
    minimum = 0;
    for (i = 0; i < vertexCount; i++)
        if (!mst[i] && distances[minimum] - distances[i] > 0.01)
            minimum = i;
    return minimum;
}

int compareVertexListAuxFunction(void *nodeA, void *nodeB){
    if (!nodeA)
        return 0;
    if (!nodeB)
        return 0;

    struct vertex {
        int parent;
        int vertex;
        double weight;
    };

    struct vertex *vertexA, *vertexB;
    vertexA = (struct vertex *) nodeA;
    vertexB = (struct vertex *) nodeB;

    if (vertexA->weight == vertexB->weight){
        if (vertexA->vertex == vertexB->vertex)
            return 0;
        else if (vertexA->vertex > vertexB->vertex)
            return 1;
        else
            return -1;
    }
    if (vertexA->weight > vertexB->weight)
        return 1;
    return -1;
}

int **primAlgorithmGraphAdjacencyList(GraphAdjacencyList *graph){
    struct vertex {
        int parent;
        int vertex;
        double weight;
    };

    int i, j, *visited, **mst, current, *neightbours;
    LinkedList *edges;
    struct vertex *currentVertex;

    if (!graph)
        return NULL;
    
    visited = (int *) malloc(getVertexCountGraphAdjacencyList(graph) * sizeof(int));
    if (!visited)
        return NULL;
    for (i = 0; i < getVertexCountGraphAdjacencyList(graph); i++)
        visited[i] = false;
    edges = createLinkedList();
    if (!edges){
        free(visited);
        return NULL;
    }

    mst = (int **) malloc(getVertexCountGraphAdjacencyList(graph) * sizeof(int *));
    if (!mst){
        destroyLinkedList(edges);
        free(visited);
        return NULL;
    }

    for (i = 0; i < getVertexCountGraphAdjacencyList(graph); i++){
        mst[i] = (int *) malloc(2 * sizeof(int));
        if (!mst[i]){
            for (j = 0; j < i; j++)
                free(mst[j]);
            return NULL;
        }
    }

    current = 0;
    currentVertex = (struct vertex *) malloc(sizeof(struct vertex));
    if (!currentVertex){
        destroyLinkedList(edges);
        free(visited);
        for (i = 0; i < getVertexCountGraphAdjacencyList(graph); i++)
            free(mst[i]);
        free(mst);
        return NULL;
    }
    currentVertex->parent = 0;
    currentVertex->vertex = current;
    currentVertex->weight = 0.0;
    insertSortedLinkedList(edges, (void *) currentVertex, compareVertexListAuxFunction);

    j = 0;
    while (getLenghtLinkedList(edges) > 0){
        currentVertex = removeFront(edges);
        if (!visited[currentVertex->vertex])
            if (currentVertex->parent != currentVertex->vertex){
                mst[j][0] = currentVertex->parent;
                mst[j++][1] = currentVertex->vertex;
            }
        current = currentVertex->vertex;

        if (!visited[current]){
            visited[current] = true;
            neightbours = getNeighbourhoodGraphAdjacencyList(graph, current);
            for (i = 0; neightbours[i] != -1; i++){
                if (visited[neightbours[i]])
                    continue;
                currentVertex = (struct vertex *) malloc(sizeof(struct vertex));
                if (!currentVertex){
                    free(neightbours);
                    destroyLinkedList(edges);
                    free(visited);
                    for (j = 0; i < getVertexCountGraphAdjacencyList(graph); i++)
                        free(mst[i]);
                    free(mst);
                    return NULL;
                }
                currentVertex->parent = current;
                currentVertex->vertex = neightbours[i];
                currentVertex->weight = getVertexGraphAdjacencyList(graph, current, neightbours[i]);
                insertSortedLinkedList(edges, (void *) currentVertex, compareVertexListAuxFunction);
            }
        }
    }

    free(neightbours);
    destroyLinkedList(edges);
    free(visited);

    return mst;
}

#endif