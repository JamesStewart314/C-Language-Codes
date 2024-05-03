#include "genStack.h"

gStack* initgStack(impressFunctionGenStack printF, compareFunctionGenStack compareF) {

    if (!printF || !compareF) {
        fprintf(stderr, "Error: At least one of the provided functions is NULL when creating a new generic Stack.\n");
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

    return newstack;
}


bool gStackIsEmpty(gStack* st) {
    if (!st) return 1;
    return (st->counter <= (size_t)0);
}


void gStackDestroy(gStack** st) {
    if (!st) return;
    if (!(*st)) return;

    if (gStackIsEmpty((*st))) {
        free(*st); (*st) = NULL;
        return;
    }

    gStackNode* auxNode = (*st)->top;
    while (auxNode != NULL) {
        (*st)->top = (*st)->top->next;
        free(auxNode); auxNode = (*st)->top;
    }

    free(*st); (*st) = NULL;

    return;
}


void gStackPush(gStack* st, void* data) {
    if (!st) return;

    gStackNode* newnode = (gStackNode *) malloc (sizeof(gStackNode));
    if (newnode == NULL) {
        fprintf(stderr, "Error: Unable to allocate memory to a new generic Stack node.\n");
        exit(EXIT_FAILURE);
    }

    (st->counter++);
    newnode->data = data;
    newnode->next = st->top;
    st->top = newnode;
    return;
}


void* gStackPop(gStack* st) {
    if (!st) return NULL;
    if (gStackIsEmpty(st)) return NULL;

    (st->counter--);
    gStackNode* auxNode = st->top;
    st->top = st->top->next;

    void* returnData = auxNode->data;
    free(auxNode) ; auxNode = NULL;

    return returnData;
}


size_t gStackCount(gStack* st) {
    if (!st) return (size_t)0;
    return st->counter;
}


void gStackImpress(gStack* st) {
    if (!st) return;
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


void* gStackRemove(gStack* st, void* data) {
    if (!st) return NULL;
    if (gStackIsEmpty(st)) return NULL;

    gStackNode* auxNode = st->top, *previousNode = NULL;
    while (auxNode) {
        if (st->compareF(auxNode->data, data) != 0) {
            // Not the desired element:
            previousNode = auxNode;
            auxNode = auxNode->next;
            continue;
        }

        // Node contains the desired 
        // information. Proceeding 
        // to remove:
        (st->counter)--;
        
        // Removing the Top of Stack:
        if (!previousNode) {
            st->top = st->top->next;
            void* returnData = auxNode->data;
            free(auxNode); auxNode = NULL;

            return returnData;
        }

        // Removing the Bottom of Stack:
        if (!auxNode->next) {
            previousNode->next = NULL;
            void* returnData = auxNode->data;
            free(auxNode); auxNode = NULL;

            return returnData;
        }

        // Removing Element in Middle:
        previousNode->next = auxNode->next;
        void* returnData = auxNode->data;
        free(auxNode); auxNode = NULL;
        
        return returnData;
        
    }

    // Element not Found:
    return NULL;
}

bool gStackSearch(gStack* st, void* data) {
    if (!st) return 0;
    if (gStackIsEmpty(st)) return 0;

    gStackNode* auxNode = st->top;
    while (auxNode != NULL) {
        if (st->compareF(auxNode->data, data) == 0) return 1;
        auxNode = auxNode->next;
    }

    return 0;
}