#include "genCLList.h"

gCLList* clInit(impressFunctionCLList printCLL, compareFunctionCLList compareCLL) {
    gCLList* newCLList = (gCLList *) malloc (sizeof(gCLList));
    if (newCLList == NULL) {
        fprintf(stderr, "Error: Failed while trying to allocate memory for a new Circular Linked List.\n");
        exit(EXIT_FAILURE);
        return NULL;
    }

    newCLList->printCLL = printCLL;
    newCLList->compareCLL = compareCLL;
    newCLList->count = (size_t)0;
    newCLList->currentNode = NULL;

    return newCLList;
}


bool clIsEmpty(gCLList* cll) {
    if (!cll) return 1;
    return (cll->count <= (size_t)0);
}


void* clGetCurrent(gCLList* cll) {
    if (!cll) return NULL;
    if (clIsEmpty(cll)) return NULL;

    return cll->currentNode->data;
}


void clInsert(gCLList* cll, void* data) {
    if (!cll) return;

    gNodeCLList* newnode = (gNodeCLList *) malloc (sizeof(gNodeCLList));
    if (newnode == NULL) {
        fprintf(stderr, "Error: Unable to allocate memory to a new Circular Linked List node.\n");
        exit(EXIT_FAILURE);
        return;
    }
    // Assigning the information to the new node:
    newnode->data = data;

    // If the Circular List is Empty:
    if (clIsEmpty(cll)) {
        // The single node in the circular list points exclusively to itself:
        newnode->next = newnode->previous = newnode;
        cll->currentNode = newnode;

        // Incrementing the circular list counter:
        (cll->count)++;

        return;
    }


    // If the Circular List has just one element:
    if (cll->count == 1) {
        cll->currentNode->next = cll->currentNode->previous = newnode;
        newnode->next = newnode->previous = cll->currentNode;
        // Incrementing the circular list counter:
        (cll->count)++;

        return;
    }

    // Circular List has more than 1 element, inserting the new element after the current node:
    cll->currentNode->next->previous = newnode;
    newnode->next = cll->currentNode->next;

    cll->currentNode->next = newnode;
    newnode->previous = cll->currentNode;
    // Incrementing the circular list counter:
    (cll->count)++;

    return;
}


void* clDeleteCurrent(gCLList* cll) {
    if (!cll) return NULL;
    if (clIsEmpty(cll)) return NULL;

    void* returnData = cll->currentNode->data;
    // If Circular List has just one element:
    if (cll->count == 1) {
        free(cll->currentNode); cll->currentNode = NULL;
        (cll->count)--;

        return returnData;
    }

    // If Circular List has more than 1 element:
    cll->currentNode->previous->next = cll->currentNode->next;
    cll->currentNode->next->previous = cll->currentNode->previous;

    gNodeCLList* nodeAux = cll->currentNode;
    cll->currentNode = cll->currentNode->next;

    free(nodeAux) ; nodeAux = NULL;
    (cll->count)--;

    return returnData;
}


void* clDelete(gCLList* cll, void* data) {
    if (!cll) return NULL;
    if (clIsEmpty(cll)) return NULL;

    // Going through the list until we find the element we want to remove:

    // Checking if the searched element is the current node:
    gNodeCLList* nodeAux = cll->currentNode;
    if (cll->compareCLL(nodeAux->data, data) == 0) {
        // Element found in current node:
        return clDeleteCurrent(cll);
    }

    // Searching for the element in the rest of the list:
    nodeAux = nodeAux->next;
    while (nodeAux != cll->currentNode) {
        if (cll->compareCLL(nodeAux->data, data) != 0) {
            // Does not represent the desired element, proceeding to the next iteration:
            nodeAux = nodeAux->next;
            continue;
        }

        // Element found (Circular List is guaranteed to have at least 2 elements in this part of the code):
        nodeAux->previous->next = nodeAux->next;
        nodeAux->next->previous = nodeAux->previous;

        void* returnData = nodeAux->data;
        free(nodeAux); nodeAux = NULL;
        (cll->count)--;

        return returnData;
    }

    // Element not Found:
    return NULL;
}


size_t clCount(gCLList* cll) {
    if (!cll) return 0;
    return cll->count;
}


void clDestroy(gCLList** cll) {
    if (!cll) return;
    if (!(*cll)) return;
    if (clIsEmpty(*cll)) {
        free(*cll); (*cll) = NULL;
        return;
    }

    // Erase the Current Element Until the List is Empty:
    while (clDeleteCurrent(*cll)) {}
    free(*cll); (*cll) = NULL;
    return;
}


void clNext(gCLList* cll) {
    if (!cll) return;
    if (clIsEmpty(cll)) return;

    cll->currentNode = cll->currentNode->next;
    return;
}


void clPrevious(gCLList* cll) {
    if (!cll) return;
    if (clIsEmpty(cll)) return;

    cll->currentNode = cll->currentNode->previous;
    return;
}


void clImpress(gCLList* cll) {
    if (!cll) return;
    if (clIsEmpty(cll)) {
        printf("[]");
        return;
    }

    gNodeCLList* nodeAux = cll->currentNode;
    printf("[ <- ");
    cll->printCLL(nodeAux->data);
    printf(", ");
    nodeAux = nodeAux->next;

    while (nodeAux != cll->currentNode) {
        cll->printCLL(nodeAux->data);
        printf(", ");
        nodeAux = nodeAux->next;
    }

    printf("\b\b -> ]");
    return;
}


bool clSearch(gCLList* cll, void* data) {
    if (!cll) return 0;
    if (clIsEmpty(cll)) return 0;

    gNodeCLList* nodeAux = cll->currentNode;
    if (cll->compareCLL(nodeAux->data, data) == 0) return 1;
    
    nodeAux = nodeAux->next;
    while (nodeAux != cll->currentNode) {
        if (cll->compareCLL(nodeAux->data, data) == 0) return 1;
        nodeAux = nodeAux->next;
    }

    return 0;
}