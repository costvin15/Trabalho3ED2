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

GraphAdjacencyList *createGraphAdjacencyList(int);
GraphAdjacencyListNode *createGraphAdjacencyListNode(int, double);

int compareGraphAdjacencyListNode(GraphAdjacencyListNode *, GraphAdjacencyListNode *);
int insertGraphAdjacencyList(GraphAdjacencyList *, int, int, double);

#endif