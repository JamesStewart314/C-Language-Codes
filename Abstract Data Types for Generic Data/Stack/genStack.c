#include "genStack.h"

gStack* stInit(impressFunctionStack printSt, compareFunctionStack compareSt) {
    gStack* newstack = (gStack *) malloc (sizeof(gStack));
    if (newstack == NULL) {
        fprintf(stderr, "Error: Failed while trying to allocate memory for a new stack.\n");
        exit(EXIT_FAILURE);
        return NULL;
    }

    newstack->counter = (size_t)0;
    newstack->top = NULL;
    newstack->printSt = printSt;
    newstack->compareSt = compareSt;

    return newstack;
}


bool stIsEmpty(gStack* st) {
    if (!st) return 1;
    return (st->counter <= (size_t)0);
}


void stDestroy(gStack** st) {
    if (!st) return;
    if (!(*st)) return;

    if (stIsEmpty((*st))) {
        free(*st);
        (*st) = NULL;
        return;
    }

    gNodeStack* aux = (*st)->top;
    while (aux) {
        (*st)->top = (*st)->top->next;
        free(aux);
        aux = (*st)->top;
    }

    free(*st);
    (*st) = NULL;
    return;
}


void stPush(gStack* st, void* data) {
    if (!st) return;

    gNodeStack* newnode = (gNodeStack *) malloc (sizeof(gNodeStack));
    if (newnode == NULL) {
        fprintf(stderr, "Failed to allocate memory for a new stack element.");
        exit(EXIT_FAILURE);
    }

    (st->counter++);
    newnode->data = data;
    newnode->next = st->top;
    st->top = newnode;
    return;
}


void* stPop(gStack* st) {
    if (!st) return NULL;
    if (stIsEmpty(st)) return NULL;

    (st->counter--);
    gNodeStack* nodeAux = st->top;
    st->top = st->top->next;

    void* returnData = nodeAux->data;
    free(nodeAux) ; nodeAux = NULL;

    return returnData;
}


size_t stCount(gStack* st) {
    if (!st) return (size_t)0;
    return st->counter;
}


void impressStack(gStack* st) {
    if (!st) return;
    if (stIsEmpty(st)) { printf("[]\n"); return; }

    gNodeStack* aux = st->top;
    printf("[");
    while (aux) {
        st->printSt(aux->data);
        printf(", ");
        aux = aux->next;
    }
    printf("\b\b]");

    return;
}


void* stRemove(gStack* st, void* data) {
    if (!st) return NULL;
    if (stIsEmpty(st)) return NULL;

    gNodeStack* nodeAux = st->top, *nodePrevious = NULL;
    while (nodeAux) {
        if (st->compareSt(nodeAux->data, data) == 0) {
            // Node contains the desired information. Proceeding to remove:
            (st->counter)--;
            
            // Removing the Top of Stack:
            if (!nodePrevious) {
                st->top = st->top->next;
                void* returnData = nodeAux->data;
                free(nodeAux); nodeAux = NULL;

                return returnData;
            }

            // Removing the Bottom of Stack:
            if (!nodeAux->next) {
                nodePrevious->next = NULL;
                void* returnData = nodeAux->data;
                free(nodeAux); nodeAux = NULL;

                return returnData;
            }

            // Removing Element in Middle:
            nodePrevious->next = nodeAux->next;
            void* returnData = nodeAux->data;
            free(nodeAux); nodeAux = NULL;
            
            return returnData;

        }

        nodePrevious = nodeAux;
        nodeAux = nodeAux->next;
    }

    // Data not Found:
    return NULL;
}