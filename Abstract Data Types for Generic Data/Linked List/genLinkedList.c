#include "genLinkedList.h"


gLinkedList* initgLinkedList(impressFunctionGenLinkedList printF, compareFunctionGenLinkedList compareF, destroyFuntionGenLinkedList destroyF) {
    
    if (!compareF) {
        fprintf(stderr, "Error: Compare Function is NULL when creating a new generic Linked List.\n");
        return NULL;
    }

    gLinkedList* newlist = (gLinkedList *) malloc (sizeof(gLinkedList));
    if (newlist == NULL) {
        fprintf(stderr, "Error: Failed while trying to allocate memory for a new generic Linked List.\n");
        exit(EXIT_FAILURE);
        return NULL;
    }

    newlist->front = newlist->rear = NULL;
    newlist->printF = printF;
    newlist->compareF = compareF;
    newlist->destroyF = destroyF;
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
        if((*list)->destroyF) (*list)->destroyF(auxNode->data);
        free(auxNode); auxNode = NULL;
        auxNode = (*list)->front;
    }

    free((*list)); (*list) = NULL;

    return;
}


void gLinkedListAppend(gLinkedList* list, Pointer data) {
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


void gLinkedListRemove(gLinkedList* list, Pointer data) {
    if (!list) return;
    if (gLinkedListIsEmpty(list)) return;

    gLinkedListNode *auxNode = list->front, *previous = NULL;
    int result;
    while (auxNode) {
        result = list->compareF(data, auxNode->data);
        if (result == 0) break;
        previous = auxNode;
        auxNode = auxNode->next;
    }

    // Element not found:
    if (!auxNode) return;

    (list->counter)--;

    // Otherwise, element found. Removing:

    // Removing from start:
    if (!previous) {        
        list->front = list->front->next;
        if (list->destroyF) list->destroyF(auxNode->data);
        free(auxNode); auxNode = NULL;

        return;
    }

    // Removing from end:
    if (!auxNode->next) {
        list->rear = previous;
        list->rear->next = NULL;
        if (list->destroyF) list->destroyF(auxNode->data);
        free(auxNode); auxNode = NULL;

        return;
    }

    // Removing element in the middle:
    previous->next = auxNode->next;
    if (list->destroyF) list->destroyF(auxNode->data);
    free(auxNode); auxNode = NULL;

    return;
}


bool gLinkedListSearch(gLinkedList* list, Pointer data) {
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
        if(list->destroyF) list->destroyF(auxNode->data);
        free(auxNode); auxNode = NULL;
    }

    list->counter = (size_t)0;
    list->front = list->rear = NULL;

    return;
}


Pointer gLinkedListPop(gLinkedList* list, long int index) {
    if (!list) return NULL;
    if (gLinkedListIsEmpty(list)) return NULL;

    gLinkedListNode *auxNode = list->front, *previous = NULL;

    if (index == 0) {
        (list->counter)--;
        Pointer returnData = auxNode->data;
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
        Pointer returnData = auxNode->data;
        
        list->rear = previous;
        list->rear->next = NULL;
        free(auxNode); auxNode = NULL;

        return returnData;
    }

    // Removing element in the middle:
    Pointer returnData = auxNode->data;
    previous->next = auxNode->next;
    free(auxNode); auxNode = NULL;

    return returnData;
}


Pointer gLinkedListGetBiggest(gLinkedList* list) {
    if (!list) return NULL;
    if (gLinkedListIsEmpty(list)) return NULL;

    gLinkedListNode* auxNode = list->front;
    Pointer returnData = auxNode->data;
    while (auxNode) {
        if (list->compareF(auxNode->data, returnData) > 0) returnData = auxNode->data;
        auxNode = auxNode->next;
    }

    return returnData;
}


Pointer gLinkedListGetSmallest(gLinkedList* list) {
    if (!list) return NULL;
    if (gLinkedListIsEmpty(list)) return NULL;

    gLinkedListNode* auxNode = list->front;
    Pointer returnData = auxNode->data;
    while (auxNode) {
        if (list->compareF(auxNode->data, returnData) < 0) returnData = auxNode->data;
        auxNode = auxNode->next;
    }

    return returnData;
}


void gLinkedListImpress(gLinkedList* list) {
    if (!list) return;
    if (!list->printF) { printf("Unable to Display Linked List: PrintF Function Does Not Exist.\n"); return; };
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

void gLinkedListReverse(gLinkedList* list) {
    if (!list) return;
    if (gLinkedListIsEmpty(list) || gLinkedListCount(list) == 1) return;

    // The list has at least two elements:

    list->rear = list->front;
    // Employing the use of three contiguous pointers to traverse the linked list, rearranging their 
    // pointers in order to reverse the order of arrangement of the elements present in the list:
    gLinkedListNode *auxNode = list->front, *auxNodePrevious = NULL, *auxNodeNext = auxNode->next;
    while(auxNodeNext != NULL) {
        auxNode->next = auxNodePrevious;
        auxNodePrevious = auxNode;
        auxNode = auxNodeNext;
        auxNodeNext = auxNodeNext->next;
    }

    auxNode->next = auxNodePrevious;
    list->front = auxNode;
    
    return;
}