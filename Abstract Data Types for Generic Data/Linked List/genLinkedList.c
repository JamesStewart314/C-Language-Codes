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


void gLinkedListAppend(gLinkedList* list, gLkLsPointerData data) {
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


void gLinkedListRemove(gLinkedList* list, gLkLsPointerData data) {
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


bool gLinkedListSearch(gLinkedList* list, gLkLsPointerData data) {
    if (!list) return 0;
    if (gLinkedListIsEmpty(list)) return 0;

    gLinkedListNode *auxNode = list->front;
    while (auxNode) {
        if (list->compareF(data, auxNode->data) == 0) return 1;
        auxNode = auxNode->next;
    }

    return 0;
}


size_t gLinkedListSize(gLinkedList* list) {
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


gLkLsPointerData gLinkedListPop(gLinkedList* list, long int index) {
    if (!list) return NULL;
    if (gLinkedListIsEmpty(list)) return NULL;

    gLinkedListNode *auxNode = list->front, *previous = NULL;

    if (index == 0) {
        (list->counter)--;
        gLkLsPointerData returnData = auxNode->data;
        list->front = list->front->next;
        free(auxNode) ; auxNode = NULL;
        
        return returnData;
    }
    
    index = (index < 0) ? (index + gLinkedListSize(list)) : index;
    if (index >= gLinkedListSize(list) || index < 0) return NULL;

    long int auxCounter = 0;
    while (auxCounter < index) {
        previous = auxNode;
        auxNode = auxNode->next;
        auxCounter++;
    }

    (list->counter)--;

    // Removing from end:
    if (!auxNode->next) {
        gLkLsPointerData returnData = auxNode->data;
        
        list->rear = previous;
        list->rear->next = NULL;
        free(auxNode); auxNode = NULL;

        return returnData;
    }

    // Removing element in the middle:
    gLkLsPointerData returnData = auxNode->data;
    previous->next = auxNode->next;
    free(auxNode); auxNode = NULL;

    return returnData;
}


gLkLsPointerData gLinkedListGetBiggest(gLinkedList* list) {
    if (!list) return NULL;
    if (gLinkedListIsEmpty(list)) return NULL;

    gLinkedListNode* auxNode = list->front;
    gLkLsPointerData returnData = auxNode->data;
    while (auxNode) {
        if (list->compareF(auxNode->data, returnData) > 0) returnData = auxNode->data;
        auxNode = auxNode->next;
    }

    return returnData;
}


gLkLsPointerData gLinkedListGetSmallest(gLinkedList* list) {
    if (!list) return NULL;
    if (gLinkedListIsEmpty(list)) return NULL;

    gLinkedListNode* auxNode = list->front;
    gLkLsPointerData returnData = auxNode->data;
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
    if (gLinkedListIsEmpty(list) || gLinkedListSize(list) == 1) return;

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
        if (!gLinkedListSearch(list2, auxNode->data)) return 0;
        auxNode = auxNode->next;
    }

    return 1;
}


size_t gLinkedListCount(gLinkedList* list, gLkLsPointerData data) {
    if (!list) return (size_t)0;
    if (gLinkedListIsEmpty(list)) return (size_t)0;

    size_t auxCounter = (size_t)0;
    gLinkedListNode* auxNode = list->front;
    while (auxNode) {
        if (list->compareF(auxNode->data, data) == 0) auxCounter++;
        auxNode = auxNode->next;
    }

    return auxCounter;
}


gLinkedList* gLinkedListCopy(gLinkedList* list) {

    // NOT IMPLEMENTED YET...
    return NULL;

    /*

    if (!list) return NULL;

    gLinkedList* newlist = initgLinkedList(list->printF, list->compareF, list->destroyF);

    if (gLinkedListIsEmpty(list)) return newlist;

    gLinkedListNode* auxNode = list->front;
    
    gLinkedListNode* newnode = (gLinkedListNode *)malloc(sizeof(gLinkedListNode));
    if (newnode == NULL) {
        fprintf(stderr, "Error: Failed while trying to allocate memory for a new generic Linked List node.\n");
        exit(EXIT_FAILURE);
        return;
    }

    */
}