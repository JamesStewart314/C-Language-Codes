#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef GENERICSTACK_H
#define GENERICSTACK_H


/* TODO: CREATE THE DEEP COPY FUNCTIONALITY FOR EVERY DATA STRUCTURE. */


/*
  If necessary, it is possible to specify
 the type of pointer used in the data
 structure by modifying the preprocessing
 directive parameter right below:
*/
typedef void* gStPointerData;

typedef void (*impressFunctionGenStack)(gStPointerData data);
typedef int (*compareFunctionGenStack)(gStPointerData data1, gStPointerData data2);
typedef void (*destroyFunctionGenStack)(gStPointerData data);

typedef struct GENERICSTACKNODE {
    gStPointerData data;
    struct GENERICSTACKNODE* next;
} gStackNode;


typedef struct GENERICSTACK {
    gStackNode* top;
    size_t counter;
    impressFunctionGenStack printF;
    compareFunctionGenStack compareF;
    destroyFunctionGenStack destroyF;
} gStack;


gStack* initgStack(impressFunctionGenStack printF, compareFunctionGenStack compareF, destroyFunctionGenStack destroyF); // Initializes the stack;
void gStackDestroy(gStack** stPointer);                                                                                 // Destroys the Stack;
void gStackPush(gStack* st, gStPointerData data);                                                                              // Inserts Elements into the Stack;
void gStackRemove(gStack* st, gStPointerData data);                                                                            // Removes and returns a given element from the stack. If it is not present, the function returns NULL;
void gStackImpress(gStack* st);                                                                                         // Displays the Stack on the Terminal in List Format;
bool gStackIsEmpty(gStack* st);                                                                                         // Checks if the Stack is Empty;
bool gStackSearch(gStack* st, gStPointerData data);                                                                            // Checks whether an element is present in the Stack, returning 1 if it is and 0 otherwise;
size_t gStackSize(gStack* st);                                                                                          // Returns the Number of Elements in the Stack;
gStPointerData gStackPop(gStack* st);                                                                                          // Returns Void Pointers to Elements Removed from the Stack.

#endif

//
// Example of Using the Stack in a Program:
/*

#include "genStack.h"


void impressf(void* data);
int comparef(void* data1, void* data2);

int main(int argc, char** argv) {

    gStack *stackOfIntegers = initgStack(impressf, comparef, NULL);      // Initializing the stack.

    int val1 = 1, val2 = 2, val3 = 3, val4 = 4;                          // Creating Elements of ANY TYPE to stack,
                                                                         // the choice of objects of type int was
                                                                         // completely arbitrary in this case.

    gStackPush(stackOfIntegers, &val1);                                  // Stacking the First element.
    gStackPush(stackOfIntegers, &val2);                                  // Stacking the Second element.
    gStackPush(stackOfIntegers, &val3);                                  // Stacking the Third element.
    gStackPush(stackOfIntegers, &val4);                                  // Stacking the Fourth element.

    puts("Stack Initial State:");
    gStackImpress(stackOfIntegers); printf("\n\n");                      // Displaying the stack in the terminal.

    int* poppedObj = (int *)gStackPop(stackOfIntegers);                  // Removing the element present at the top of the stack.
    if (poppedObj) {
        printf("Popped Object: %i\n", *poppedObj);                       // Displaying the newly removed object.
    }
    gStackImpress(stackOfIntegers); printf("\n");                        // Displaying the stack in the terminal.

    gStackRemove(stackOfIntegers, &val4);                                // Trying to Remove an Object from the Stack.
    gStackRemove(stackOfIntegers, &val2);                                // Trying to Remove an Object from the Stack.

    gStackImpress(stackOfIntegers); printf("\n");                        // Displaying the stack in the terminal.

    puts("\n*Destroying the Stack of Integers.");
    gStackDestroy(&stackOfIntegers);                                     // Don't forget to deallocate the memory present on the stack when closing the program.
    puts("*Stack destroyed successfully!");

    puts("\nEnd of the Program!");

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
