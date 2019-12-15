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

#ifndef _GRAPH_ADJACENCY_MATRIX_H_
#define _GRAPH_ADJACENCY_MATRIX_H_

typedef struct _adjacency_matrix_ GraphAdjacencyMatrix;

GraphAdjacencyMatrix *createGraphAdjacencyMatrix(int);
int destroyGraphAdjacencyMatrix(GraphAdjacencyMatrix *);
int insertGraphAdjacencyMatrix(GraphAdjacencyMatrix *, int, int, double, int);

double getVertexGraphAdjacencyMatrix(GraphAdjacencyMatrix *, int, int);
int getVertexCountGraphAdjacencyMatrix(GraphAdjacencyMatrix *);
void printGraphAdjacencyMatrix(GraphAdjacencyMatrix *);

int *getNeighbourhoodGraphAdjacencyMatrix(GraphAdjacencyMatrix *, int);
int breadthFirstSearchGraphAdjacencyMatrix(GraphAdjacencyMatrix *, int, int);
int depthFirstSearchGraphAdjacencyMatrix(GraphAdjacencyMatrix *);

int **primAlgorithmGraphAdjacencyMatrix(GraphAdjacencyMatrix *);
int **kruskalAlgorithmGraphAdjacencyMatrix(GraphAdjacencyMatrix *);
double **floydWarshallGraphAdjacencyMatrix(GraphAdjacencyMatrix *graph);

#else

extern GraphAdjacencyMatrix *createGraphAdjacencyMatrix(int);
extern int destroyGraphAdjacencyMatrix(GraphAdjacencyMatrix *);
extern int insertGraphAdjacencyMatrix(GraphAdjacencyMatrix *, int, int, double, int);

extern double getVertexGraphAdjacencyMatrix(GraphAdjacencyMatrix *, int, int);
extern int getVertexCountGraphAdjacencyMatrix(GraphAdjacencyMatrix *);
extern void printGraphAdjacencyMatrix(GraphAdjacencyMatrix *);

extern int breadthFirstSearchGraphAdjacencyMatrix(GraphAdjacencyMatrix *, int, int);
extern int depthFirstSearchGraphAdjacencyMatrix(GraphAdjacencyMatrix *);

extern int **primAlgorithmGraphAdjacencyMatrix(GraphAdjacencyMatrix *);
extern int **kruskalAlgorithmGraphAdjacencyMatrix(GraphAdjacencyMatrix *);
extern double **floydWarshallGraphAdjacencyMatrix(GraphAdjacencyMatrix *graph);

#endif