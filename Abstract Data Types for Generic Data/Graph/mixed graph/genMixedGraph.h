#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef GENERICMIXEDGRAPH_H
#define GENERICMIXEDGRAPH_H

#include "../../Linked List/genLinkedList.h"

typedef void* Pointer;

typedef void (*impressFunctionGenMixedGraph)(Pointer data);
typedef int (*compareFunctionGenMixedGraph)(Pointer data1, Pointer data2);
typedef void (*destroyFunctionGenMixedGraph)(Pointer data);


typedef struct GENERICMIXEDGRAPHVERTEX {
    Pointer data;
    gLinkedList* neighboringVertices;
    struct GENERICMIXEDGRAPHVERTEX* nextVertex;
} gMixedGraphVertex;


typedef struct GENERICMIXEDGRAPH {
    gMixedGraphVertex* currentVertex;
    size_t counter;
    impressFunctionGenMixedGraph printF;
    compareFunctionGenMixedGraph compareF;
    destroyFunctionGenMixedGraph destroyF;
} gMixedGraph;


gMixedGraph* initgMixedGraph(impressFunctionGenMixedGraph printF, compareFunctionGenMixedGraph compareF, destroyFunctionGenMixedGraph destroyF);
void gMixedGraphDestroy(gMixedGraph** graphPointer);
void gMixedGraphInsertVertex(gMixedGraph* graph, Pointer data);
void gMixedGraphRemoveVertex(gMixedGraph* graph, Pointer data);
void gMixedGraphClear(gMixedGraph* graph);
void gMixedGraphImpress(gMixedGraph* graph);
void gMixedGraphCreateEdge(gMixedGraph* graph, Pointer vertex1, Pointer vertex2);
void gMixedGraphRemoveEdge(gMixedGraph* graph, Pointer vertex1, Pointer vertex2);
void gMixedGraphCreateUnidirectionalEdge(gMixedGraph* graph, Pointer sourceVertex, Pointer destinationVertex);
void gMixedGraphRemoveUnidirectionalEdge(gMixedGraph* graph, Pointer sourceVertex, Pointer destinationVertex);
bool gMixedGraphIsEmpty(gMixedGraph* graph);
bool gMixedGraphSearchVertex(gMixedGraph* graph, Pointer data);
bool gMixedGraphSearchUnidirectionalEdge(gMixedGraph* graph, Pointer sourceVertex, Pointer destinationVertex);
bool gMixedGraphSearchEdge(gMixedGraph* graph, Pointer vertex1, Pointer vertex2);

#endif

/*
                 Warning: The data structure code contained in this folder has
             dependencies on other data structure located in the same package of this
                      directory - namely, the Linked List data structure.
             Consequently, the compilation command for any project that uses this Graph
             code must include the path of the directory that contain the header file
                              of the dependencie mentioned above.

               Here is a practical example of compilation using the GCC compiler of
                                the program commented right below:

• gcc main.c genMixedGraph.c "../../Linked List/genLinkedList.c" -o executableProgram -I "../../Linked List"

*/

//
// Example of Using the Graph in a Program:
/*

#include "genMixedGraph.h"

void impressf(void* data);
int comparef(void* data1, void* data2);


int main(int argc, char** argv) {

    gMixedGraph* graphOfIntegers = initgMixedGraph(impressf, comparef, NULL);

    int val1 = 1, val2 = 2, val3 = 3, val4 = 4, val5 = 5;

    gMixedGraphInsertVertex(graphOfIntegers, &val1);
    gMixedGraphInsertVertex(graphOfIntegers, &val2);
    gMixedGraphInsertVertex(graphOfIntegers, &val3);
    gMixedGraphInsertVertex(graphOfIntegers, &val4);
    gMixedGraphInsertVertex(graphOfIntegers, &val5);

    gMixedGraphImpress(graphOfIntegers);

    gMixedGraphCreateUnidirectionalEdge(graphOfIntegers, &val1, &val5);
    gMixedGraphCreateUnidirectionalEdge(graphOfIntegers, &val1, &val2);
    gMixedGraphCreateUnidirectionalEdge(graphOfIntegers, &val1, &val3);
    gMixedGraphCreateUnidirectionalEdge(graphOfIntegers, &val2, &val4);
    gMixedGraphCreateUnidirectionalEdge(graphOfIntegers, &val2, &val3);
    gMixedGraphCreateUnidirectionalEdge(graphOfIntegers, &val2, &val3);
    gMixedGraphCreateUnidirectionalEdge(graphOfIntegers, &val5, &val3);

    gMixedGraphCreateEdge(graphOfIntegers, &val4, &val3);
    gMixedGraphCreateEdge(graphOfIntegers, &val3, &val4);
    gMixedGraphCreateEdge(graphOfIntegers, &val4, &val5);

    gMixedGraphImpress(graphOfIntegers);

    gMixedGraphRemoveEdge(graphOfIntegers, &val3, &val4);

    gMixedGraphImpress(graphOfIntegers);

    printf("\nThere is a unidirectional edge starting from val5 and pointing to val3: %s\n", gMixedGraphSearchUnidirectionalEdge(graphOfIntegers, &val5, &val3) ? "Yes" : "No");
    printf("\nThere is an edge between val5 and val3: %s\n", gMixedGraphSearchEdge(graphOfIntegers, &val5, &val3) ? "Yes" : "No");

    gMixedGraphDestroy(&graphOfIntegers);

    return 0;
}


int comparef(void* data1, void* data2) {
    int aux1 = *((int *)data1);
    int aux2 = *((int *)data2);

    if (!aux1 || !aux2) {
        if (!aux1 && !aux2) return 1;
        return 0;
    }

    if (aux1 > aux2) return 1;
    if (aux1 < aux2) return -1;
    return 0;
}


void impressf(void* data) {
    int* aux = (int *)data;
    if (aux != NULL) { printf("%d", *aux); } else { printf("NULL"); }
    return;
}

*/