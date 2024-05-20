#include "genLinkedList.h"


gLinkedList* initgLinkedList(impressFunctionGenLinkedList printF, compareFunctionGenLinkedList compareF,
                             destroyFuntionGenLinkedList destroyF, deepcopyFunctionGenLinkedList deepcopyF) {
    
    if (!compareF) {
        fprintf(stderr, "Error: Compare Function is NULL when creating a new generic Linked List.\n");
        return NULL;
    }

    gLinkedList* newlist = (gLinkedList *) malloc(sizeof(gLinkedList));
    if (newlist == NULL) {
        fprintf(stderr, "Error: Failed while trying to allocate memory for a new generic Linked List.\n");
        exit(EXIT_FAILURE);
        return NULL;
    }

    newlist->front = newlist->rear = NULL;
    newlist->counter = (uint32_t)0;
    newlist->printF = printF;
    newlist->compareF = compareF;
    newlist->destroyF = destroyF;
    newlist->deepcopyF = deepcopyF;
    
    return newlist;
}


gLinkedList* gLinkedListCopy(gLinkedList* list) {
    if (!list) return NULL;

    gLinkedList* newlist = initgLinkedList(list->printF, list->compareF, list->destroyF, list->deepcopyF);
    if (gLinkedListIsEmpty(list)) return newlist;

    gLinkedListNode *auxNode = list->front;
    while (auxNode) {
        gLinkedListAppend(newlist, (list->deepcopyF ? (list->deepcopyF(auxNode->data)) : auxNode->data));
        auxNode = auxNode->next;
    }

    return newlist;
}


void gLinkedListAppend(gLinkedList* list, gLinkedListDataPtr data) {
    if (!list) return;

    gLinkedListNode* newnode = (gLinkedListNode *) malloc(sizeof(gLinkedListNode));
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

    list->counter = (uint32_t)0;
    list->front = list->rear = NULL;

    return;
}


void gLinkedListDestroy(gLinkedList** listPointer) {
    if (!listPointer) return;
    if (!(*listPointer)) return;

    if (gLinkedListIsEmpty((*listPointer))) {
        free((*listPointer)); (*listPointer) = NULL;
        return;
    }

    gLinkedListNode* auxNode = (*listPointer)->front;
    while (auxNode) {
        (*listPointer)->front = (*listPointer)->front->next;
        if((*listPointer)->destroyF) (*listPointer)->destroyF(auxNode->data);
        free(auxNode); auxNode = NULL;
        auxNode = (*listPointer)->front;
    }

    free((*listPointer)); (*listPointer) = NULL;

    return;
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


void gLinkedListRemove(gLinkedList* list, gLinkedListDataPtr data) {
    if (!list) return;
    if (gLinkedListIsEmpty(list)) return;

    gLinkedListNode *auxNode = list->front, *previous = NULL;
    while (auxNode) {
        if (list->compareF(data, auxNode->data) == 0) break;
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


void gLinkedListReverse(gLinkedList* list) {
    if (!list) return;
    if (gLinkedListIsEmpty(list) || gLinkedListSize(list) == 1) return;

    // The list has at least two elements:

    list->rear = list->front;
    // Employing the use of three contiguous pointers to traverse the linked list, rearranging their 
    // pointers in order to reverse the order of arrangement of the elements present in the list:
    gLinkedListNode *auxNode = list->front, *auxNodePrevious = NULL, *auxNodeNext = auxNode->next;
    while (auxNodeNext != NULL) {
        auxNode->next = auxNodePrevious;
        auxNodePrevious = auxNode;
        auxNode = auxNodeNext;
        auxNodeNext = auxNodeNext->next;
    }

    auxNode->next = auxNodePrevious;
    list->front = auxNode;
    
    return;
}


bool gLinkedListIsEmpty(gLinkedList* list) {
    if (!list) return 1;
    return (list->counter <= (uint32_t)0);
}


bool gLinkedListIsEquals(gLinkedList* list1, gLinkedList* list2) {
    if (!list1 || !list2) return (!list1 && !list2);

    if (list1->compareF != list2->compareF) {
        fprintf(stderr, "Error: It is not possible to compare two linked lists whose comparison functions differ from each other.\n");
        return 0;
    }

    if (gLinkedListIsEmpty(list1) || gLinkedListIsEmpty(list2)) return (gLinkedListIsEmpty(list1) && gLinkedListIsEmpty(list2));

    if (list1->counter != list2->counter) return 0;

    gLinkedListNode *auxNode1 = list1->front, *auxNode2 = list2->front;
    while (auxNode1 && auxNode2) {
        if (list1->compareF(auxNode1->data, auxNode2->data) != 0) return 0;
        auxNode1 = auxNode1->next;
        auxNode2 = auxNode2->next;
    }

    return (!auxNode1 && !auxNode2);
}


bool gLinkedListSearch(gLinkedList* list, gLinkedListDataPtr data) {
    if (!list) return 0;
    if (gLinkedListIsEmpty(list)) return 0;

    gLinkedListNode *auxNode = list->front;
    while (auxNode) {
        if (list->compareF(data, auxNode->data) == 0) return 1;
        auxNode = auxNode->next;
    }

    return 0;
}


bool gLinkedListHasSameElements(gLinkedList* list1, gLinkedList* list2) {
    if (!list1 || !list2) return (!list1 && !list2);

    if (list1->compareF != list2->compareF) {
        fprintf(stderr, "Error: It is not possible to compare two linked lists whose comparison functions differ from each other.\n");
        return 0;
    }

    if (gLinkedListIsEmpty(list1) || gLinkedListIsEmpty(list2)) return (gLinkedListIsEmpty(list1) && gLinkedListIsEmpty(list2));

    if (list1->counter != list2->counter) return 0;

    gLinkedListNode* auxNode = list1->front;
    while (auxNode) {
        if (gLinkedListCount(list1, auxNode->data) != gLinkedListCount(list2, auxNode->data)) return 0;
        auxNode = auxNode->next;
    }

    return 1;
}


bool gLinkedListShareSameElements(gLinkedList* list1, gLinkedList* list2) {
    if (!list1 || !list2) return (!list1 && !list2);

    if (list1->compareF != list2->compareF) {
        fprintf(stderr, "Error: It is not possible to compare two linked lists whose comparison functions differ from each other.\n");
        return 0;
    }

    if (gLinkedListIsEmpty(list1) || gLinkedListIsEmpty(list2)) return (gLinkedListIsEmpty(list1) && gLinkedListIsEmpty(list2));

    gLinkedListNode* auxNode = list1->front;
    while (auxNode) {
        if (!gLinkedListSearch(list2, auxNode->data)) return 0;
        auxNode = auxNode->next;
    }

    return 1;
}


uint32_t gLinkedListCount(gLinkedList* list, gLinkedListDataPtr data) {
    if (!list) return (uint32_t)0;
    if (gLinkedListIsEmpty(list)) return (uint32_t)0;

    uint32_t auxCounter = (uint32_t)0;
    gLinkedListNode* auxNode = list->front;
    while (auxNode) {
        if (list->compareF(auxNode->data, data) == 0) auxCounter++;
        auxNode = auxNode->next;
    }

    return auxCounter;
}


uint32_t gLinkedListSize(gLinkedList* list) {
    if (!list) return 0;
    return list->counter;
}


gLinkedListDataPtr gLinkedListGetBiggest(gLinkedList* list) {
    if (!list) return NULL;
    if (gLinkedListIsEmpty(list)) return NULL;

    gLinkedListNode* auxNode = list->front;
    gLinkedListDataPtr returnData = auxNode->data;
    while (auxNode) {
        if (list->compareF(auxNode->data, returnData) > 0) returnData = auxNode->data;
        auxNode = auxNode->next;
    }

    return returnData;
}


gLinkedListDataPtr gLinkedListGetSmallest(gLinkedList* list) {
    if (!list) return NULL;
    if (gLinkedListIsEmpty(list)) return NULL;

    gLinkedListNode* auxNode = list->front;
    gLinkedListDataPtr returnData = auxNode->data;
    while (auxNode) {
        if (list->compareF(auxNode->data, returnData) < 0) returnData = auxNode->data;
        auxNode = auxNode->next;
    }

    return returnData;
}


gLinkedListDataPtr gLinkedListPop(gLinkedList* list, int32_t index) {
    if (!list) return NULL;
    if (gLinkedListIsEmpty(list)) return NULL;

    gLinkedListNode *auxNode = list->front, *previous = NULL;

    if (index == 0) {
        (list->counter)--;
        gLinkedListDataPtr returnData = auxNode->data;
        list->front = list->front->next;
        free(auxNode) ; auxNode = NULL;
        
        return returnData;
    }
    
    index = (index < (int32_t)0) ? (index + (int32_t)gLinkedListSize(list)) : index;
    if (index >= (int32_t)gLinkedListSize(list) || index < (int32_t)0) return NULL;

    uint32_t auxCounter = 0;
    while (auxCounter < index) {
        previous = auxNode;
        auxNode = auxNode->next;
        auxCounter++;
    }

    (list->counter)--;

    // Removing from end:
    if (!auxNode->next) {
        gLinkedListDataPtr returnData = auxNode->data;
        
        list->rear = previous;
        list->rear->next = NULL;
        free(auxNode); auxNode = NULL;

        return returnData;
    }

    // Removing element in the middle:
    gLinkedListDataPtr returnData = auxNode->data;
    previous->next = auxNode->next;
    free(auxNode); auxNode = NULL;

    return returnData;
}
