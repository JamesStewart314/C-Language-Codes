#include "genStack.h"

gStack* stInit(impressFunctionStack printSt) {
    gStack* newstack = (gStack *) malloc (sizeof(gStack));
    newstack->counter = (size_t)0;
    newstack->top = NULL;
    newstack->printSt = printSt;

    return newstack;
}


bool stIsEmpty(gStack* st) {
    if (!st) return 1;
    if (st->counter <= (size_t)0) return 1;
    return 0;
}


void stDestroy(gStack **st) {
    if (!st) return;
    if (!(*st)) return;

    if (stIsEmpty((*st))) {
        free(*st);
        *st = NULL;
        return;
    }

    gNodeStack* aux = (*st)->top;
    while (aux) {
        (*st)->top = (*st)->top->next;
        free(aux);
        aux = (*st)->top;
    }

    free(*st);
    *st = NULL;
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


void *stPop(gStack* st) {
    if (!st) return NULL;
    if (stIsEmpty(st)) return NULL;

    (st->counter--);
    gNodeStack* aux = st->top;
    st->top = st->top->next;

    return aux->data;
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
