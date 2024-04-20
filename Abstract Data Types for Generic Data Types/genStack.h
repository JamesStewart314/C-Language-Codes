#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef GENSTACK_H
#define GENSTACK_H

typedef void (*impressFunctionStack)(void* data);

typedef struct GENERICNODESTACK {
    void* data;
    struct GENERICNODESTACK* next;
} gNodeStack;


typedef struct GENERICSTACK {
    gNodeStack* top;
    size_t counter;
    impressFunctionStack ifunc;
} gStack;


gStack* stInit(impressFunctionStack ifunc);          // Initializes the stack;
void stDestroy(gStack **st);                         // Destroys the Stack;
bool stIsEmpty(gStack *st);                          // Checks if the Stack is Empty;
void stPush(gStack *st, void* data);                 // Inserts Elements into the Stack;
void* stPop(gStack *st);                             // Returns Void Pointers to Elements Removed from the Stack.
size_t stCount(gStack *st);                          // Returns the Number of Elements in the Stack;
void impressStack(gStack *st);                       // Displays the Stack on the Terminal in List Format.

#endif

//
// Example of Using the Stack in a Program:
//
/*

void impressf(void *data) {
    printf("%i", *((int *)data));
    return;
}

int main(void) {

    gStack *integerStack = stInit(impressf); // Initializing the stack.

    int val1 = 2, val2 = 3, val3 = 1;                     // Creating Elements of ANY TYPE to stack,
                                                          // the choice of objects of type int was
                                                          // completely arbitrary in this case.

    stPush(integerStack, &val1);                          // Stacking the First element.
    stPush(integerStack, &val2);                          // Stacking the Second element.
    stPush(integerStack, &val3);                          // Stacking the Third element.
    impressStack(integerStack);                           // Displaying the stack in the terminal.
    int* removedObj = (int *)stPop(integerStack);         // Removing the element present at the top of the stack.
    printf("\nRemoved Object: %i\n", *removedObj);        // Displaying the newly removed object.
    impressStack(integerStack);                           // Displaying the stack in the terminal.

    stDestroy(&integerStack);                             // Don't forget to deallocate the memory present on the stack when closing the program.

    return 0;
}

*/
