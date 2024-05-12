#include "genMixedGraph.h"

/*
        It is worth highlighting some characteristics inherent to
                the implementation of this graph algorithm:

    • For simplicity purposes, a scenario involving a multiplicity of
           vertices present in the graph will not be considered.
    That is, the vertices are completely distinct two by two in each graph.
     The criteria for distinguishing each vertex are determined explicitly 
     by the external comparison function provided during the instantiation 
                 of the individual structure of each graph.
*/

gMixedGraph* initgMixedGraph(impressFunctionGenMixedGraph printF, compareFunctionGenMixedGraph compareF, destroyFunctionGenMixedGraph destroyF) {

    if (!compareF) {
        fprintf(stderr, "Error: Compare Function is NULL when creating a new generic Mixed Graph.\n");
        return NULL;
    }

    gMixedGraph* newgraph = (gMixedGraph *)malloc(sizeof(gMixedGraph));
    if (newgraph == NULL) {
        fprintf(stderr, "Error: Failed while trying to allocate memory for a new generic Mixed Graph.\n");
        exit(EXIT_FAILURE);
    }

    newgraph->currentVertex = NULL;
    newgraph->counter = (size_t)0;
    newgraph->printF = printF;
    newgraph->compareF = compareF;
    newgraph->destroyF = destroyF;

    return newgraph;
}


void gMixedGraphDestroy(gMixedGraph** graphPointer) {
    if (!graphPointer) return;
    if (!(*graphPointer)) return;

    if (gMixedGraphIsEmpty((*graphPointer))) {
        free(*graphPointer); (*graphPointer) = NULL;
        return;
    }

    gMixedGraphVertex* auxVertex = (*graphPointer)->currentVertex;
    do {
        (*graphPointer)->currentVertex = (*graphPointer)->currentVertex->nextVertex;
        
        gLinkedListDestroy(&(auxVertex->neighboringVertices));
        if ((*graphPointer)->destroyF) (*graphPointer)->destroyF(auxVertex->data);
        
        free(auxVertex); 
        auxVertex = (*graphPointer)->currentVertex;

    } while (auxVertex);

    free(*graphPointer); (*graphPointer) = NULL;

    return;
}


void gMixedGraphInsertVertex(gMixedGraph* graph, Pointer data) {
    if(!graph) return;

    // Checking whether the new vertex is already present in the graph:
    if (gMixedGraphSearchVertex(graph, data)) return;

    gMixedGraphVertex* newvertex = (gMixedGraphVertex *) malloc (sizeof(gMixedGraphVertex));
    if (newvertex == NULL) {
        fprintf(stderr, "Error: Failed while trying to allocate memory for a new generic Mixed Graph Vertex.\n");
        exit(EXIT_FAILURE);
    }

    newvertex->data = data;
    newvertex->neighboringVertices = initgLinkedList(graph->printF, graph->compareF, NULL);
    
    if (gMixedGraphIsEmpty(graph)) {
        newvertex->nextVertex = NULL;
        (graph->counter)++;
        graph->currentVertex = newvertex;
        return;
    }

    (graph->counter)++;
    newvertex->nextVertex = graph->currentVertex;
    graph->currentVertex = newvertex;

    return;
}


void gMixedGraphRemoveVertex(gMixedGraph* graph, Pointer data) {
    if (!graph) return;
    if (gMixedGraphIsEmpty(graph)) return;

    gMixedGraphVertex *auxVertex = graph->currentVertex, *previousVertex = NULL;
    while (auxVertex) {
        if (graph->compareF(auxVertex->data, data) == 0) break;
        auxVertex = auxVertex->nextVertex;
    }

    // Vertex not found:
    if (!auxVertex) return;

    (graph->counter)--;

    if (!previousVertex) {
        // removing first Vertex:
        graph->currentVertex = graph->currentVertex->nextVertex;
        
        gLinkedListDestroy(&(auxVertex->neighboringVertices));
        if (graph->destroyF) graph->destroyF(auxVertex->data);
        free(auxVertex); auxVertex = NULL;

        return;
    }

    if (!auxVertex->nextVertex) {
        // Removing Last Vertex:
        previousVertex->nextVertex = NULL;

        gLinkedListDestroy(&(auxVertex->neighboringVertices));
        if (graph->destroyF) graph->destroyF(auxVertex->data);
        free(auxVertex); auxVertex = NULL;

        return;
    }

    // Removing an intermediate vertex:
    previousVertex->nextVertex = auxVertex->nextVertex;
    
    gLinkedListDestroy(&(auxVertex->neighboringVertices));
    if (graph->destroyF) graph->destroyF(auxVertex->data);
    free(auxVertex); auxVertex = NULL;

    return;
}


void gMixedGraphClear(gMixedGraph* graph) {
    if (!graph) return;
    if (gMixedGraphIsEmpty(graph)) return;

    while (!gMixedGraphIsEmpty(graph)) gMixedGraphRemoveVertex(graph, graph->currentVertex->data);

    return;
}


void gMixedGraphImpress(gMixedGraph* graph) {
    if (!graph) return;
    if (!graph->printF) { printf("Unable to Display Graph: PrintF Function Does Not Exist.\n"); return; }

    if (gMixedGraphIsEmpty(graph)) { printf("Graph Empty!\n"); return; }

    printf("/----------------------------\\");

    gMixedGraphVertex* auxVertex = graph->currentVertex;
    while (auxVertex) {
        printf("\n");
        printf("["); graph->printF(auxVertex->data); printf("] ");
        printf("Points to: "); gLinkedListImpress(auxVertex->neighboringVertices); printf(";");

        auxVertex = auxVertex->nextVertex;
    }

    printf("\n\\----------------------------/\n");

    return;
}


void gMixedGraphCreateEdge(gMixedGraph* graph, Pointer vertex1, Pointer vertex2) {
    if (!graph) return;
    if (gMixedGraphIsEmpty(graph)) return;
    
    gMixedGraphCreateUnidirectionalEdge(graph, vertex1, vertex2);
    gMixedGraphCreateUnidirectionalEdge(graph, vertex2, vertex1);

    return;
}


void gMixedGraphRemoveEdge(gMixedGraph* graph, Pointer vertex1, Pointer vertex2) {
    if (!graph) return;
    if (gMixedGraphIsEmpty(graph)) return;

    gMixedGraphRemoveUnidirectionalEdge(graph, vertex1, vertex2);
    gMixedGraphRemoveUnidirectionalEdge(graph, vertex2, vertex1);

    return;
}


void gMixedGraphCreateUnidirectionalEdge(gMixedGraph* graph, Pointer sourceVertex, Pointer destinationVertex) {
    if (!graph) return;
    if (gMixedGraphIsEmpty(graph)) return;

    bool foundDestinationVertexFlag = 0;

    gMixedGraphVertex* auxVertex = graph->currentVertex;
    while (auxVertex) {
        if (graph->compareF(auxVertex->data, sourceVertex) == 0) break;
        if (graph->compareF(auxVertex->data, destinationVertex) == 0) foundDestinationVertexFlag = 1;
        auxVertex = auxVertex->nextVertex;
    }

    if (!auxVertex) return;

    if (!foundDestinationVertexFlag) {
        if (!gMixedGraphSearchVertex(graph, destinationVertex)) return;
    }

    if (gLinkedListSearch(auxVertex->neighboringVertices, destinationVertex)) return;
    gLinkedListAppend(auxVertex->neighboringVertices, destinationVertex);

    return;
}


void gMixedGraphRemoveUnidirectionalEdge(gMixedGraph* graph, Pointer sourceVertex, Pointer destinationVertex) {
    if (!graph) return;
    if (gMixedGraphIsEmpty(graph)) return;

    gMixedGraphVertex* auxVertex = graph->currentVertex;
    while (auxVertex) {
        if (graph->compareF(auxVertex->data, sourceVertex) == 0) break;
        auxVertex = auxVertex->nextVertex;
    }

    if (!auxVertex) return;

    gLinkedListRemove(auxVertex->neighboringVertices, destinationVertex);

    return;
}


bool gMixedGraphIsEmpty(gMixedGraph* graph) {
    if (!graph) return 1;
    return (graph->counter <= (size_t)0);
}


bool gMixedGraphSearchVertex(gMixedGraph* graph, Pointer data) {
    if (!graph) return 0;
    if (gMixedGraphIsEmpty(graph)) return 0;

    gMixedGraphVertex* auxVertex = graph->currentVertex;
    while (auxVertex) {
        if (graph->compareF(auxVertex->data, data) == 0) return 1;
        auxVertex = auxVertex->nextVertex;
    }

    return 0;
}


bool gMixedGraphSearchUnidirectionalEdge(gMixedGraph* graph, Pointer sourceVertex, Pointer destinationVertex) {
    if (!graph) return 0;
    if (gMixedGraphIsEmpty(graph)) return 0;

    gMixedGraphVertex* auxVertex = graph->currentVertex;
    while (auxVertex) {
        if (graph->compareF(auxVertex->data, sourceVertex) == 0) break;
        auxVertex = auxVertex->nextVertex;
    }

    if (!auxVertex) return 0;

    return gLinkedListSearch(auxVertex->neighboringVertices, destinationVertex);
}


bool gMixedGraphSearchEdge(gMixedGraph* graph, Pointer vertex1, Pointer vertex2) {
    if (!graph) return 0;
    if (gMixedGraphIsEmpty(graph)) return 0;

    return (gMixedGraphSearchUnidirectionalEdge(graph, vertex1, vertex2) && gMixedGraphSearchUnidirectionalEdge(graph, vertex2, vertex1));
}