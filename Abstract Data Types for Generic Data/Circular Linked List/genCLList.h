#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef GENERICCIRCULARLINKEDLIST_H
#define GENERICCIRCULARLINKEDLIST_H

typedef void (*impressFunctionGenCLList)(void* data);
typedef int (*compareFunctionGenCLList)(void* data1, void* data2);

typedef struct GENERICCLLISTNODE {
    void* data;
    struct GENERICCLLISTNODE *previous, *next;
} gCLListNode;


typedef struct {
    gCLListNode* currentNode;
    size_t counter;
    impressFunctionGenCLList printF;
    compareFunctionGenCLList compareF;
} gCLList;


gCLList* initgCLList(impressFunctionGenCLList printF, compareFunctionGenCLList compareF);    // Initialize the Circular Linked List.
bool gCLLIsEmpty(gCLList* cll);                                                           // Informs whether the circular list is empty.
void* gCLLGetCurrent(gCLList* cll);                                                       // Returns the data of current element of the circular list.
void gCLLInsert(gCLList* cll, void* data);                                                // Inserts a new element after the current element.

void* gCLLDeleteCurrent(gCLList* cll);                                                    //  Remove the current element, the new current becomes the next 
                                                                                        // element after the current one and the function returns the 
                                                                                        // information present in the current node just removed.

void* gCLLRemove(gCLList* cll, void* data);                                               // Remove a specific element, returning its value as a result.
size_t gCLLCount(gCLList* cll);                                                           // Returns the total number of elements in the circular list.
void gCLLDestroy(gCLList** cll);                                                          // Frees memory allocated to the circular linked list.
void gCLLNext(gCLList* cll);                                                              // Changes the current to the next element in the list.
void gCLLPrevious(gCLList* cll);                                                          // Changes the current to the previous element in the list.
void gCLLImpress(gCLList* cll);                                                           // Displays the circular list on the terminal;
bool gCLLSearch(gCLList* cll, void* data);                                                // Checks whether an element is present in the Circular List, returning 1 if it is and 0 otherwise.

#endif


//
// Example of Using the Circular Linked List in a Program:
/*

#include "genCLList.h"

void impressf(void* data);
int comparef(void* data1, void* data2);

int main(int argc, char** argv) {
    gCLList *integerCircularLinkedList = initgCLList(impressf, comparef); // Creating a circular list of integers.
                                                                          //  It is worth mentioning that the choice
                                                                          // of the integer type was completely arbitrary
                                                                          // in this case, it is possible to choose ANY
                                                                          // other type or data structure.

    gCLLImpress(integerCircularLinkedList); printf("\n");                 // Displaying the empty circular list in the terminal.

    int val1 = 1, val2 = 2, val3 = 3, val4 = 4, val5 = 5;                 // Creating the values.
    gCLLInsert(integerCircularLinkedList, &val1);                         // Inserting the first element.
    gCLLInsert(integerCircularLinkedList, &val2);                         // Inserting the second element.
    gCLLInsert(integerCircularLinkedList, &val3);                         // Inserting the third element.
    gCLLInsert(integerCircularLinkedList, &val4);                         // Inserting the fourth element.
    gCLLInsert(integerCircularLinkedList, &val5);                         // Inserting the fifth element.
                                                                          
    gCLLImpress(integerCircularLinkedList);                               //  Displaying the result in the terminal.
                                                                          // Note that the display of values does not
                                                                          // match their insertion order and this is
                                                                          // fully consistent with the expected behavior,
                                                                          // as each new element is inserted subsequently
                                                                          // in relation to the current node and, as the
                                                                          // current node was the first value to be inserted,
                                                                          // subsequent insertions follow this pattern.
    
    printf("\n");                                                         // New line.

    gCLLDeleteCurrent(integerCircularLinkedList);                         // Removing the current node.
    gCLLImpress(integerCircularLinkedList); printf("\n");                 // Displaying the circular list in the terminal.
    gCLLRemove(integerCircularLinkedList, &val5);                         // Removing 5 from the circular list.
    gCLLImpress(integerCircularLinkedList); printf("\n");                 // Displaying the circular list in the terminal.
    gCLLNext(integerCircularLinkedList);                                  // Moving the current node to the next node in the circular list.
    gCLLImpress(integerCircularLinkedList); printf("\n");                 // Displaying the circular list in the terminal.
    gCLLPrevious(integerCircularLinkedList);                              // Moving the current node to the previous node in the circular list.
    gCLLImpress(integerCircularLinkedList);                               // Displaying the circular list in the terminal.

    gCLLDestroy(&integerCircularLinkedList);                              //  Destroying the list. Always remember to perform
                                                                          // this step for each circular list created, considering
                                                                          // that it is necessary to deallocate the memory before
                                                                          // definitively closing the program.
    puts("\nProgram Finished.");

    return 0;
}


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

*/