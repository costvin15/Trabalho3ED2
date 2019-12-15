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

#ifndef _GRAPH_ADJACENCY_LIST_H_
#define _GRAPH_ADJACENCY_LIST_H_

typedef struct _adjacency_list_node_ GraphAdjacencyListNode;
typedef struct _adjacency_list_ GraphAdjacencyList;

GraphAdjacencyList *createGraphAdjacencyList(int, int);
GraphAdjacencyListNode *createGraphAdjacencyListNode(int, double);

int getVertexCountGraphAdjacencyList(GraphAdjacencyList *);
int getEdgesCountGraphAdjacencyList(GraphAdjacencyList *);
void printGraphAdjacencyList(GraphAdjacencyList *);

int compareGraphAdjacencyListNode(void *, void *);
int insertGraphAdjacencyList(GraphAdjacencyList *, int, int, double, int);

double getVertexGraphAdjacencyList(GraphAdjacencyList *, int, int);
int *getNeighbourhoodGraphAdjacencyList(GraphAdjacencyList *, int);
int breadthFirstSearchGraphAdjacencyList(GraphAdjacencyList *, int, int);
int **primAlgorithmGraphAdjacencyList(GraphAdjacencyList *);
double **floydWarshallGraphAdjacencyList(GraphAdjacencyList *);

#else

extern GraphAdjacencyList *createGraphAdjacencyList(int, int);
extern GraphAdjacencyListNode *createGraphAdjacencyListNode(int, double);

extern int getVertexCountGraphAdjacencyList(GraphAdjacencyList *);
extern int getEdgesCountGraphAdjacencyList(GraphAdjacencyList *);
extern void printGraphAdjacencyList(GraphAdjacencyList *);

extern int compareGraphAdjacencyListNode(void *, void *);
extern int insertGraphAdjacencyList(GraphAdjacencyList *, int, int, double, int);

extern double getVertexGraphAdjacencyList(GraphAdjacencyList *, int, int);
extern int *getNeighbourhoodGraphAdjacencyList(GraphAdjacencyList *graph, int vertex);
extern int breadthFirstSearchGraphAdjacencyList(GraphAdjacencyList *, int, int);
extern int **primAlgorithmGraphAdjacencyList(GraphAdjacencyList *);
extern double **floydWarshallGraphAdjacencyList(GraphAdjacencyList *);

#endif