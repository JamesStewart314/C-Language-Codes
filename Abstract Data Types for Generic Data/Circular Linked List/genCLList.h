#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef GENERICLINKEDCIRCULARLIST_H
#define GENERICLINKEDCIRCULARLIST_H

typedef void (*impressFunctionCLList)(void* data);
typedef int (*compareFunctionCLList)(void* data1, void* data2);

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


gCLList* clInit(impressFunctionCLList printCLL, compareFunctionCLList compareCLL);      // Initialize the Circular Linked List.
bool clIsEmpty(gCLList* cll);                                                           // Informs whether the circular list is empty.
void* clGetCurrent(gCLList* cll);                                                       // Returns the data of current element of the circular list.
void clInsert(gCLList* cll, void* data);                                                // Inserts a new element after the current element.

void *clDeleteCurrent(gCLList *cll);                                                    //  Remove the current element, the new current becomes the next 
                                                                                        // element after the current one and the function returns the 
                                                                                        // information present in the current node just removed.

void* clDelete(gCLList* cll, void* data);                                               // Remove a specific element, returning its value as a result.
size_t clCount(gCLList* cll);                                                           // Returns the total number of elements in the circular list.
void clDestroy(gCLList** cll);                                                          // Frees memory allocated to the circular linked list.
void clNext(gCLList* cll);                                                              // Changes the current to the next element in the list.
void clPrevious(gCLList* cll);                                                          // Changes the current to the previous element in the list.
void clImpress(gCLList* cll);                                                           // Displays the circular list on the terminal;
bool clSearch(gCLList* cll, void* data);                                                // Checks whether an element is present in the Circular List, returning 1 if it is and 0 otherwise.

#endif

//
// Example of Using the Circular Linked List in a Program:
/*

void impressf(void* data) {
    printf("%d", *((int *)data));
    return;
}


int comparef(void* data1, void* data2) {
    int aux1 = *((int *)data1);
    int aux2 = *((int *)data2);

    if (aux1 > aux2) return 1;
    if (aux1 < aux2) return -1;
    return 0;
}


int main(int argc, char** argv) {
    gCLList *integerList = clInit(impressf, comparef);    // Creating a circular list of integers.
                                                          //  It is worth mentioning that the choice
                                                          // of the integer type was completely arbitrary
                                                          // in this case, it is possible to choose ANY
                                                          // other type or data structure.

    clImpress(integerList); printf("\n");                 // Displaying the empty circular list in the terminal.

    int val1 = 1, val2 = 2, val3 = 3, val4 = 4, val5 = 5; // Creating the values.
    clInsert(integerList, &val1);                         // Inserting the first element.
    clInsert(integerList, &val2);                         // Inserting the second element.
    clInsert(integerList, &val3);                         // Inserting the third element.
    clInsert(integerList, &val4);                         // Inserting the fourth element.
    clInsert(integerList, &val5);                         // Inserting the fifth element.

    clImpress(integerList);                               //  Displaying the result in the terminal.
                                                          // Note that the display of values does not
                                                          // match their insertion order and this is
                                                          // fully consistent with the expected behavior,
                                                          // as each new element is inserted subsequently
                                                          // in relation to the current node and, as the
                                                          // current node was the first value to be inserted,
                                                          // subsequent insertions follow this pattern.
    printf("\n");                                         // New line.

    clDeleteCurrent(integerList);                         // Removing the current node.
    clImpress(integerList); printf("\n");                 // Displaying the circular list in the terminal.
    clNext(integerList);                                  // Moving the current node to the next node in the circular list.
    clNext(integerList);                                  // Moving the current node to the next node in the circular list.
    clImpress(integerList); printf("\n");                 // Displaying the circular list in the terminal.
    clPrevious(integerList);                              // Moving the current node to the previous node in the circular list.
    clImpress(integerList);                               // Displaying the circular list in the terminal.

    clDestroy(&integerList);                              //  Destroying the list. Always remember to perform
                                                          // this step for each circular list created, considering
                                                          // that it is necessary to deallocate the memory before
                                                          // definitively closing the program.
    puts("\nProgram Finished.");

    return 0;
}

*/