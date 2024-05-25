#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#ifndef GENERICMIXEDGRAPH_H
#define GENERICMIXEDGRAPH_H


/* TODO: CREATE THE DEEP COPY FUNCTIONALITY FOR EVERY DATA STRUCTURE. */
/* TODO: implicitly implement the vertex insertion function when creating unidirectional edges. */


#include "../../Linked List/genLinkedList.h"

typedef void* gMiexdGraphDataPtr;

typedef void (*impressFunctionGenMixedGraph)(gMiexdGraphDataPtr data);
typedef int (*compareFunctionGenMixedGraph)(gMiexdGraphDataPtr data1, gMiexdGraphDataPtr data2);
typedef void (*destroyFunctionGenMixedGraph)(gMiexdGraphDataPtr data);
typedef gMiexdGraphDataPtr (*deepcopyFunctionGenMixedGraph)(gMiexdGraphDataPtr data);


typedef struct GENERICMIXEDGRAPHVERTEX {
    gMiexdGraphDataPtr data;
    gLinkedList* neighboringVertices;
    struct GENERICMIXEDGRAPHVERTEX* nextVertex;
} gMixedGraphVertex;


typedef struct GENERICMIXEDGRAPH {
    gMixedGraphVertex* currentVertex;
    uint32_t counter;
    impressFunctionGenMixedGraph printF;
    compareFunctionGenMixedGraph compareF;
    destroyFunctionGenMixedGraph destroyF;
    deepcopyFunctionGenLinkedList deepcopyF;
} gMixedGraph;


gMixedGraph* initgMixedGraph(impressFunctionGenMixedGraph printF, compareFunctionGenMixedGraph compareF,
                             destroyFunctionGenMixedGraph destroyF, deepcopyFunctionGenLinkedList deepcopyF);

gMixedGraph* gMixedGraphCopy(gMixedGraph* graph);
void gMixedGraphClear(gMixedGraph* graph);
void gMixedGraphImpress(gMixedGraph* graph);
void gMixedGraphDestroy(gMixedGraph** graphPointer);
void gMixedGraphInsertVertex(gMixedGraph* graph, gMiexdGraphDataPtr data);
void gMixedGraphRemoveVertex(gMixedGraph* graph, gMiexdGraphDataPtr data);
void gMixedGraphCreateEdge(gMixedGraph* graph, gMiexdGraphDataPtr vertex1, gMiexdGraphDataPtr vertex2);
void gMixedGraphRemoveEdge(gMixedGraph* graph, gMiexdGraphDataPtr vertex1, gMiexdGraphDataPtr vertex2);
void gMixedGraphCreateUnidirectionalEdge(gMixedGraph* graph, gMiexdGraphDataPtr sourceVertex, gMiexdGraphDataPtr destinationVertex);
void gMixedGraphRemoveUnidirectionalEdge(gMixedGraph* graph, gMiexdGraphDataPtr sourceVertex, gMiexdGraphDataPtr destinationVertex);
bool gMixedGraphIsEmpty(gMixedGraph* graph);
bool gMixedGraphIsEquals(gMixedGraph* graph1, gMixedGraph* graph2);
bool gMixedGraphSearchVertex(gMixedGraph* graph, gMiexdGraphDataPtr data);
bool gMixedGraphSearchEdge(gMixedGraph* graph, gMiexdGraphDataPtr vertex1, gMiexdGraphDataPtr vertex2);
bool gMixedGraphSearchUnidirectionalEdge(gMixedGraph* graph, gMiexdGraphDataPtr sourceVertex, gMiexdGraphDataPtr destinationVertex);
uint32_t gMixedGraphGetVertexDegree(gMixedGraph* graph, gMiexdGraphDataPtr vertex);
uint32_t gMixedGraphSize(gMixedGraph* graph);

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

    gMixedGraph* graphOfIntegers = initgMixedGraph(impressf, comparef, NULL, NULL);

    int val1 = 1, val2 = 2, val3 = 3, val4 = 4, val5 = 5, val6 = 6, val7 = 7;

    gMixedGraphInsertVertex(graphOfIntegers, &val1);
    gMixedGraphInsertVertex(graphOfIntegers, &val2);
    gMixedGraphInsertVertex(graphOfIntegers, &val3);
    gMixedGraphInsertVertex(graphOfIntegers, &val4);
    gMixedGraphInsertVertex(graphOfIntegers, &val5);

    gMixedGraphImpress(graphOfIntegers);
    printf("\nVertex Degree of 4: %zu\n\n", gMixedGraphGetVertexDegree(graphOfIntegers, &val4));

    gMixedGraphCreateUnidirectionalEdge(graphOfIntegers, &val1, &val5);
    gMixedGraphCreateUnidirectionalEdge(graphOfIntegers, &val1, &val2);
    gMixedGraphCreateUnidirectionalEdge(graphOfIntegers, &val1, &val3);
    gMixedGraphCreateUnidirectionalEdge(graphOfIntegers, &val2, &val2);
    gMixedGraphCreateUnidirectionalEdge(graphOfIntegers, &val2, &val4);
    gMixedGraphCreateUnidirectionalEdge(graphOfIntegers, &val2, &val3);
    gMixedGraphCreateUnidirectionalEdge(graphOfIntegers, &val2, &val3);
    gMixedGraphCreateUnidirectionalEdge(graphOfIntegers, &val5, &val3);

    gMixedGraphCreateEdge(graphOfIntegers, &val4, &val3);
    gMixedGraphCreateEdge(graphOfIntegers, &val3, &val4);
    gMixedGraphCreateEdge(graphOfIntegers, &val4, &val5);

    gMixedGraphImpress(graphOfIntegers);
    printf("\n=> Vertex Degree of 4: %zu\n", gMixedGraphGetVertexDegree(graphOfIntegers, &val4));
    printf("=> Vertex Degree of 2: %zu\n", gMixedGraphGetVertexDegree(graphOfIntegers, &val2));
    printf("=> Vertex Degree of 3: %zu\n\n", gMixedGraphGetVertexDegree(graphOfIntegers, &val3));

    gMixedGraphRemoveEdge(graphOfIntegers, &val3, &val4);

    gMixedGraphImpress(graphOfIntegers);

    printf("\nThere is a unidirectional edge starting from val5 and pointing to val3: %s\n", gMixedGraphSearchUnidirectionalEdge(graphOfIntegers, &val5, &val3) ? "Yes" : "No");
    printf("\nThere is an edge between val5 and val3: %s\n", gMixedGraphSearchEdge(graphOfIntegers, &val5, &val3) ? "Yes" : "No");

    puts("\n*Creating a manual copy of the graph of integers.");
    gMixedGraph* graphOfIntegersMCopy = initgMixedGraph(impressf, comparef, NULL, NULL);

    gMixedGraphInsertVertex(graphOfIntegersMCopy, &val1);
    gMixedGraphInsertVertex(graphOfIntegersMCopy, &val2);
    gMixedGraphInsertVertex(graphOfIntegersMCopy, &val3);
    gMixedGraphInsertVertex(graphOfIntegersMCopy, &val4);
    gMixedGraphInsertVertex(graphOfIntegersMCopy, &val5);

    gMixedGraphCreateUnidirectionalEdge(graphOfIntegersMCopy, &val5, &val3);
    gMixedGraphCreateUnidirectionalEdge(graphOfIntegersMCopy, &val5, &val4);
    gMixedGraphCreateUnidirectionalEdge(graphOfIntegersMCopy, &val4, &val5);
    gMixedGraphCreateUnidirectionalEdge(graphOfIntegersMCopy, &val2, &val2);
    gMixedGraphCreateUnidirectionalEdge(graphOfIntegersMCopy, &val2, &val4);
    gMixedGraphCreateUnidirectionalEdge(graphOfIntegersMCopy, &val2, &val3);
    gMixedGraphCreateUnidirectionalEdge(graphOfIntegersMCopy, &val1, &val5);
    gMixedGraphCreateUnidirectionalEdge(graphOfIntegersMCopy, &val1, &val2);
    gMixedGraphCreateUnidirectionalEdge(graphOfIntegersMCopy, &val1, &val3);

    puts("\nCopy Graph:");
    gMixedGraphImpress(graphOfIntegersMCopy);

    printf("Original Graph and Manual Copy Graph are Equal? %s\n", gMixedGraphIsEquals(graphOfIntegers, graphOfIntegersMCopy) ? "Yes" : "No");
    gMixedGraphCreateUnidirectionalEdge(graphOfIntegersMCopy, &val1, &val4);
    gMixedGraphCreateUnidirectionalEdge(graphOfIntegersMCopy, &val6, &val7);

    puts("\nCopy Graph:");
    gMixedGraphImpress(graphOfIntegersMCopy);
    printf("Original Graph and Manual Copy Graph are Equal? %s\n", gMixedGraphIsEquals(graphOfIntegers, graphOfIntegersMCopy) ? "Yes" : "No");

    gMixedGraphDestroy(&graphOfIntegers);
    gMixedGraphDestroy(&graphOfIntegersMCopy);

    puts("\nProgram Finished!");

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