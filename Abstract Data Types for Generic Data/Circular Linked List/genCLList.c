#include "genCLList.h"

gCLList* initgCLList(impressFunctionGenCLList printF, compareFunctionGenCLList compareF) {

    if (!printF || !compareF) {
        fprintf(stderr, "Error: At least one of the provided functions is NULL when creating a new generic Circular Linked List.\n");
        return NULL;
    }

    gCLList* newCLList = (gCLList *) malloc (sizeof(gCLList));
    if (newCLList == NULL) {
        fprintf(stderr, "Error: Failed while trying to allocate memory for a new generic Circular Linked List.\n");
        exit(EXIT_FAILURE);
        return NULL;
    }

    newCLList->printF = printF;
    newCLList->compareF = compareF;
    newCLList->counter = (size_t)0;
    newCLList->currentNode = NULL;

    return newCLList;
}


bool gCLLIsEmpty(gCLList* cll) {
    if (!cll) return 1;
    return (cll->counter <= (size_t)0);
}


void* gCLLGetCurrent(gCLList* cll) {
    if (!cll) return NULL;
    if (gCLLIsEmpty(cll)) return NULL;

    return cll->currentNode->data;
}


void gCLLInsert(gCLList* cll, void* data) {
    if (!cll) return;

    gCLListNode* newnode = (gCLListNode *) malloc (sizeof(gCLListNode));
    if (newnode == NULL) {
        fprintf(stderr, "Error: Unable to allocate memory to a new generic Circular Linked List node.\n");
        exit(EXIT_FAILURE);
        return;
    }
    // Assigning the information to the new node:
    newnode->data = data;

    // If the Circular List is Empty:
    if (gCLLIsEmpty(cll)) {
        // The single node in the circular list points exclusively to itself:
        newnode->next = newnode->previous = newnode;
        cll->currentNode = newnode;

        // Incrementing the circular list counter:
        (cll->counter)++;

        return;
    }


    // If the Circular List has just one element:
    if (cll->counter == 1) {
        cll->currentNode->next = cll->currentNode->previous = newnode;
        newnode->next = newnode->previous = cll->currentNode;
        // Incrementing the circular list counter:
        (cll->counter)++;

        return;
    }

    // Circular List has more than 1 element, inserting the new element after the current node:
    cll->currentNode->next->previous = newnode;
    newnode->next = cll->currentNode->next;

    cll->currentNode->next = newnode;
    newnode->previous = cll->currentNode;
    // Incrementing the circular list counter:
    (cll->counter)++;

    return;
}


void* gCLLRemoveCurrent(gCLList* cll) {
    if (!cll) return NULL;
    if (gCLLIsEmpty(cll)) return NULL;

    void* returnData = cll->currentNode->data;
    // If Circular List has just one element:
    if (cll->counter == 1) {
        free(cll->currentNode); cll->currentNode = NULL;
        (cll->counter)--;

        return returnData;
    }

    // If Circular List has more than 1 element:
    cll->currentNode->previous->next = cll->currentNode->next;
    cll->currentNode->next->previous = cll->currentNode->previous;

    gCLListNode* auxNode = cll->currentNode;
    cll->currentNode = cll->currentNode->next;

    free(auxNode) ; auxNode = NULL;
    (cll->counter)--;

    return returnData;
}


void* gCLLRemove(gCLList* cll, void* data) {
    if (!cll) return NULL;
    if (gCLLIsEmpty(cll)) return NULL;

    // Going through the list until we find the element we want to remove:

    // Checking if the searched element is the current node:
    gCLListNode* auxNode = cll->currentNode;
    if (cll->compareF(auxNode->data, data) == 0) {
        // Element found in current node:
        return gCLLRemoveCurrent(cll);
    }

    // Searching for the element in the rest of the list:
    auxNode = auxNode->next;
    while (auxNode != cll->currentNode) {
        if (cll->compareF(auxNode->data, data) != 0) {
            // Does not represent the desired element, proceeding to the next iteration:
            auxNode = auxNode->next;
            continue;
        }

        // Element found (Circular List is guaranteed to have at least 2 elements in this part of the code):
        auxNode->previous->next = auxNode->next;
        auxNode->next->previous = auxNode->previous;

        void* returnData = auxNode->data;
        free(auxNode); auxNode = NULL;
        (cll->counter)--;

        return returnData;
    }

    // Element not Found:
    return NULL;
}


size_t gCLLCount(gCLList* cll) {
    if (!cll) return 0;
    return cll->counter;
}


void gCLLDestroy(gCLList** cll) {
    if (!cll) return;
    if (!(*cll)) return;
    if (gCLLIsEmpty(*cll)) {
        free(*cll); (*cll) = NULL;
        return;
    }

    // Erase the Current Element Until the List is Empty:
    while (gCLLRemoveCurrent(*cll)) {}
    free(*cll); (*cll) = NULL;
    return;
}


void gCLLNext(gCLList* cll) {
    if (!cll) return;
    if (gCLLIsEmpty(cll)) return;

    cll->currentNode = cll->currentNode->next;
    return;
}


void gCLLPrevious(gCLList* cll) {
    if (!cll) return;
    if (gCLLIsEmpty(cll)) return;

    cll->currentNode = cll->currentNode->previous;
    return;
}


void gCLLImpress(gCLList* cll) {
    if (!cll) return;
    if (gCLLIsEmpty(cll)) { printf("()"); return; }

    gCLListNode* auxNode = cll->currentNode;
    printf("( <- ");
    cll->printF(auxNode->data);
    printf(", ");
    auxNode = auxNode->next;

    while (auxNode != cll->currentNode) {
        cll->printF(auxNode->data);
        printf(", ");
        auxNode = auxNode->next;
    }

    printf("\b\b -> )");
    return;
}


bool gCLLSearch(gCLList* cll, void* data) {
    if (!cll) return 0;
    if (gCLLIsEmpty(cll)) return 0;

    gCLListNode* auxNode = cll->currentNode;
    if (cll->compareF(auxNode->data, data) == 0) return 1;
    
    auxNode = auxNode->next;
    while (auxNode != cll->currentNode) {
        if (cll->compareF(auxNode->data, data) == 0) return 1;
        auxNode = auxNode->next;
    }

    return 0;
}


void gCLLClear(gCLList* cll) {
    if (!cll) return;

    while (gCLLRemoveCurrent(cll)) {}
    return;
}


void* gCLLGetBiggest(gCLList* cll) {
    if (!cll) return NULL;
    if (gCLLIsEmpty(cll)) return NULL;

    // Going through the list until we find the biggest element:
    void* returnData = cll->currentNode->data;
    gCLListNode* auxNode = cll->currentNode->next;
    while (auxNode != cll->currentNode) {
        if (cll->compareF(auxNode->data, returnData) > 0) {
            returnData = auxNode->data;
        }
        auxNode = auxNode->next;
    }

    return returnData;
}


void* gCLLGetSmallest(gCLList* cll) {
    if (!cll) return NULL;
    if (gCLLIsEmpty(cll)) return NULL;

    // Going through the list until we find the smallest element:
    void* returnData = cll->currentNode->data;
    gCLListNode* auxNode = cll->currentNode->next;
    while (auxNode != cll->currentNode) {
        if (cll->compareF(auxNode->data, returnData) < 0) {
            returnData = auxNode->data;
        }
        auxNode = auxNode->next;
    }

    return returnData;
}