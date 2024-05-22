#include "genQueue.h"

gQueue* initgQueue(impressFunctionGenQueue printF, compareFunctionGenQueue compareF,
                   destroyFunctionGenQueue destroyF, deepcopyFunctionGenQueue deepcopyF) {

    if (!compareF) {
        fprintf(stderr, "Error: Compare Function is NULL when creating a new generic Queue.\n");
        return NULL;
    }

    gQueue* newqueue = (gQueue *) malloc(sizeof(gQueue));
    if (newqueue == NULL) {
        fprintf(stderr, "Error: Failed while trying to allocate memory for a new generic Queue.\n");
        exit(EXIT_FAILURE);
        return NULL;
    }

    newqueue->counter = (uint32_t)0;
    newqueue->front = newqueue->rear = NULL;
    newqueue->printF = printF;
    newqueue->compareF = compareF;
    newqueue->destroyF = destroyF;
    newqueue->deepcopyF = deepcopyF;

    return newqueue;
}


gQueue* gQueueCopy(gQueue* q) {
    if (!q) return NULL;

    gQueue* newqueue = initgQueue(q->printF, q->compareF, q->destroyF, q->deepcopyF);

    if (gQueueIsEmpty(q)) return newqueue;

    gQueueNode* auxNode = q->front;
    while (auxNode) {
        gQueueEnqueue(newqueue, (q->deepcopyF ? (q->deepcopyF(auxNode->data)) : auxNode->data));
        auxNode = auxNode->next;
    }

    return newqueue;
}


void gQueueClear(gQueue* q) {
    if (!q) return;
    // Queue is already empty:
    if (gQueueIsEmpty(q)) return;

    gQueueNode* auxNode = q->front;
    do {
        q->front = q->front->next;
        if (q->destroyF) q->destroyF(auxNode->data);
        free(auxNode); auxNode = q->front;
    } while (auxNode);

    q->counter = (uint32_t)0;
    q->front = q->rear = NULL;

    return;
}


void gQueueDestroy(gQueue** qPointer) {
    if (!qPointer) return;
    if (!(*qPointer)) return;

    if (gQueueIsEmpty(*qPointer)) {
        free(*qPointer); (*qPointer) = NULL;
        return;
    }

    gQueueNode* auxNode = (*qPointer)->front;

    do {
        (*qPointer)->front = (*qPointer)->front->next;
        if ((*qPointer)->destroyF) (*qPointer)->destroyF(auxNode->data);
        free(auxNode); auxNode = (*qPointer)->front;
    } while (auxNode);

    free(*qPointer); (*qPointer) = NULL;

    return;
}


void gQueueEnqueue(gQueue* q, gQueueDataPtr data) {
    if (!q) return;

    gQueueNode* newnode = (gQueueNode *) malloc(sizeof(gQueueNode));
    if (newnode == NULL) {
        fprintf(stderr, "Error: Unable to allocate memory to a new generic Queue node.\n");
        exit(EXIT_FAILURE);
        return;
    }

    newnode->data = data;
    newnode->next = NULL;

    if (gQueueIsEmpty(q)) {
        q->front = q->rear = newnode;
        (q->counter)++;
        return;
    }

    q->rear->next = newnode;
    q->rear = newnode;
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


void gQueueRemove(gQueue* q, gQueueDataPtr data) {
    if (!q) return;
    if (gQueueIsEmpty(q)) return;

    gQueueNode* auxNode = q->front, *previous = NULL;
    while (auxNode) {
        if (q->compareF(auxNode->data, data) == 0) break;
        // Not the Searched Element:
        previous = auxNode;
        auxNode = auxNode->next;
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


bool gQueueIsEmpty(gQueue* q) { 
    if (!q) return 1;
    return (q->counter <= (uint32_t)0);
}


bool gQueueIsEquals(gQueue* q1, gQueue* q2) {
    if (!q1 || !q2) return (!q1 && !q2);

    if (q1->compareF != q2->compareF) {
        fprintf(stderr, "Error: It is not possible to compare two generic queues whose comparison functions differ from each other.\n");
        return 0;
    }

    if (gQueueIsEmpty(q1) || gQueueIsEmpty(q2)) return (gQueueIsEmpty(q1) && gQueueIsEmpty(q2));

    if (q1->counter != q2->counter) return 0;

    gQueueNode *auxNode1 = q1->front, *auxNode2 = q2->front;
    while (auxNode1 && auxNode2) {
        if (q1->compareF(auxNode1->data, auxNode2->data) != 0) return 0;
        auxNode1 = auxNode1->next;
        auxNode2 = auxNode2->next;
    }

    return (!auxNode1 && !auxNode2);
}


bool gQueueHasSameElements(gQueue* q1, gQueue* q2) {
    if (!q1 || !q2) return (!q1 && !q2);

    if (q1->compareF != q2->compareF) {
        fprintf(stderr, "Error: It is not possible to compare two generic queues whose comparison functions differ from each other.\n");
        return 0;
    }

    if (gQueueIsEmpty(q1) || gQueueIsEmpty(q2)) return (gQueueIsEmpty(q1) && gQueueIsEmpty(q2));

    gQueueNode* auxNode = q1->front;
    while (auxNode) {
        if (gQueueCount(q1, auxNode->data) != gQueueCount(q2, auxNode->data)) return 0;
        auxNode = auxNode->next;
    }

    return 1;
}


bool gQueueShareSameElements(gQueue* q1, gQueue* q2) {
    if (!q1 || !q2) return (!q1 && !q2);

    if (q1->compareF != q2->compareF) {
        fprintf(stderr, "Error: It is not possible to compare two generic queues whose comparison functions differ from each other.\n");
        return 0;
    }

    if (gQueueIsEmpty(q1) || gQueueIsEmpty(q2)) return (gQueueIsEmpty(q1) && gQueueIsEmpty(q2));

    gQueueNode* auxNode = q1->front;
    while (auxNode) {
        if (!gQueueSearch(q2, auxNode->data)) return 0;
        auxNode = auxNode->next;
    }

    return 1;
}


bool gQueueSearch(gQueue* q, gQueueDataPtr data) {
    if (!q) return 0;
    if (gQueueIsEmpty(q)) return 0;

    gQueueNode* auxNode = q->front;
    while (auxNode) {
        if (q->compareF(auxNode->data, data) == 0) return 1;
        auxNode = auxNode->next;
    }

    return 0;
}


uint32_t gQueueCount(gQueue* q, gQueueDataPtr data) {
    if (!q) return (uint32_t)0;
    if (gQueueIsEmpty(q)) return (uint32_t)0;

    uint32_t auxCounter = (uint32_t)0;
    gQueueNode* auxNode = q->front;
    while (auxNode) {
        if (q->compareF(auxNode->data, data) == 0) auxCounter++;
        auxNode = auxNode->next;
    }

    return auxCounter;
}


uint32_t gQueueSize(gQueue* q) {
    if (!q) return 0;
    return q->counter;
}


gQueueDataPtr gQueueDequeue(gQueue* q) {
    if (!q) return NULL;
    if (gQueueIsEmpty(q)) return NULL;

    (q->counter)--;
    gQueueNode* auxNode = q->front;
    q->front = q->front->next;

    gQueueDataPtr returnData = auxNode->data;
    free(auxNode); auxNode = NULL;

    return returnData;
}


gQueueDataPtr gQueueGetBiggest(gQueue* q) {
    if (!q) return NULL;
    if (gQueueIsEmpty(q)) return NULL;

    gQueueNode* auxNode = q->front;
    gQueueDataPtr returnData = auxNode->data;
    while (auxNode) {
        if (q->compareF(auxNode->data, returnData) > 0) returnData = auxNode->data;
        auxNode = auxNode->next;
    }

    return returnData;
}


gQueueDataPtr gQueueGetSmallest(gQueue* q) {
    if (!q) return NULL;
    if (gQueueIsEmpty(q)) return NULL;

    gQueueNode* auxNode = q->front;
    gQueueDataPtr returnData = auxNode->data;
    while (auxNode) {
        if (q->compareF(auxNode->data, returnData) < 0) returnData = auxNode->data;
        auxNode = auxNode->next;
    }

    return returnData;
}