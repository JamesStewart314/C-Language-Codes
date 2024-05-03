#include "genLinkedList.h"


gLinkedList* initgLinkedList(impressFunctionGenLinkedList printF, compareFunctionGenLinkedList compareF) {
    
    if (!printF || !compareF) {
        fprintf(stderr, "Error: At least one of the provided functions is NULL when creating a new generic Linked List.\n");
        return NULL;
    }

    gLinkedList* newlist = (gLinkedList *) malloc (sizeof(gLinkedList));
    if (newlist == NULL) {
        fprintf(stderr, "Failed while trying to allocate memory for a new generic Linked List\n");
        exit(EXIT_FAILURE);
        return NULL;
    }

    newlist->front = newlist->rear = NULL;
    newlist->printF = printF;
    newlist->compareF = compareF;
    newlist->counter = (size_t)0;
    
    return newlist;
}


bool gLinkedListIsEmpty(gLinkedList* list) {
    if (!list) return 1;
    return (list->counter <= (size_t)0);
}


void gLinkedListDestroy(gLinkedList** list) {
    if (!list) return;
    if (!(*list)) return;

    if (gLinkedListIsEmpty((*list))) {
        free((*list)); (*list) = NULL;
        return;
    }

    gLinkedListNode* auxNode = (*list)->front;
    while (auxNode) {
        (*list)->front = (*list)->front->next;
        free(auxNode);
        auxNode = (*list)->front;
    }

    free((*list)); (*list) = NULL;

    return;
}


void gLinkedListAppend(gLinkedList* list, void* data) {
    if (!list) return;

    gLinkedListNode* newnode = (gLinkedListNode *) malloc (sizeof(gLinkedListNode));
    if (newnode == NULL) {
        fprintf(stderr, "Error: Failed while trying to allocate memory for a new generic Linked List node.\n");
        exit(EXIT_FAILURE);
        return;
    }

    newnode->data = data;
    newnode->next = NULL;
    
    if (gLinkedListIsEmpty(list)) {
        list->rear = list->front = newnode;
    } else {
        list->rear->next = newnode;
        list->rear = newnode;
    }

    (list->counter)++;

    return;
}


void* gLinkedListRemove(gLinkedList* list, void* data) {
    if (!list) return NULL;
    if (gLinkedListIsEmpty(list)) return NULL;

    gLinkedListNode *auxNode = list->front, *previous = NULL;
    int result;
    while (auxNode) {
        result = list->compareF(data, auxNode->data);
        if (result == 0) break;
        previous = auxNode;
        auxNode = auxNode->next;
    }

    // Element not found:
    if (!auxNode) return NULL;

    (list->counter)--;

    // Otherwise, element found. Removing:

    // Removing from start:
    if (!previous) {
        void* returnData = auxNode->data;
        
        list->front = list->front->next;
        free(auxNode); auxNode = NULL;

        return returnData;
    }

    // Removing from end:
    if (!auxNode->next) {
        void* returnData = auxNode->data;
        
        list->rear = previous;
        list->rear->next = NULL;
        free(auxNode); auxNode = NULL;

        return returnData;
    }

    // Removing element in the middle:
    void* returnData = auxNode->data;
    previous->next = auxNode->next;
    free(auxNode); auxNode = NULL;

    return returnData;
}


bool gLinkedListSearch(gLinkedList* list, void* data) {
    if (!list) return 0;
    if (gLinkedListIsEmpty(list)) return 0;

    gLinkedListNode *auxNode = list->front;
    int result;
    while (auxNode) {
        result = list->compareF(data, auxNode->data);
        if (result == 0) return 1;
        auxNode = auxNode->next;
    }

    return 0;
}


size_t gLinkedListCount(gLinkedList* list) {
    if (!list) return 0;
    return list->counter;
}


void gLinkedListClear(gLinkedList* list) {
    if (!list) return;
    if (gLinkedListIsEmpty(list)) return;

    gLinkedListNode* auxNode;
    while (list->front) {
        auxNode = list->front;
        list->front = list->front->next;
        free(auxNode); auxNode = NULL;
    }

    list->counter = (size_t)0;
    list->front = list->rear = NULL;

    return;
}


void* gLinkedListPop(gLinkedList* list, long int index) {
    if (!list) return NULL;
    if (gLinkedListIsEmpty(list)) return NULL;

    gLinkedListNode *auxNode = list->front, *previous = NULL;

    if (index == 0) {
        (list->counter)--;
        void* returnData = auxNode->data;
        list->front = list->front->next;
        free(auxNode) ; auxNode = NULL;
        
        return returnData;
    }
    
    index = (index < 0) ? (index + gLinkedListCount(list)) : index;
    if (index >= gLinkedListCount(list) || index < 0) return NULL;

    long int auxCounter = 0;
    while (auxCounter < index) {
        previous = auxNode;
        auxNode = auxNode->next;
        auxCounter++;
    }

    (list->counter)--;

    // Removing from end:
    if (!auxNode->next) {
        void* returnData = auxNode->data;
        
        list->rear = previous;
        list->rear->next = NULL;
        free(auxNode); auxNode = NULL;

        return returnData;
    }

    // Removing element in the middle:
    void* returnData = auxNode->data;
    previous->next = auxNode->next;
    free(auxNode); auxNode = NULL;

    return returnData;
}


void* gLinkedListGetBiggest(gLinkedList* list) {
    if (!list) return NULL;
    if (gLinkedListIsEmpty(list)) return NULL;

    gLinkedListNode* auxNode = list->front;
    void* returnData = auxNode->data;
    while (auxNode) {
        if (list->compareF(auxNode->data, returnData) > 0) returnData = auxNode->data;
        auxNode = auxNode->next;
    }

    return returnData;
}


void* gLinkedListGetSmallest(gLinkedList* list) {
    if (!list) return NULL;
    if (gLinkedListIsEmpty(list)) return NULL;

    gLinkedListNode* auxNode = list->front;
    void* returnData = auxNode->data;
    while (auxNode) {
        if (list->compareF(auxNode->data, returnData) < 0) returnData = auxNode->data;
        auxNode = auxNode->next;
    }

    return returnData;
}


void gLinkedListImpress(gLinkedList* list) {
    if (!list) return;
    if (gLinkedListIsEmpty(list)) { printf("[]"); return; }

    printf("[");
    gLinkedListNode* auxNode = list->front;
    while (auxNode) {
        list->printF(auxNode->data);
        printf(", ");
        auxNode = auxNode->next;
    }

    printf("\b\b]");

    return;
}
