#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef GENERICLINKEDLIST_H
#define GENERICLINKEDLIST_H

#include "genLinkedList.h"

typedef void (*impressFunctionGenLinkedList)(void* data);
typedef int (*compareFunctionGenLinkedList)(void* data1, void* data2);

typedef struct GENERICLINKEDLISTNODE {
    void* data;
    struct GENERICLINKEDLISTNODE* next;
} gLinkedListNode;


typedef struct {
    gLinkedListNode *front, *rear;
    size_t counter;
    impressFunctionGenLinkedList printF;
    compareFunctionGenLinkedList compareF;
} gLinkedList;


gLinkedList* initgLinkedList(impressFunctionGenLinkedList printF, compareFunctionGenLinkedList compareF);  // Initializes a generic linked list and returns a pointer to it. The function takes pointers to print and compare functions as parameters;
void gLinkedListDestroy(gLinkedList** list);                                                               // Destroys the generic linked list, freeing all allocated memory for it. Receives a pointer to the pointer of the list as a parameter;
bool gLinkedListIsEmpty(gLinkedList* list);                                                                // Checks if the generic linked list is empty;
void gLinkedListAppend(gLinkedList* list, void* data);                                                     // Appends a new node containing the provided data to the end of the linked list;
void* gLinkedListRemove(gLinkedList* list, void* data);                                                    // Removes the first node containing the provided data from the linked list and returns it;
bool gLinkedListSearch(gLinkedList* list, void* data);                                                     // Searches for a node containing the provided data in the linked list. Returns true if found, false otherwise;
size_t gLinkedListCount(gLinkedList* list);                                                                // Counts the number of nodes in the linked list;
void gLinkedListClear(gLinkedList* list);                                                                  // Clears the linked list, removing all nodes and freeing allocated memory;
void* gLinkedListPop(gLinkedList* list, long int index);                                                   // Removes and returns the node at the specified index position in the linked list;
void *gLinkedListGetBiggest(gLinkedList *list);                                                            // Returns a pointer containing the largest value in the linked list;
void* gLinkedListGetSmallest(gLinkedList* list);                                                           // Returns a pointer containing the smallest value in the linked list;
void gLinkedListImpress(gLinkedList* list);                                                                // Prints the data stored in each node of the linked list.

#endif


//
// Example of Using the Linked List in a Program:
/*

#include "genLinkedList.h"

void impressf(void* data);
int comparef(void* data1, void* data2);

int main(int argc, char** argv) {
    puts("*Creating a Linked List of Integer Values.");
    gLinkedList* linkedListOfIntegers = initgLinkedList(impressf, comparef);
    printf("List Created: "); gLinkedListImpress(linkedListOfIntegers); printf("\n");

    int val1 = 1, val2 = 2, val3 = 3, val4 = 4, val5 = 5;
    int antiVal1 = (-1), antiVal2 = (-2), antiVal3 = (-3);

    gLinkedListAppend(linkedListOfIntegers, &val1);
    gLinkedListAppend(linkedListOfIntegers, &val2);
    gLinkedListAppend(linkedListOfIntegers, &val3);
    gLinkedListAppend(linkedListOfIntegers, &val4);
    gLinkedListAppend(linkedListOfIntegers, &val5);
    gLinkedListAppend(linkedListOfIntegers, &antiVal1);
    gLinkedListAppend(linkedListOfIntegers, &antiVal2);
    gLinkedListAppend(linkedListOfIntegers, &antiVal3);

    puts("\nInserted Elements:");
    gLinkedListImpress(linkedListOfIntegers); printf("\n");

    puts("\nRemoving 5 from the list:");
    gLinkedListRemove(linkedListOfIntegers, &val5);
    gLinkedListImpress(linkedListOfIntegers); printf("\n");

    puts("\nRemoving 1 from the list:");
    gLinkedListRemove(linkedListOfIntegers, &val1);
    gLinkedListImpress(linkedListOfIntegers); printf("\n");

    puts("\nRemoving -3 from the list:");
    gLinkedListRemove(linkedListOfIntegers, &antiVal3);
    gLinkedListImpress(linkedListOfIntegers); printf("\n");


    puts("\nPopping the value in index 2:");
    int* poppingResult = (int *)gLinkedListPop(linkedListOfIntegers, 2);
    if (poppingResult) {
        printf("Value Popped: %d\n", *poppingResult);
    }
    gLinkedListImpress(linkedListOfIntegers); printf("\n");


    puts("\nPopping the value in index -1 (last element):");
    poppingResult = (int *)gLinkedListPop(linkedListOfIntegers, -1);
    if (poppingResult) {
        printf("Value Popped: %d\n", *poppingResult);
    }
    gLinkedListImpress(linkedListOfIntegers); printf("\n");


    puts("\nPopping the value in index 29 (Exceeds the maximum list index):");
    poppingResult = (int *)gLinkedListPop(linkedListOfIntegers, 29);
    if (poppingResult) {
        printf("Value Popped: %d\n", *poppingResult);
    } else { printf("No value obtained...\n"); }
    gLinkedListImpress(linkedListOfIntegers); printf("\n");


    puts("\nPopping the value in index -10 (Exceeds the minimum list index):");
    poppingResult = (int *)gLinkedListPop(linkedListOfIntegers, -10);
    if (poppingResult) {
        printf("Value Popped: %d\n", *poppingResult);
    } else { printf("No value obtained...\n"); }
    gLinkedListImpress(linkedListOfIntegers); printf("\n");


    puts("\nTesting Search and Max/Min Functions: ");
    printf("=> Is the value (-1) in the list?: %s\n", gLinkedListSearch(linkedListOfIntegers, &antiVal1) ? "Yes" : "No");
    printf("=> Is the value 5 in the list?: %s\n", gLinkedListSearch(linkedListOfIntegers, &val5) ? "Yes" : "No");

    int* returnValue = gLinkedListGetBiggest(linkedListOfIntegers);
    if (returnValue) {
        printf("=> Current Biggest Value on the List: %d\n", *returnValue);
    }

    returnValue = gLinkedListGetSmallest(linkedListOfIntegers);
    if (returnValue) {
        printf("=> Current Smallest Value on the List: %d\n", *returnValue);
    }

    puts("\nFinal State of the List:");
    gLinkedListImpress(linkedListOfIntegers); printf("\n");

    
    puts("\n*Destroying the Linked List!");
    gLinkedListDestroy(&linkedListOfIntegers);
    printf("Linked List Destroyed: "); gLinkedListImpress(linkedListOfIntegers); printf("\n");


    puts("\nProgram Finished!");

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