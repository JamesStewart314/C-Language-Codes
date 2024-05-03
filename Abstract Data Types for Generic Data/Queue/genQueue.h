#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef GENERICQUEUE_H
#define GENERICQUEUE_H

typedef void (*impressFunctionGenQueue)(void* data);
typedef int (*compareFunctionGenQueue)(void* data1, void* data2);


typedef struct GENERICQUEUENODE {
    void* data;
    struct GENERICQUEUENODE* next;
} gQueueNode;


typedef struct {
  size_t counter;
  gQueueNode *front, *rear;
  impressFunctionGenQueue printF;
  compareFunctionGenQueue compareF;
} gQueue;


gQueue* initgQueue(impressFunctionGenQueue printF, compareFunctionGenQueue compareF); // Initializes the Queue;
bool gQueueIsEmpty(gQueue* q);                                                        // Checks if the Queue is Empty;
void gQueueEnqueue(gQueue* q, void* data);                                            // Inserts Elements into the Queue;
void gQueueImpress(gQueue* q);                                                        // Displays the Queue on the Terminal in List Format;
void gQueueDestroy(gQueue** q);                                                       // Destroys the Queue;
bool gQueueSearch(gQueue* q, void* data);                                             // Checks whether an element is present in the Queue, returning 1 if it is and 0 otherwise;
void* gQueueRemove(gQueue* q, void* data);                                            // Removes and returns a given element from the Queue. If it is not present, the function returns NULL;
void* gQueueDequeue(gQueue* q);                                                       // Returns Void Pointers to Elements Removed from the Queue;
size_t gQueueCount(gQueue* q);                                                        // Returns the Number of Elements in the Queue;
void gQueueClear(gQueue *q);                                                          // Removes all elements contained in the queue.

#endif

//
// Example of Using the Queue in a Program:
/*

#include "genQueue.h"


int comparef(void* data1, void* data2);
void impressf(void* data);

int main(int argc, char** argv) {

    gQueue* queueOfIntegers = initgQueue(impressf, comparef);           // Creating the Queue.

    int val1 = 1, val2 = 2, val3 = 3;                                   // Creating Elements of ANY TYPE to enqueue,
                                                                        // the choice of objects of type int was
                                                                        // completely arbitrary in this case.

    puts("Inserting elements into the queue:");
    gQueueEnqueue(queueOfIntegers, &val1);                              // Inserting the first element in the Queue.
    gQueueImpress(queueOfIntegers); printf("\n");                       // Displays the queue in the terminal.

    gQueueEnqueue(queueOfIntegers, &val2);                              // Inserting the second element in the Queue.
    gQueueImpress(queueOfIntegers); printf("\n");                       // Displays the queue in the terminal.

    gQueueEnqueue(queueOfIntegers, &val3);                              // Inserting the second element in the Queue.
    gQueueImpress(queueOfIntegers); printf("\n");                       // Showing the final Result.

    puts("\n*Removing 2 from the queue");
    gQueueRemove(queueOfIntegers, &val2);                               // Removing Val2 from the Queue.
    gQueueImpress(queueOfIntegers); printf("\n");                       // Displays the queue in the terminal.

    int* dedequeued_value = (int *)gQueueDequeue(queueOfIntegers);      // Getting an element from the queue. 
                                                                        // If the queue is empty, a pointer to 
                                                                        // NULL will be returned.
    if (dedequeued_value) {
        printf("\nDequeued value: %i\n", *dedequeued_value);
    }

    gQueueImpress(queueOfIntegers); printf("\n\n");                     // Displays the queue in the terminal.
    gQueueRemove(queueOfIntegers, &val2);                               // TRYING to remove Val2 - which is no longer present - from the queue.
    
    puts("Replacing removed elements:");
    gQueueEnqueue(queueOfIntegers, &val2);
    gQueueEnqueue(queueOfIntegers, &val1);
    gQueueImpress(queueOfIntegers); printf("\n\n");
    puts("After clearing all queue elements:");
    gQueueClear(queueOfIntegers);                                       // Removing all elements contained in the queue.
    gQueueImpress(queueOfIntegers); printf("\n");


    gQueueDestroy(&queueOfIntegers);                                    // Cleaning the Queue before exiting.
    gQueueImpress(queueOfIntegers); printf("\n");                       // TRYING to Display the released queue in the terminal.

    puts("Program Finished!");

    return 0;
}


int comparef(void* data1, void* data2) {
    int aux1 = *((int *)data1);
    int aux2 = *((int *)data2);

    if (aux1 > aux2) return 1;
    if (aux1 < aux2) return -1;
    return 0;
}


void impressf(void* data) {
    int* aux = (int *)data;
    printf("%d", *aux);
    return;
}

*/