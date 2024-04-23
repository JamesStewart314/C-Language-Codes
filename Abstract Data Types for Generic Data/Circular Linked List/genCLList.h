#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef GENERICLINKEDCIRCULARLIST_H
#define GENERICLINKEDCIRCULARLIST_H

typedef void (*impressFunctionCLList)(void* data);
typedef void (*compareFunctionCLList)(void* data1, void* data2);

typedef struct GENERICNODECLLIST {
    void* data;
    struct GENERICNODECLLIST *previous, *next;
} gNodeCLList;


typedef struct {
    gNodeCLList* currentNode;
    size_t count;
    impressFunctionCLList printCLL;
    compareFunctionCLList compareCLL;
} gCLList;


gCLList* initCLL();                              // Initialize the Circular Linked List.
void* getCLCurrent(gCLList* cll);                // Returns the data of current element of the circular list.
void clInsert(gCLList* cll, void* data);         // Inserts a new element after the current element.
void* lcDeleteCurrent(gCLList *cll);             // Remove the current element, returning its value as a result.
void* clDelete(gCLList* cll, void* data);        // Remove a specific element, returning its value as a result.
size_t clCount(gCLList* cll);                    // Returns the total number of elements in the circular list.
void clDestroy(gCLList** cll);                   // Frees memory allocated to the circular linked list.
bool clIsEmpty(gCLList* cll);                    // Informs whether the circular list is empty.
void clNext(gCLList* cll);                       // Changes the current to the next element in the list.
void clPrevious(gCLList *cll);                   // Changes the current to the previous element in the list.

#endif