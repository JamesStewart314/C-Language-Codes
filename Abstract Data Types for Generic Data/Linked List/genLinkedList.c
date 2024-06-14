#include "genLinkedList.h"


gLinkedListNode* mergeGenericLinkedList(gLinkedListNode* node1, uint32_t size1, gLinkedListNode* node2, uint32_t size2, gLinkedList* list) {
    // if (!node1 || !node2) return ((node1 != NULL) ? node1 : node2);

    gLinkedListNode *auxNode1 = node1, *auxNode2 = node2;

    // Variables to get the new start and end of the 
    // linked list during the merge process:
    gLinkedListNode *tempFront = NULL, *tempRear = NULL;

    // Variable to track the results of comparisons:
    int comparisonResult;

    /* We perform the first step of the merge outside the loop to avoid 
    redundant checks for the case where the tempFront pointer is NULL. 
    In this way, we obtain a small performance gain in the algorithm 
    as a whole. */
    comparisonResult = list->compareF(auxNode1->data, auxNode2->data);

    if (comparisonResult < 0) {
        tempFront = tempRear = auxNode1;
        auxNode1 = auxNode1->next;
        size1--;

    } else if (comparisonResult > 0) {
        tempFront = tempRear = auxNode2;
        auxNode2 = auxNode2->next;
        size2--;

    } else {
        tempFront = tempRear = auxNode1;

        auxNode1 = auxNode1->next;
        size1--;

        tempRear->next = auxNode2;
        tempRear = auxNode2;
        
        auxNode2 = auxNode2->next;            
        size2--;
    }

    while ((size1 > 0) && (size2 > 0)) {
        comparisonResult = list->compareF(auxNode1->data, auxNode2->data);

        if (comparisonResult < 0) {
            tempRear->next = auxNode1;
            tempRear = auxNode1;

            auxNode1 = auxNode1->next;
            size1--;

        } else if (comparisonResult > 0) {
            tempRear->next = auxNode2;
            tempRear = auxNode2;

            auxNode2 = auxNode2->next;
            size2--;

        } else {
            tempRear->next = auxNode1;
            tempRear = auxNode1;

            auxNode1 = auxNode1->next;
            size1--;

            tempRear->next = auxNode2;
            tempRear = auxNode2;
            
            auxNode2 = auxNode2->next;            
            size2--;
        }
    }

    // If the right side of the merge is exhausted first:
    if (size2 <= 0 && size1 > 0) {
        gLinkedListNode* finalNode = tempRear->next;

        while (size1 > 0) {
            tempRear->next = auxNode1;
            tempRear = auxNode1;
            auxNode1 = auxNode1->next;
            size1--;
        }

        tempRear->next = finalNode;
    }

    // If the left side of the merge is exhausted first:
    if (size1 <= 0 && size2 > 0) {
        while (size2 > 0) {
            tempRear->next = auxNode2;
            tempRear = auxNode2;
            auxNode2 = auxNode2->next;
            size2--;
        }
    }
    
    list->front = tempFront;
    list->rear = tempRear;

    return tempFront;
}


gLinkedListNode* recursiveMergeSortGenericLinkedList(gLinkedListNode* node, uint32_t size, gLinkedList* list, gLinkedListNode** frontResult, gLinkedListNode** rearResult) {
    
    if (size <= 0) return NULL;
    if (size == (uint32_t)1) {
        list->front = list->rear = node;
        (*frontResult) = (*rearResult) = node;
        return node;
    }

    if (size == (uint32_t)2) {

        int comparisonResult = list->compareF(node->data, node->next->data);
        if (comparisonResult <= 0) {
            list->front = node;
            list->rear = node->next;
            
            (*frontResult) = node;
            (*rearResult) = node->next;

            return node;
        }

        gLinkedListNode* nextNode = node->next;
        node->next = nextNode->next;
        nextNode->next = node;

        list->front = nextNode;
        list->rear = node;

        (*frontResult) = nextNode;
        (*rearResult) = nextNode->next;

        return nextNode;        
    }

    uint32_t middlePoint = (size / (uint32_t)2);
    uint32_t auxCounter = middlePoint;

    gLinkedListNode* middleNode = node;
    while (auxCounter > 0) {
        middleNode = middleNode->next;
        auxCounter--;
    }

    gLinkedListNode *leftMergeSortFrontResult, *leftMergeSortRearResult;
    gLinkedListNode *leftMergeSortResult = recursiveMergeSortGenericLinkedList(node, middlePoint, list, &leftMergeSortFrontResult, &leftMergeSortRearResult);
    gLinkedListNode *rightMergeSortFrontResult, *rightMergeSortRearResult;
    gLinkedListNode *rightMergeSortResult = recursiveMergeSortGenericLinkedList(middleNode, size - middlePoint, list, &rightMergeSortFrontResult, &rightMergeSortRearResult);

    leftMergeSortRearResult->next = rightMergeSortFrontResult;

    gLinkedListNode* mergeResult = mergeGenericLinkedList(leftMergeSortResult, middlePoint, rightMergeSortResult, size - middlePoint, list);

    (*frontResult) = list->front;
    (*rearResult) = list->rear;

    return mergeResult;
}


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
        if (list->destroyF) list->destroyF(auxNode->data);
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


void gLinkedListInsert(gLinkedList* list, int32_t index, gLinkedListDataPtr data) {
    if (!list) return;

    gLinkedListNode* newnode = (gLinkedListNode *) malloc(sizeof(gLinkedListNode));
    if (newnode == NULL) {
        fprintf(stderr, "Error: Failed while trying to allocate memory for a new generic Linked List node.\n");
        exit(EXIT_FAILURE);
        return;
    }

    newnode->data = data;

    if (gLinkedListIsEmpty(list)) {
        newnode->next = NULL;
        list->front = list->rear = newnode;
        (list->counter)++;

        return;
    }

    index = (index < (int32_t)0) ? ((int32_t)gLinkedListSize(list) + index) : index;

    // Inserting the element at the beginning of the list:
    if (index <= (int32_t)0) {
        newnode->next = list->front;
        list->front = newnode;
        (list->counter)++;

        return;
    }

    // Inserting the new element at the end of the list:
    if (index >= (int32_t)gLinkedListSize(list)) {
        newnode->next = NULL;
        list->rear->next = newnode;
        list->rear = newnode;
        (list->counter)++;

        return;
    }

    // inserting the new element at some intermediate index of the list:
    gLinkedListNode *auxNode = list->front, *previous = NULL;
    while (index > 0) {
        previous = auxNode;
        auxNode = auxNode->next;
        index--;
    }

    previous->next = newnode;
    newnode->next = auxNode;
    (list->counter)++;

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


void gLinkedListRemoveAll(gLinkedList* list, gLinkedListDataPtr data) {
    if (!list) return;
    if (gLinkedListIsEmpty(list)) return;

    gLinkedListNode *auxNode = list->front, *previous = NULL;
    while (auxNode) {
        if (list->compareF(auxNode->data, data) != 0) {
            previous = auxNode;
            auxNode = auxNode->next;
            continue;
        }

        // Element Found:

        (list->counter--);
        if (previous) {
            // Not removing from the start:
            if (auxNode->next) {
                // Removing in the middle:
                previous->next = auxNode->next;
                if (list->destroyF) list->destroyF(auxNode->data);
                free(auxNode);
                auxNode = previous->next;

            } else {
                // Removing from the end:
                previous->next = NULL;
                list->rear = previous;
                if (list->destroyF) list->destroyF(auxNode->data);
                free(auxNode); auxNode = NULL;
            }

        } else {
            // Removing from the start:
            list->front = list->front->next;
            if (list->destroyF) list->destroyF(auxNode->data);
            free(auxNode);
            auxNode = list->front;
        }
    }

    return;
}


bool gLinkedListIsEmpty(gLinkedList* list) {
    if (!list) return 1;
    return (list->counter <= 0);
}


bool gLinkedListRemove(gLinkedList* list, gLinkedListDataPtr data) {
    if (!list) return 0;
    if (gLinkedListIsEmpty(list)) return 0;

    gLinkedListNode *auxNode = list->front, *previous = NULL;
    while (auxNode) {
        if (list->compareF(data, auxNode->data) == 0) break;
        previous = auxNode;
        auxNode = auxNode->next;
    }

    // Element not found:
    if (!auxNode) return 0;

    (list->counter)--;

    // Otherwise, element found. Removing:

    // Removing from start:
    if (!previous) {        
        list->front = list->front->next;
        if (list->destroyF) list->destroyF(auxNode->data);
        free(auxNode); auxNode = NULL;

        return 1;
    }

    // Removing from end:
    if (!auxNode->next) {
        list->rear = previous;
        list->rear->next = NULL;
        if (list->destroyF) list->destroyF(auxNode->data);
        free(auxNode); auxNode = NULL;

        return 1;
    }

    // Removing element in the middle:
    previous->next = auxNode->next;
    if (list->destroyF) list->destroyF(auxNode->data);
    free(auxNode); auxNode = NULL;

    return 1;
}


bool gLinkedListIsEquals(gLinkedList* list1, gLinkedList* list2) {
    if (!list1 || !list2) return (!list1 && !list2);

    if (list1->compareF != list2->compareF) {
        fprintf(stderr, "Error: It is not possible to compare two generic linked lists whose comparison functions differ from each other.\n");
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


void gLinkedListSort(gLinkedList* list) {
    if (!list) return;
    if (gLinkedListIsEmpty(list) || gLinkedListSize(list) == (uint32_t)1) return;

    gLinkedListNode *newFront, *newRear;
    recursiveMergeSortGenericLinkedList(list->front, list->counter, list, &newFront, &newRear);

    //list->front = newFront;
    //list->rear = newRear;

    return;
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
    if (!list) return (uint32_t)0;
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


gLinkedListDataPtr gLinkedListGet(gLinkedList* list, int64_t index) {
    if (!list) return NULL;
    if (gLinkedListIsEmpty(list)) return NULL;

    index = (index < 0) ? (index + (int64_t)gLinkedListSize(list)) : index;
    if (index >= (int64_t)gLinkedListSize(list) || index < 0) return NULL;

    if (index == 0) return list->front->data;
    if (index == (int64_t)(gLinkedListSize(list) - 1)) return list->rear->data;

    gLinkedListNode* auxNode = list->front;
    while ((index--) > 0) {
        auxNode = auxNode->next;
    }

    return auxNode->data;

}


gLinkedListDataPtr gLinkedListPop(gLinkedList* list, int64_t index) {
    if (!list) return NULL;
    if (gLinkedListIsEmpty(list)) return NULL;
    
    index = (index < 0) ? (index + (int64_t)gLinkedListSize(list)) : index;
    if (index >= (int64_t)gLinkedListSize(list) || index < 0) return NULL;

    (list->counter)--;

    gLinkedListNode *auxNode = list->front, *previous = NULL;

    if (index == 0) {
        gLinkedListDataPtr returnData = auxNode->data;
        list->front = list->front->next;
        free(auxNode) ; auxNode = NULL;
        
        return returnData;
    }

    while ((index--) > 0) {
        previous = auxNode;
        auxNode = auxNode->next;
    }

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
