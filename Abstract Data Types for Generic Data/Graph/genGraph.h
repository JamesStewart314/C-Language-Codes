#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef GENERICGRAPH_H
#define GENERICGRAPH_H

#include "../Linked List/genLinkedList.h"

typedef void* Pointer;

typedef void (*impressFunctionGenGraph)(Pointer data);
typedef int (*compareFunctionGenGraph)(Pointer data1, Pointer data2);
typedef void (*destroyFunctionGenGraph)(Pointer data);


typedef struct GENERICGRAPHVERTEX {
    Pointer data;
    gLinkedList* neighboringVertices;
    struct GENERICGRAPHVERTEX* nextVertex;
} gGraphVertex;


typedef struct GENERICGRAPH {
    gGraphVertex* currentVertex;
    size_t counter;
    impressFunctionGenGraph printF;
    compareFunctionGenGraph compareF;
    destroyFunctionGenGraph destoyF;
} gGraph;


gGraph* initgGraph(impressFunctionGenGraph printF, compareFunctionGenGraph compareF, destroyFunctionGenGraph destroyF);
void gGraphDestroy(gGraph** graphPointer);
void gGraphInsertVertex(gGraph* graph, Pointer data);
void gGraphRemoveVertex(gGraph* graph, Pointer data);
void gGraphClear(gGraph* graph);
void gGraphImpress(gGraph* graph);
void gGraphCreateEdge(gGraph* graph, Pointer vertex1, Pointer vertex2);
void gGraphRemoveEdge(gGraph* graph, Pointer vertex1, Pointer vertex2);
void gGraphCreateUnidirectionalEdge(gGraph* graph, Pointer sourceVertex, Pointer destinationVertex);
void gGraphRemoveUnidirectionalEdge(gGraph* graph, Pointer sourceVertex, Pointer destinationVertex);
bool gGraphIsEmpty(gGraph* graph);
bool gGraphSearchUnidirectionalEdge(gGraph* graph, Pointer sourceVertex, Pointer destinationVertex);
bool gGraphSearchEdge(gGraph *graph, Pointer vertex1, Pointer vertex2);

#endif