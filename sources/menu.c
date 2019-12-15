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
#include <stdlib.h>
#include <string.h>
#include "../headers/graphadjacencylist.h"
#include "../headers/graphadjacencymatrix.h"
#include "../headers/utils.h"

void options(int argc, char **argv){
    int representation;
    GraphAdjacencyMatrix *graphMatrix;
    GraphAdjacencyList *graphList;
    int i, **bfs, *vertex;

    graphMatrix = NULL;
    graphList = NULL;

    if (strcmp(argv[1], "--representation") == 0){
        if (strcmp(argv[2], "matrix") == 0){
            representation = 0;
            graphMatrix = populateGraphAdjacencyMatrix(argv[3], atoi(argv[4]));
        } else if (strcmp(argv[2], "list") == 0){
            representation = 1;
            graphList = populateGraphAdjacencyList(argv[3], atoi(argv[4]));
        } else {
            printf("Unrecognized command: %s\n", argv[2]);
        }
    } else 
        printf("Unrecognized command: %s\n", argv[1]);
    
    if (strcmp(argv[5], "--bfs") == 0){
        if (argc < 8){
            printf("Usage main [--representation] [matrix || list] [filename] [directioned (0 or 1)] [--bfs] [home vertex] [destiny vertex]\n");
            return;
        }
        
        if (!representation)
            printf("%d\n", breadthFirstSearchGraphAdjacencyMatrix(graphMatrix, atoi(argv[6]), atoi(argv[7])));
        else
            printf("%d\n", breadthFirstSearchGraphAdjacencyList(graphList, atoi(argv[6]), atoi(argv[7])));
        return;        
    }

    if (strcmp(argv[5], "--print") == 0){
        if (!representation)
            printGraphAdjacencyMatrix(graphMatrix);
        else
            printGraphAdjacencyList(graphList);
        return;
    }

    if (strcmp(argv[5], "--eccentricity") == 0){
        if (argc < 7){
            printf("Usage main [--representation] [matrix || list] [filename] [directioned (0 or 1)] [--eccentricity] [vertex]\n");
            return;
        }

        if (!representation)
            printf("%lf\n", getEccentricityGraphAdjacencyMatrix(graphMatrix, atoi(argv[6])));
        else
            printf("%lf\n", getEccentricityGraphAdjacencyList(graphList, atoi(argv[6])));            
        return;
    }

    if (strcmp(argv[5], "--diameter") == 0){
        if (!representation)
            printf("%lf\n", getDiameterGraphAdjacencyMatrix(graphMatrix));
        else
            printf("%lf\n", getDiameterGraphAdjacencyList(graphList));
        return;
    }

    if (strcmp(argv[5], "--radius") == 0){
        if (!representation)
            printf("%lf\n", getRadiusGraphAdjacencyMatrix(graphMatrix));
        else
            printf("%lf\n", getRadiusGraphAdjacencyList(graphList));
        return;
    }

    if (strcmp(argv[5], "--prim") == 0){
        if (!representation)
            bfs = primAlgorithmGraphAdjacencyMatrix(graphMatrix);
        else
            bfs = primAlgorithmGraphAdjacencyList(graphList);
        for (i = 0; i < getVertexCountGraphAdjacencyMatrix(graphMatrix) - 1; i++)
            printf("%d %d\n", bfs[i][0], bfs[i][1]);
        return;
    }

    if (strcmp(argv[5], "--kruskal") == 0){
        if (!representation)
            bfs = kruskalAlgorithmGraphAdjacencyMatrix(graphMatrix);
        else
            bfs = kruskalAlgorithmGraphAdjacencyList(graphList);
        for (i = 0; i < getVertexCountGraphAdjacencyMatrix(graphMatrix) - 1; i++)
            if (bfs[i])
                printf("%d %d\n", bfs[i][0], bfs[i][1]);
        return;
    }

    if (strcmp(argv[5], "--vertices_by_radius") == 0){
        if (argc < 8){
            printf("Usage main [--representation] [matrix || list] [filename] [directioned (0 or 1)] [--vertices_by_radius] [vertex] [radius]\n");
            return;
        }

        if (!representation)
            vertex = getVerticesByRadiusGraphAdjacencyMatrix(graphMatrix, atoi(argv[6]), atof(argv[7]));
        else
            vertex = getVerticesByRadiusGraphAdjacencyList(graphList, atoi(argv[6]), atof(argv[7]));
        for (i = 0; vertex[i] != -1; i++)
            printf("%d ", vertex[i]);
        putchar('\n');
        return;
    }
}

void menu(int argc, char **argv){
    if (argc < 6)
        printf("Usage: main [--representation] [matrix || list] [filename] [directioned (0 or 1)]\n[--bfs] [home vertex] [destiny vertex]\n[--print]\n[--eccentricity] [vertex]\n[--diameter]\n[--radius]\n[--prim]\n[--kruskal]\n[--vertices_by_radius] [vertex] [radius]\n");
    else
        options(argc, argv);
}

#endif