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


gMixedGraphVertex* getGraphVertex(gMixedGraph* graph, gMiexdGraphDataPtr vertex) {
    if (!graph) return NULL;
    if (gMixedGraphIsEmpty(graph)) return NULL;

    gMixedGraphVertex* auxVertex = graph->currentVertex;
    while (auxVertex) {
        if (graph->compareF(auxVertex->data, vertex) == 0) break;
        auxVertex = auxVertex->nextVertex;
    }

    return auxVertex;
}


gMixedGraph* initgMixedGraph(impressFunctionGenMixedGraph printF, compareFunctionGenMixedGraph compareF,
                             destroyFunctionGenMixedGraph destroyF, deepcopyFunctionGenLinkedList deepcopyF) {

    if (!compareF) {
        fprintf(stderr, "Error: Compare Function is NULL when creating a new generic Mixed Graph.\n");
        return NULL;
    }

    gMixedGraph* newgraph = (gMixedGraph *) malloc(sizeof(gMixedGraph));
    if (newgraph == NULL) {
        fprintf(stderr, "Error: Failed while trying to allocate memory for a new generic Mixed Graph.\n");
        exit(EXIT_FAILURE);
    }

    newgraph->currentVertex = NULL;
    newgraph->counter = (uint32_t)0;
    newgraph->printF = printF;
    newgraph->compareF = compareF;
    newgraph->destroyF = destroyF;
    newgraph->deepcopyF = deepcopyF;

    return newgraph;
}


gMixedGraph* gMixedGraphCopy(gMixedGraph* graph) {
    if (!graph) return NULL;
    
    gMixedGraph* newgraph = initgMixedGraph(graph->printF, graph->compareF, graph->destroyF, graph->deepcopyF);

    if (gMixedGraphIsEmpty(graph)) return newgraph;

    gMixedGraphVertex* auxVertex = graph->currentVertex;
    while (auxVertex) {
        gMixedGraphInsertVertex(newgraph, (graph->deepcopyF ? graph->deepcopyF(auxVertex->data) : auxVertex->data));
        newgraph->currentVertex->neighboringVertices = gLinkedListCopy(auxVertex->neighboringVertices);
        auxVertex->nextVertex;
    }

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


void gMixedGraphInsertVertex(gMixedGraph* graph, gMiexdGraphDataPtr data) {
    if (!graph) return;

    // Checking whether the new vertex is already present in the graph:
    if (gMixedGraphSearchVertex(graph, data)) {
        if (graph->destroyF) graph->destroyF(data);
        return;
    }

    gMixedGraphVertex* newvertex = (gMixedGraphVertex *) malloc(sizeof(gMixedGraphVertex));
    if (newvertex == NULL) {
        fprintf(stderr, "Error: Failed while trying to allocate memory for a new generic Mixed Graph Vertex.\n");
        exit(EXIT_FAILURE);
    }

    newvertex->data = data;
    newvertex->neighboringVertices = initgLinkedList(graph->printF, graph->compareF, NULL, graph->deepcopyF);
    
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


void gMixedGraphRemoveVertex(gMixedGraph* graph, gMiexdGraphDataPtr data) {
    if (!graph) return;
    if (gMixedGraphIsEmpty(graph)) return;

    gMixedGraphVertex *auxVertex = graph->currentVertex, *previousVertex = NULL;
    while (auxVertex) {
        if (graph->compareF(auxVertex->data, data) == 0) break;
        auxVertex = auxVertex->nextVertex;
    }

    // Vertex not found:
    if (!auxVertex) {
        if (graph->destroyF) graph->destroyF(data);
        return;
    }

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


void gMixedGraphCreateEdge(gMixedGraph* graph, gMiexdGraphDataPtr vertex1, gMiexdGraphDataPtr vertex2) {
    if (!graph) return;
    if (gMixedGraphIsEmpty(graph)) return;
    
    gMixedGraphCreateUnidirectionalEdge(graph, vertex1, vertex2);
    gMixedGraphCreateUnidirectionalEdge(graph, vertex2, vertex1);

    return;
}


void gMixedGraphRemoveEdge(gMixedGraph* graph, gMiexdGraphDataPtr vertex1, gMiexdGraphDataPtr vertex2) {
    if (!graph) return;
    if (gMixedGraphIsEmpty(graph)) return;

    gMixedGraphRemoveUnidirectionalEdge(graph, vertex1, vertex2);
    gMixedGraphRemoveUnidirectionalEdge(graph, vertex2, vertex1);

    return;
}


void gMixedGraphCreateUnidirectionalEdge(gMixedGraph* graph, gMiexdGraphDataPtr sourceVertex, gMiexdGraphDataPtr destinationVertex) {
    if (!graph) return;
    if (gMixedGraphIsEmpty(graph)) return;

    gMixedGraphVertex *auxVertex = graph->currentVertex, *auxDestinationVertex = NULL;
    while (auxVertex) {
        if (graph->compareF(auxVertex->data, sourceVertex) == 0) break;
        if (graph->compareF(auxVertex->data, destinationVertex) == 0) auxDestinationVertex = auxVertex;
        auxVertex = auxVertex->nextVertex;
    }


    do {
        if (!auxVertex) {
            gMixedGraphInsertVertex(graph, sourceVertex);
            auxVertex = graph->currentVertex;

            if (!auxDestinationVertex) {
                gMixedGraphInsertVertex(graph, destinationVertex);
                auxDestinationVertex = graph->currentVertex;
            }

            break;
        }

        if (!auxDestinationVertex) {
            auxDestinationVertex = auxVertex;

            while (auxDestinationVertex) {
                if (graph->compareF(auxDestinationVertex->data, destinationVertex) == 0) break;
                auxDestinationVertex = auxDestinationVertex->nextVertex;
            }

            if (!auxDestinationVertex) {
                // The vertex is not found in the graph, so we can insert it:
                gMixedGraphInsertVertex(graph, destinationVertex);
                auxDestinationVertex = graph->currentVertex;
            }

            break;
        }

        // Edge Alreary Exists:
        if (gLinkedListSearch(auxVertex->neighboringVertices, auxDestinationVertex)) {
            // if the function parameters are different objects 
            // containing the same information, we destroy the duplicate:
            if (auxVertex->data != sourceVertex) {
                if (graph->destroyF) graph->destroyF(sourceVertex);
            }

            if (auxDestinationVertex->data != destinationVertex) {
                if (graph->destroyF) graph->destroyF(destinationVertex);
            }

            return;
        }

    } while (false);

    gLinkedListAppend(auxVertex->neighboringVertices, auxDestinationVertex->data);

    // if the function parameters are different objects 
    // containing the same information, we destroy the duplicate:
    if (auxVertex->data != sourceVertex) {
        if (graph->destroyF) graph->destroyF(sourceVertex);
    }

    if (auxDestinationVertex->data != destinationVertex) {
        if (graph->destroyF) graph->destroyF(destinationVertex);
    }

    return;
}


void gMixedGraphRemoveUnidirectionalEdge(gMixedGraph* graph, gMiexdGraphDataPtr sourceVertex, gMiexdGraphDataPtr destinationVertex) {
    if (!graph) return;
    if (gMixedGraphIsEmpty(graph)) return;

    gMixedGraphVertex *auxVertex = graph->currentVertex, *auxDestinationVertex = NULL;
    while (auxVertex) {
        if (graph->compareF(auxVertex->data, sourceVertex) == 0) break;
        if (graph->compareF(auxVertex->data, destinationVertex) == 0) auxDestinationVertex = auxVertex;
        auxVertex = auxVertex->nextVertex;
    }

    if (!auxVertex) {
        if (graph->destroyF) graph->destroyF(sourceVertex);

        if (auxDestinationVertex && (auxDestinationVertex->data != destinationVertex)) {
            if (graph->destroyF) graph->destroyF(destinationVertex);
        }
    }

    gLinkedListRemove(auxVertex->neighboringVertices, destinationVertex);

    return;
}


bool gMixedGraphIsEmpty(gMixedGraph* graph) {
    if (!graph) return 1;
    return (graph->counter <= 0);
}


bool gMixedGraphSearchVertex(gMixedGraph* graph, gMiexdGraphDataPtr data) {
    if (!graph) return 0;
    if (gMixedGraphIsEmpty(graph)) return 0;

    gMixedGraphVertex* auxVertex = graph->currentVertex;
    while (auxVertex) {
        if (graph->compareF(auxVertex->data, data) == 0) return 1;
        auxVertex = auxVertex->nextVertex;
    }

    return 0;
}


bool gMixedGraphSearchUnidirectionalEdge(gMixedGraph* graph, gMiexdGraphDataPtr sourceVertex, gMiexdGraphDataPtr destinationVertex) {
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


bool gMixedGraphSearchEdge(gMixedGraph* graph, gMiexdGraphDataPtr vertex1, gMiexdGraphDataPtr vertex2) {
    if (!graph) return 0;
    if (gMixedGraphIsEmpty(graph)) return 0;

    return (gMixedGraphSearchUnidirectionalEdge(graph, vertex1, vertex2) && gMixedGraphSearchUnidirectionalEdge(graph, vertex2, vertex1));
}


uint32_t gMixedGraphSize(gMixedGraph* graph) {
    if (!graph) return (uint32_t)0;
    return graph->counter;
}


uint32_t gMixedGraphGetVertexDegree(gMixedGraph* graph, gMiexdGraphDataPtr vertex) {
    if (!graph) return (uint32_t)0;
    if (gMixedGraphIsEmpty(graph)) return (uint32_t)0;

    uint32_t vertexDegree = (uint32_t)0;

    gMixedGraphVertex* auxVertex = graph->currentVertex;
    while (auxVertex) {
        if (graph->compareF(auxVertex->data, vertex) != 0) {
            if (gLinkedListSearch(auxVertex->neighboringVertices, vertex)) vertexDegree++;
            
            auxVertex = auxVertex->nextVertex;
            continue;
        }
        
        // Vertex Found:
        gLinkedListNode* auxNode = auxVertex->neighboringVertices->front;
        while (auxNode) {
            if (graph->compareF((gMiexdGraphDataPtr)auxNode->data, auxVertex->data) != 0) {
                // If it corresponds to a one-sided edge, increment one unit:
                if (!gMixedGraphSearchEdge(graph, (gMiexdGraphDataPtr)auxNode->data, auxVertex->data)) vertexDegree++;
                auxNode = auxNode->next;
                continue;
            }

            // Pointing to himself:
            vertexDegree += (uint32_t)2;
            
            auxNode = auxNode->next;
            continue;
        }

        auxVertex = auxVertex->nextVertex;
        continue;
    }

    return vertexDegree;
}


bool gMixedGraphIsEquals(gMixedGraph* graph1, gMixedGraph* graph2) {
    if (!graph1 || !graph2) return (!graph1 && !graph2);
    
    if (graph1->compareF != graph2->compareF) {
        fprintf(stderr, "Error: It is not possible to compare two graphs whose comparison functions differ from each other.\n");
        return 0;
    }

    if (gMixedGraphIsEmpty(graph1) || gMixedGraphIsEmpty(graph2)) return (gMixedGraphIsEmpty(graph1) && gMixedGraphIsEmpty(graph2));
    
    if (graph1->counter != graph2->counter) return 0;

    gMixedGraphVertex *auxVertex1 = graph1->currentVertex, *auxVertex2 = NULL;
    while (auxVertex1) {
        auxVertex2 = getGraphVertex(graph2, auxVertex1->data);
        if (!auxVertex2) return 0;
        if (!gLinkedListHasSameElements(auxVertex1->neighboringVertices, auxVertex2->neighboringVertices)) return 0;
        auxVertex1 = auxVertex1->nextVertex;
    }

    return 1;
}