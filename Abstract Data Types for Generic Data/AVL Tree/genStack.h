#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef GENSTACK_H
#define GENSTACK_H

typedef void (*impressFunctionStack)(void* data);
typedef int (*compareFunctionStack)(void* data1, void* data2);

typedef struct GENERICNODESTACK {
    void* data;
    struct GENERICNODESTACK* next;
} gNodeStack;


typedef struct GENERICSTACK {
    gNodeStack* top;
    size_t counter;
    impressFunctionStack printSt;
    compareFunctionStack compareSt;
} gStack;


gStack* stInit(impressFunctionStack printSt, compareFunctionStack compareSt);        // Initializes the stack;
bool stIsEmpty(gStack* st);                                                          // Checks if the Stack is Empty;
void stDestroy(gStack** st);                                                         // Destroys the Stack;
void stPush(gStack* st, void* data);                                                 // Inserts Elements into the Stack;
void* stPop(gStack* st);                                                             // Returns Void Pointers to Elements Removed from the Stack.
void* stRemove(gStack* st, void* data);                                              // Removes and returns a given element from the stack. If it is not present, the function returns NULL;
size_t stCount(gStack* st);                                                          // Returns the Number of Elements in the Stack;
void stImpress(gStack* st);                                                          // Displays the Stack on the Terminal in List Format;
bool stSearch(gStack *st, void *data);                                               // Checks whether an element is present in the Stack, returning 1 if it is and 0 otherwise.

#endif

//
// Example of Using the Stack in a Program:
/*

void impressf(void* data) {
    printf("%i", *((int *)data));
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

    gStack *integerStack = stInit(impressf, comparef);    // Initializing the stack.

    int val1 = 1, val2 = 2, val3 = 3, val4 = 4;           // Creating Elements of ANY TYPE to stack,
                                                          // the choice of objects of type int was
                                                          // completely arbitrary in this case.

    stPush(integerStack, &val1);                          // Stacking the First element.
    stPush(integerStack, &val2);                          // Stacking the Second element.
    stPush(integerStack, &val3);                          // Stacking the Third element.
    stPush(integerStack, &val4);                          // Stacking the Fourth element.

    puts("Stack Initial State:");
    stImpress(integerStack);                              // Displaying the stack in the terminal.

    int* poppedObj = (int *)stPop(integerStack);          // Removing the element present at the top of the stack.
    printf("\n\nPopped Object: %i\n", *poppedObj);        // Displaying the newly removed object.
    stImpress(integerStack);                              // Displaying the stack in the terminal.

    void* removedObj = stRemove(integerStack, &val4);     // Trying to Remove an Object from the Stack.

    int* removedObjConverted;
    if(removedObj) {                                      // Checking if the Removed Value is not NULL.
        removedObjConverted = (int *)removedObj;          // Pointer Casting to Correct Type.
        printf("\nRemoved Object: %i\n", *removedObjConverted);
    } else { printf("\n"); }

    removedObj = stRemove(integerStack, &val2);

    if(removedObj) {                                       // Checking if the Removed Value is not NULL.
        removedObjConverted = (int *)removedObj;           // Pointer Casting to Correct Type.
        printf("\nRemoved Object: %i\n", *removedObjConverted);
    } else { printf("\n"); }

    stImpress(integerStack);                               // Displaying the stack in the terminal.

    stDestroy(&integerStack);                              // Don't forget to deallocate the memory present on the stack when closing the program.

    return 0;
}

*/
