#ifndef _GRAPH_H_
#define _GRAPH_H_

typedef struct _adjacency_matrix_ GraphAdjacencyMatrix;

GraphAdjacencyMatrix *createGraphAdjacencyMatrix(int);
int destroyGraphAdjacencyMatrix(GraphAdjacencyMatrix *);
int insertGraphAdjacencyMatrix(GraphAdjacencyMatrix *, int, int, int, int);
int getVertexGraphAdjacencyMatrix(GraphAdjacencyMatrix *, int, int);
int getVertexCountGraphAdjacencyMatrix(GraphAdjacencyMatrix *);

#else

extern GraphAdjacencyMatrix *createGraphAdjacencyMatrix(int);
extern int destroyGraphAdjacencyMatrix(GraphAdjacencyMatrix *);
extern int insertGraphAdjacencyMatrix(GraphAdjacencyMatrix *, int, int, int, int);
extern int getVertexGraphAdjacencyMatrix(GraphAdjacencyMatrix *, int, int);
extern int getVertexCountGraphAdjacencyMatrix(GraphAdjacencyMatrix *);

#endif