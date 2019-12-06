#ifndef _GRAPH_H_
#define _GRAPH_H_

typedef struct _adjacency_matrix_ GraphAdjacencyMatrix;

GraphAdjacencyMatrix *createGraphAdjacencyMatrix(int);
int destroyGraphAdjacencyMatrix(GraphAdjacencyMatrix *);
int insertGraphAdjacencyMatrix(GraphAdjacencyMatrix *, int, int, double, int);
double getVertexGraphAdjacencyMatrix(GraphAdjacencyMatrix *, int, int);
int getVertexCountGraphAdjacencyMatrix(GraphAdjacencyMatrix *);

int *breadthFirstSearchAdjacencyMatrix(GraphAdjacencyMatrix *, int, int);

#else

extern GraphAdjacencyMatrix *createGraphAdjacencyMatrix(int);
extern int destroyGraphAdjacencyMatrix(GraphAdjacencyMatrix *);
extern int insertGraphAdjacencyMatrix(GraphAdjacencyMatrix *, int, int, double, int);
extern double getVertexGraphAdjacencyMatrix(GraphAdjacencyMatrix *, int, int);
extern int getVertexCountGraphAdjacencyMatrix(GraphAdjacencyMatrix *);

extern int *breadthFirstSearchAdjacencyMatrix(GraphAdjacencyMatrix *, int, int);

#endif