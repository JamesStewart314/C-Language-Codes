#include "genStack.h"

gStack* initgStack(impressFunctionGenStack printF, compareFunctionGenStack compareF, destroyFunctionGenStack destroyF) {

    if (!compareF) {
        fprintf(stderr, "Error: Compare Function is NULL when creating a new generic Stack.\n");
        return NULL;
    }

    gStack* newstack = (gStack *) malloc (sizeof(gStack));
    if (newstack == NULL) {
        fprintf(stderr, "Error: Failed while trying to allocate memory for a new generic Stack.\n");
        exit(EXIT_FAILURE);
        return NULL;
    }

    newstack->counter = (size_t)0;
    newstack->top = NULL;
    newstack->printF = printF;
    newstack->compareF = compareF;
    newstack->destroyF = destroyF;

    return newstack;
}


bool gStackIsEmpty(gStack* st) {
    if (!st) return 1;
    return (st->counter <= (size_t)0);
}


void gStackDestroy(gStack** stPointer) {
    if (!stPointer) return;
    if (!(*stPointer)) return;

    if (gStackIsEmpty((*stPointer))) {
        free(*stPointer); (*stPointer) = NULL;
        return;
    }

    gStackNode* auxNode = (*stPointer)->top;
    while (auxNode != NULL) {
        (*stPointer)->top = (*stPointer)->top->next;
        if ((*stPointer)->destroyF) (*stPointer)->destroyF(auxNode->data);
        free(auxNode); auxNode = (*stPointer)->top;
    }

    free(*stPointer); (*stPointer) = NULL;

    return;
}


void gStackPush(gStack* st, gStPointerData data) {
    if (!st) return;

    gStackNode* newnode = (gStackNode *) malloc (sizeof(gStackNode));
    if (newnode == NULL) {
        fprintf(stderr, "Error: Unable to allocate memory to a new generic Stack node.\n");
        exit(EXIT_FAILURE);
        return;
    }

    (st->counter++);
    newnode->data = data;
    newnode->next = st->top;
    st->top = newnode;
    return;
}


gStPointerData gStackPop(gStack* st) {
    if (!st) return NULL;
    if (gStackIsEmpty(st)) return NULL;

    (st->counter--);
    gStackNode* auxNode = st->top;
    st->top = st->top->next;

    gStPointerData returnData = auxNode->data;
    free(auxNode) ; auxNode = NULL;

    return returnData;
}


size_t gStackSize(gStack* st) {
    if (!st) return (size_t)0;
    return st->counter;
}


void gStackImpress(gStack* st) {
    if (!st) return;
    if (!st->printF) { printf("Unable to Display Stack: PrintF Function Does Not Exist.\n"); return; }

    if (gStackIsEmpty(st)) { printf("[]"); return; }

    gStackNode* auxNode = st->top;
    printf("[");
    while (auxNode != NULL) {
        st->printF(auxNode->data);
        printf(" -> ");
        auxNode = auxNode->next;
    }
    printf("NULL]");

    return;
}


void gStackRemove(gStack* st, gStPointerData data) {
    if (!st) return;
    if (gStackIsEmpty(st)) return;

    gStackNode* auxNode = st->top, *previousNode = NULL;
    while (auxNode) {
        if (st->compareF(auxNode->data, data) == 0) break;
        // Not the desired element:
        previousNode = auxNode;
        auxNode = auxNode->next;
    }

    // Element not Found:
    if (!auxNode) return;

    // Node contains the desired 
    // information. Proceeding 
    // to remove:
    (st->counter)--;
    
    // Removing the Top of Stack:
    if (!previousNode) {
        st->top = st->top->next;
        if (st->destroyF) st->destroyF(auxNode->data);
        free(auxNode); auxNode = NULL;

        return;
    }

    // Removing the Bottom of Stack:
    if (!auxNode->next) {
        previousNode->next = NULL;
        if (st->destroyF) st->destroyF(auxNode->data);
        free(auxNode); auxNode = NULL;

        return;
    }

    // Removing Element in Middle:
    previousNode->next = auxNode->next;
    if (st->destroyF) st->destroyF(auxNode->data);
    free(auxNode); auxNode = NULL;
    
    return;
}

bool gStackSearch(gStack* st, gStPointerData data) {
    if (!st) return 0;
    if (gStackIsEmpty(st)) return 0;

    gStackNode* auxNode = st->top;
    while (auxNode != NULL) {
        if (st->compareF(auxNode->data, data) == 0) return 1;
        auxNode = auxNode->next;
    }

    return 0;
}