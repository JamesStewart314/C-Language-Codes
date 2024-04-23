#include "genQueue.h"

gQueue* initQueue(impressFunctionQueue printQ, compareFunctionQueue compareQ) {

    gQueue* newqueue = (gQueue *) malloc (sizeof(gQueue));
    if (newqueue == NULL) {
        fprintf(stderr, "Error: Failed while trying to allocate memory for a new queue.\n");
        exit(EXIT_FAILURE);
        return NULL;
    }

    newqueue->counter = (size_t)0;
    newqueue->front = newqueue->rear = NULL;
    newqueue->printQ = printQ;
    newqueue->compareQ = compareQ;

    return newqueue;
}


bool queueIsEmpty(gQueue* q) { 
    if (!q) return 1;
    return (q->front == NULL);
}


void enqueue(gQueue* q, void* data) {
    gNodeQueue* newnode = (gNodeQueue *) malloc (sizeof(gNodeQueue));
    if (newnode == NULL) {
        fprintf(stderr, "Error: Unable to allocate memory to a new Queue node.\n");
        exit(EXIT_FAILURE);
    }

    newnode->data = data;
    newnode->next = NULL;
    (q->counter)++;

    if (queueIsEmpty(q)) {
        q->front = q->rear = newnode;
    } else {
        q->rear->next = newnode;
        q->rear = newnode;
    }

    return;
}


void impressQueue(gQueue* q) {
    if (!q) return;
    if (queueIsEmpty(q)) { printf("[]"); return; }
    
    printf("[");
    gNodeQueue* nodeAux = q->front;
    while (nodeAux) {
        q->printQ(nodeAux->data);
        printf(", ");
        nodeAux = nodeAux->next;
    }
    printf("\b\b]");
}


void freeQueue(gQueue** q) {
    if (!q) return;
    if (!(*q)) return;
    if (queueIsEmpty(*q)) {
        free(*q);
        (*q) = NULL;
        return;
    };

    gNodeQueue* nodeAux = (*q)->front;

    do {
        (*q)->front = (*q)->front->next;
        free(nodeAux);
        nodeAux = (*q)->front;
    } while (nodeAux);

    free(*q);
    (*q) = NULL;

    return;
}


bool searchInQueue(gQueue* q, void* data) {
    if (!q) return 0;
    if (queueIsEmpty(q)) return 0;

    gNodeQueue* nodeAux = q->front;
    while(nodeAux) {
        if (q->compareQ(nodeAux->data, data) == 0) return 1;
        nodeAux = nodeAux->next;
    }

    return 0;
}


void* removeFromQueue(gQueue* q, void* data) {
    if (!q) return NULL;
    if (queueIsEmpty(q)) return NULL;

    gNodeQueue* nodeAux = q->front, *previous = NULL;
    while(nodeAux) {
        if (q->compareQ(nodeAux->data, data) != 0) {
            // Not the Searched Element:
            previous = nodeAux;
            nodeAux = nodeAux->next;
            continue;
        }
        
        // Element Found:
        (q->counter)--;

        // Removing First Element:
        if (!previous) {
            q->front = q->front->next;
            
            void* returnData = nodeAux->data;
            free(nodeAux); nodeAux = NULL;
            return returnData;
        }

        // Removing Last Element:
        if (!nodeAux->next) {
            q->rear = previous;
            previous->next = NULL;

            void* returnData = nodeAux->data;
            free(nodeAux); nodeAux = NULL;
            
            return returnData;
        }

        // Removing Element in Middle:
        previous->next = nodeAux->next;
        void* returnData = nodeAux->data;
        free(nodeAux); nodeAux = NULL;
        
        return returnData;
    }

    // Element not Found:
    return NULL;
}


void* dequeue(gQueue* q) {
    if (!q) return NULL;
    if (queueIsEmpty(q)) return NULL;

    (q->counter)--;
    gNodeQueue* nodeAux = q->front;
    q->front = q->front->next;

    void* returnData = nodeAux->data;
    free(nodeAux) ; nodeAux = NULL;

    return returnData;
}


size_t queueCount(gQueue* q) {
    if (!q) return 0;
    return q->counter;
}
