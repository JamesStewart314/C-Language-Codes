#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef GENERICCIRCULARLINKEDLIST_H
#define GENERICCIRCULARLINKEDLIST_H


/* TODO: CREATE THE DEEP COPY FUNCTIONALITY FOR EVERY DATA STRUCTURE. */


/*
  If necessary, it is possible to specify
 the type of pointer used in the data
 structure by modifying the preprocessing
 directive parameter right below:
*/
typedef void* gCLLPointerData;

typedef void (*impressFunctionGenCLList)(gCLLPointerData data);
typedef int (*compareFunctionGenCLList)(gCLLPointerData data1, gCLLPointerData data2);
typedef void (*destroyFunctionGenCLList)(gCLLPointerData data);

typedef struct GENERICCLLISTNODE {
    gCLLPointerData data;
    struct GENERICCLLISTNODE *previous, *next;
} gCLListNode;

typedef struct {
    gCLListNode* currentNode;
    size_t counter;
    impressFunctionGenCLList printF;
    compareFunctionGenCLList compareF;
    destroyFunctionGenCLList destroyF;
} gCLList;


gCLList* initgCLList(impressFunctionGenCLList printF, compareFunctionGenCLList compareF, destroyFunctionGenCLList destroyF); // Initialize the Circular Linked List;
void gCLLInsert(gCLList* cll, gCLLPointerData data);                                                                         // Inserts a new element after the current node;

void gCLLRemoveCurrent(gCLList* cll);                                                                                        //  Remove the current element, the new current becomes the next 
                                                                                                                             // element after the current one and the function returns the 
                                                                                                                             // information present in the current node just removed;

void gCLLRemove(gCLList* cll, gCLLPointerData data);                                                                         // Remove a specific element, returning its value as a result;
void gCLLDestroy(gCLList** cllPointer);                                                                                      // Frees memory allocated to the circular linked list;
void gCLLNext(gCLList* cll);                                                                                                 // Changes the current to the next element in the list;
void gCLLPrevious(gCLList* cll);                                                                                             // Changes the current to the previous element in the list;
void gCLLImpress(gCLList* cll);                                                                                              // Displays the circular list on the terminal;
void gCLLClear(gCLList* cll);                                                                                                // Erase all elements in the circular list;
bool gCLLSearch(gCLList* cll, gCLLPointerData data);                                                                         // Checks whether an element is present in the circular list, returning 1 if it is and 0 otherwise;
bool gCLLIsEmpty(gCLList* cll);                                                                                              // Informs whether the circular list is empty;
size_t gCLLSize(gCLList* cll);                                                                                               // Returns the number of elements in the circular list;
gCLLPointerData gCLLGetCurrent(gCLList* cll);                                                                                // Returns the data of current element of the circular list;
gCLLPointerData gCLLGetBiggest(gCLList* cll);                                                                                // Return a pointer to the biggest element in the circular list;
gCLLPointerData gCLLGetSmallest(gCLList* cll);                                                                               // Return a pointer to the smallest element in the circular list.

#endif


//
// Example of Using the Circular Linked List in a Program:
/*

#include "genCLList.h"

void impressf(void* data);
int comparef(void* data1, void* data2);

int main(int argc, char** argv) {

    gCLList *circularLinkedListOfIntegers = initgCLList(impressf, comparef, NULL); // Creating a circular list of integers.
                                                                                   //  It is worth mentioning that the choice
                                                                                   // of the integer type was completely arbitrary
                                                                                   // in this case, it is possible to choose ANY
                                                                                   // other type or data structure.

    gCLLImpress(circularLinkedListOfIntegers); printf("\n");                       // Displaying the empty circular list in the terminal.

    int val1 = 1, val2 = 2, val3 = 3, val4 = 4, val5 = 5;                          // Creating the values.
    gCLLInsert(circularLinkedListOfIntegers, &val1);                               // Inserting the first element.
    gCLLInsert(circularLinkedListOfIntegers, &val2);                               // Inserting the second element.
    gCLLInsert(circularLinkedListOfIntegers, &val3);                               // Inserting the third element.
    gCLLInsert(circularLinkedListOfIntegers, &val4);                               // Inserting the fourth element.
    gCLLInsert(circularLinkedListOfIntegers, &val5);                               // Inserting the fifth element.

    gCLLImpress(circularLinkedListOfIntegers);                                     //  Displaying the result in the terminal.
                                                                                   // Note that the display of values does not
                                                                                   // match their insertion order and this is
                                                                                   // fully consistent with the expected behavior,
                                                                                   // as each new element is inserted subsequently
                                                                                   // in relation to the current node and, as the
                                                                                   // current node was the first value to be inserted,
                                                                                   // subsequent insertions follow this pattern.

    printf("\n");                                                                  // New line.

    gCLLRemoveCurrent(circularLinkedListOfIntegers);                               // Removing the current node.
    gCLLImpress(circularLinkedListOfIntegers); printf("\n");                       // Displaying the circular list in the terminal.
    gCLLRemove(circularLinkedListOfIntegers, &val5);                               // Removing 5 from the circular list.
    gCLLImpress(circularLinkedListOfIntegers); printf("\n");                       // Displaying the circular list in the terminal.
    gCLLNext(circularLinkedListOfIntegers);                                        // Moving the current node to the next node in the circular list.
    gCLLImpress(circularLinkedListOfIntegers); printf("\n");                       // Displaying the circular list in the terminal.
    gCLLPrevious(circularLinkedListOfIntegers);                                    // Moving the current node to the previous node in the circular list.
    gCLLImpress(circularLinkedListOfIntegers);                                     // Displaying the circular list in the terminal.

    gCLLDestroy(&circularLinkedListOfIntegers);                                    //  Destroying the list. Always remember to perform
                                                                                   // this step for each circular list created, considering
                                                                                   // that it is necessary to deallocate the memory before
                                                                                   // definitively closing the program.
    puts("\nProgram Finished.");

    return 0;
}


void impressf(void* data) {
    int* aux = (int *)data;
    if (aux != NULL) { printf("%d", *aux); } else { printf("NULL"); }
    return;
}


int comparef(void* data1, void* data2) {
    int aux1 = *((int *)data1);
    int aux2 = *((int *)data2);

    if (!aux1 || !aux2) {
        if (!aux1 && !aux2) return 1;
        return 0;
    }

    if (aux1 > aux2) return 1;
    if (aux1 < aux2) return -1;
    return 0;
}

*/