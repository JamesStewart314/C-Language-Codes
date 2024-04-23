#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef GENERICQUEUE_H
#define GENERICQUEUE_H

typedef void (*impressFunctionQueue)(void* data);
typedef int (*compareFunctionQueue)(void* data1, void* data2);


typedef struct GENERICNODEQUEUE {
    void* data;
    struct GENERICNODEQUEUE *next;
} gNodeQueue;


typedef struct {
  size_t counter;

  gNodeQueue* front;
  gNodeQueue* rear;

  impressFunctionQueue printQ;
  compareFunctionQueue compareQ;
} gQueue;

gQueue *initQueue(impressFunctionQueue printQ, compareFunctionQueue compareQ); // Initializes the Queue;
bool queueIsEmpty(gQueue* q);                                                  // Checks if the Queue is Empty;
void enqueue(gQueue *q, void *data);                                           // Inserts Elements into the Queue;
void impressQueue(gQueue *q);                                                  // Displays the Queue on the Terminal in List Format;
void freeQueue(gQueue** q);                                                    // Destroys the Queue;
bool searchInQueue(gQueue *q, void *data);                                     // Checks whether an element is present in the Queue, returning 1 if it is and 0 otherwise;
void *removeFromQueue(gQueue *q, void *data);                                  // Removes and returns a given element from the Queue. If it is not present, the function returns NULL;
void *dequeue(gQueue *q);                                                      // Returns Void Pointers to Elements Removed from the Queue;
size_t queueCount(gQueue *q);                                                  // Returns the Number of Elements in the Queue.

#endif

//
// Example of Using the Queue in a Program:
/*

int compareFunQ(void* data1, void* data2) {
    int aux1 = *((int *)data1);
    int aux2 = *((int *)data2);

    if (aux1 > aux2) return 1;
    if (aux1 < aux2) return -1;
    return 0;
}

void impressFunQueue(void* data) {
    int* aux = (int *)data;
    printf("%d", *aux);
    return;
}

int main(void) {

    gQueue* integerQueue = initQueue(impressFunQueue, compareFunQ); // Creating the Queue.

    int val1 = 1, val2 = 2, val3 = 3;     // Creating Elements of ANY TYPE to enqueue,
                                          // the choice of objects of type int was
                                          // completely arbitrary in this case.

    enqueue(integerQueue, &val1);         // Inserting the first element in the Queue.
    impressQueue(integerQueue);           // Displays the queue in the terminal.

    enqueue(integerQueue, &val2);         // Inserting the second element in the Queue.
    impressQueue(integerQueue);           // Displays the queue in the terminal.

    enqueue(integerQueue, &val3);         // Inserting the second element in the Queue.
    impressQueue(integerQueue);           // Displays the queue in the terminal.

    impressQueue(integerQueue);           // Showing the final Result.

    removeFromQueue(integerQueue, &val2); // Removing Val2 from the Queue.
    impressQueue(integerQueue);           // Displays the queue in the terminal.

    int* dedequeued_value = (int *)dequeue(integerQueue);
    printf("dequeued value: %i\n", *dedequeued_value);

    impressQueue(integerQueue);           // Displays the queue in the terminal.
    removeFromQueue(integerQueue, &val2); // TRYING to remove Val2 - which is no longer present - from the queue.
    impressQueue(integerQueue);           // Displays the queue in the terminal.
    removeFromQueue(integerQueue, &val3); // Removing Val3 from the Queue.
    impressQueue(integerQueue);           // Displays the empty queue in the terminal.

    freeQueue(&integerQueue);             // Cleaning the Queue before exiting.
    impressQueue(integerQueue);           // TRYING to Display the released queue in the terminal.

    puts("Program Finished.");

    return 0;
}

*/