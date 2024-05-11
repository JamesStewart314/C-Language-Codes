#include "genQueue.h"

gQueue* initgQueue(impressFunctionGenQueue printF, compareFunctionGenQueue compareF, destroyFunctionGenQueue destroyF) {

    if (!compareF) {
        fprintf(stderr, "Error: Compare Function is NULL when creating a new generic Queue.\n");
        return NULL;
    }

    gQueue* newqueue = (gQueue *) malloc (sizeof(gQueue));
    if (newqueue == NULL) {
        fprintf(stderr, "Error: Failed while trying to allocate memory for a new generic Queue.\n");
        exit(EXIT_FAILURE);
        return NULL;
    }

    newqueue->counter = (size_t)0;
    newqueue->front = newqueue->rear = NULL;
    newqueue->printF = printF;
    newqueue->compareF = compareF;
    newqueue->destroyF = destroyF;

    return newqueue;
}


bool gQueueIsEmpty(gQueue* q) { 
    if (!q) return 1;
    return (q->counter <= (size_t)0);
}


void gQueueEnqueue(gQueue* q, Pointer data) {
    if (!q) return;

    gQueueNode* newnode = (gQueueNode *) malloc (sizeof(gQueueNode));
    if (newnode == NULL) {
        fprintf(stderr, "Error: Unable to allocate memory to a new generic Queue node.\n");
        exit(EXIT_FAILURE);
        return;
    }

    newnode->data = data;
    newnode->next = NULL;

    if (gQueueIsEmpty(q)) {
        q->front = q->rear = newnode;
    } else {
        q->rear->next = newnode;
        q->rear = newnode;
    }

    (q->counter)++;

    return;
}


void gQueueImpress(gQueue* q) {
    if (!q) return;
    if (!q->printF) { printf("Unable to Display Queue: PrintF Function Does Not Exist.\n"); return; }
    if (gQueueIsEmpty(q)) { printf("[]"); return; }
    
    printf("[");
    gQueueNode* auxNode = q->front;
    while (auxNode) {
        q->printF(auxNode->data);
        printf(", ");
        auxNode = auxNode->next;
    }
    printf("\b\b]");

    return;
}


void gQueueDestroy(gQueue** q) {
    if (!q) return;
    if (!(*q)) return;

    if (gQueueIsEmpty(*q)) {
        free(*q); (*q) = NULL;
        return;
    };

    gQueueNode* auxNode = (*q)->front;

    do {
        (*q)->front = (*q)->front->next;
        if ((*q)->destroyF) (*q)->destroyF(auxNode->data);
        free(auxNode); auxNode = (*q)->front;
    } while (auxNode);

    free(*q); (*q) = NULL;

    return;
}


bool gQueueSearch(gQueue* q, Pointer data) {
    if (!q) return 0;
    if (gQueueIsEmpty(q)) return 0;

    gQueueNode* auxNode = q->front;
    while(auxNode) {
        if (q->compareF(auxNode->data, data) == 0) return 1;
        auxNode = auxNode->next;
    }

    return 0;
}


void gQueueRemove(gQueue* q, Pointer data) {
    if (!q) return;
    if (gQueueIsEmpty(q)) return;

    gQueueNode* auxNode = q->front, *previous = NULL;
    while(auxNode) {
        if (q->compareF(auxNode->data, data) != 0) {
            // Not the Searched Element:
            previous = auxNode;
            auxNode = auxNode->next;
            continue;
        }
        // Comparison result == 0 => element found:
        break;
    }

    // Element not Found:
    if (!auxNode) return;
    // Otherwise, element Found:
    (q->counter)--;

    // Removing First Element:
    if (!previous) {
        q->front = q->front->next;
        if (q->destroyF) q->destroyF(auxNode->data);
        free(auxNode); auxNode = NULL;
        
        return;
    }

    // Removing Last Element:
    if (!auxNode->next) {
        q->rear = previous;
        q->rear->next = NULL;
        if (q->destroyF) q->destroyF(auxNode->data);
        free(auxNode); auxNode = NULL;
        
        return;
    }

    // Removing Element in Middle:
    previous->next = auxNode->next;
    if (q->destroyF) q->destroyF(auxNode->data);
    free(auxNode); auxNode = NULL;
    
    return;
}


Pointer gQueueDequeue(gQueue* q) {
    if (!q) return NULL;
    if (gQueueIsEmpty(q)) return NULL;

    (q->counter)--;
    gQueueNode* auxNode = q->front;
    q->front = q->front->next;

    Pointer returnData = auxNode->data;
    free(auxNode) ; auxNode = NULL;

    return returnData;
}


size_t gQueueCount(gQueue* q) {
    if (!q) return 0;
    return q->counter;
}


void gQueueClear(gQueue* q) {
    if (!q) return;
    // Queue is already empty:
    if (gQueueIsEmpty(q)) return;

    gQueueNode* auxNode = q->front;
    while (auxNode) {
        q->front = q->front->next;
        if (q->destroyF) q->destroyF(auxNode->data);
        free(auxNode); auxNode = q->front;
    }

    q->counter = (size_t)0;
    q->front = q->rear = NULL;

    return;
}