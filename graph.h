#ifndef _GRAPH_H_

typedef struct _adjacency_matrix_ GraphAdjacencyMatrix;


GraphAdjacencyMatrix *createGraphAdjacencyMatrix(int);
int destroyGraphAdjacencyMatrix(GraphAdjacencyMatrix *);
int insertGraphAdjacencyMatrix(GraphAdjacencyMatrix *, int, int, int, int);

#else

extern GraphAdjacencyMatrix *createGraphAdjacencyMatrix(int);
extern int destroyGraphAdjacencyMatrix(GraphAdjacencyMatrix *);
extern int insertGraphAdjacencyMatrix(GraphAdjacencyMatrix *, int, int, int, int);

#endif