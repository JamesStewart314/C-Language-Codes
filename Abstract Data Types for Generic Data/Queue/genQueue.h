#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#ifndef GENERICQUEUE_H
#define GENERICQUEUE_H

/*
  If necessary, it is possible to specify
 the type of pointer used in the data
 structure by modifying the preprocessing
 directive parameter right below:
*/
typedef void* gQueueDataPtr;

typedef void (*impressFunctionGenQueue)(gQueueDataPtr data);
typedef int (*compareFunctionGenQueue)(gQueueDataPtr data1, gQueueDataPtr data2);
typedef void (*destroyFunctionGenQueue)(gQueueDataPtr data);
typedef gQueueDataPtr (*deepcopyFunctionGenQueue)(gQueueDataPtr data);


typedef struct GENERICQUEUENODE {
    gQueueDataPtr data;
    struct GENERICQUEUENODE* next;
} gQueueNode;


typedef struct {
    gQueueNode *front, *rear;
    uint32_t counter;
    impressFunctionGenQueue printF;
    compareFunctionGenQueue compareF;
    destroyFunctionGenQueue destroyF;
    deepcopyFunctionGenQueue deepcopyF;
} gQueue;


gQueue* initgQueue(impressFunctionGenQueue printF, compareFunctionGenQueue compareF,
                   destroyFunctionGenQueue destroyF, deepcopyFunctionGenQueue deepcopyF);    // Initializes the queue and returns a pointer to it;

gQueue* gQueueCopy(gQueue* q);                                                               // Creates a deep copy of the given queue and returns a pointer to the new queue;
void gQueueClear(gQueue* q);                                                                 // Removes all elements contained in the given queue;
void gQueueDestroy(gQueue** qPointer);                                                       // Destroys the queue and all elements in it;
void gQueueEnqueue(gQueue* q, gQueueDataPtr data);                                           // Inserts Elements into the Queue;
void gQueueImpress(gQueue* q);                                                               // Displays the Queue on the Terminal in List Format;
void gQueueRemove(gQueue* q, gQueueDataPtr data);                                            // Removes a given element from the Queue;
bool gQueueIsEmpty(gQueue* q);                                                               // Checks if the queue is empty. Returns 1 if empty and 0 otherwise;
bool gQueueSearch(gQueue* q, gQueueDataPtr data);                                            // Verifies the presence of an element in the Queue, returning 1 if found and 0 otherwise;
bool gQueueIsEquals(gQueue* q1, gQueue* q2);                                                 // Determines whether two queues are identical. The judging criteria consists of a quantitative, qualitative and structural correspondence of the elements in both queues;
bool gQueueHasSameElements(gQueue* q1, gQueue* q2);                                          // Determines whether two queues have the same elements, disregarding ordering criteria in this analysis;
bool gQueueShareSameElements(gQueue* q1, gQueue* q2);                                        // Determines whether two queues share the same elements, disregarding ordering and multiplicity criteria of elements;
uint32_t gQueueCount(gQueue* q, gQueueDataPtr data);                                         // Counts the occurrences of a given element in the queue and returns the total obtained from this count;
uint32_t gQueueSize(gQueue* q);                                                              // Returns the number of elements in the queue;
gQueueDataPtr gQueueDequeue(gQueue* q);                                                      // Returns a pointer to the newly dequeued element from the queue;
gQueueDataPtr gQueueGetBiggest(gQueue* q);                                                   // Returns a pointer to the biggest element present on the queue;
gQueueDataPtr gQueueGetSmallest(gQueue* q);                                                  // Returns a pointer to the smallest element present on the queue.

#endif

//
// Example of Using the Queue in a Program:
/*

#include <string.h>
#include "genQueue.h"


typedef struct {
    char* name;
    unsigned int id;
} Person;


void impressFPerson(void* data);
int compareFPerson(void* data1, void* data2);
void destroyFPerson(void* data);
void* deepcopyFPerson(void* data);
void impressFIntegers(void* data);
int compareFIntegers(void* data1, void* data2);
Person* createPerson(char* name, unsigned int id); // Function determined to speed up the process of creating persons.


int main(int argc, char** argv) {

    puts("*Creating a Queue of Persons.");
    gQueue* queueOfPersons = initgQueue(impressFPerson, compareFPerson, destroyFPerson, deepcopyFPerson);
    printf("Queue Created: "); gQueueImpress(queueOfPersons); printf("\n\n");

    Person *person1 = createPerson("Ayrton", 19), *person2 = createPerson("James", 20), *person3 = createPerson(NULL, 17);
    Person *person4 = createPerson("Carlos", 21), *person5 = createPerson("Davi", 18);

    puts("Inserting Persons into the queue:");
    gQueueEnqueue(queueOfPersons, person1);
    gQueueEnqueue(queueOfPersons, person2);
    gQueueEnqueue(queueOfPersons, person3);
    gQueueEnqueue(queueOfPersons, person4);
    gQueueEnqueue(queueOfPersons, person5);

    gQueueImpress(queueOfPersons); printf("\n");

    puts("\n*Removing Person3 from the queue:");
    gQueueRemove(queueOfPersons, person3);
    gQueueImpress(queueOfPersons); printf("\n");

    Person* dequeuedPerson = gQueueDequeue(queueOfPersons);
    if (dequeuedPerson) {
        printf("\nDequeued Person: "); impressFPerson(dequeuedPerson); printf("\n");
        destroyFPerson(dequeuedPerson); dequeuedPerson = NULL;
    }

    gQueueImpress(queueOfPersons); printf("\n\n");
    gQueueRemove(queueOfPersons, person3);                               // TRYING to remove person3 - which is no longer present - from the queue.

    puts("Replacing removed elements:");
    gQueueEnqueue(queueOfPersons, createPerson("Ayrton", 19));
    gQueueEnqueue(queueOfPersons, createPerson(NULL, 17));
    gQueueImpress(queueOfPersons); printf("\n\n");

    puts("*Copying the Queue of Persons:");
    gQueue* copyQueueOfPersons = gQueueCopy(queueOfPersons);

    puts("After clearing all queue elements:");
    gQueueClear(queueOfPersons);                                       // Removing all elements contained in the queue.
    gQueueImpress(queueOfPersons); printf("\n");

    puts("\n*Destroying Original Queue of Persons.");
    gQueueDestroy(&queueOfPersons);                                    // Destroying the Queue before exiting.
    gQueueImpress(queueOfPersons);                                     // TRYING to Display the released queue in the terminal.
    puts("*Original Queue of Persons Destroyed.\n");

    
    puts("Displaying the new copy of the Persons queue, demonstrating its independence from the original queue that was recently destroyed:");
    gQueueImpress(copyQueueOfPersons); printf("\n");
    
    gQueueDestroy(&copyQueueOfPersons);


    puts("\nNow, let's create a simple integer queue, a type of data structure that does not require dynamic memory allocation.");

    puts("*Creating the Queue of Integers:");
    gQueue* queueOfIntegers = initgQueue(impressFIntegers, compareFIntegers, NULL, NULL);
    gQueueImpress(queueOfIntegers); printf("\n\n");

    int val1 = 1, val2 = 2, val3 = 3, val4 = 4, val5 = 5;

    puts("*Inserting values from 1 to 5 in the integer queue:");
    gQueueEnqueue(queueOfIntegers, &val1);
    gQueueEnqueue(queueOfIntegers, &val2);
    gQueueEnqueue(queueOfIntegers, &val3);
    gQueueEnqueue(queueOfIntegers, &val4);
    gQueueEnqueue(queueOfIntegers, &val5);
    gQueueImpress(queueOfIntegers); printf("\n\n");


    puts("All previously performed operations are equally applicable to the integer queue, so it would be redundant to recreate them for this specific example.");

    puts("We will demonstrate below that the replication function of queues remains fully functional even in the absence of an explicit copy method provided during queue creation.\nThis is due to the fact that in this particular case there is no dynamic memory allocation.");

    puts("\n*Copying the Queue of Integers:");
    gQueue* copyQueueOfIntegers = gQueueCopy(queueOfIntegers);
    gQueueImpress(copyQueueOfIntegers); printf("\n\n");

    puts("*Destroying the Original Queue of Integers:");
    gQueueDestroy(&queueOfIntegers);

    puts("\nThe original queue remains independently unchanged:");
    gQueueImpress(copyQueueOfIntegers); printf("\n");

    puts("\n*Destroying also the copy of the original Queue of Integers:");
    gQueueDestroy(&copyQueueOfIntegers);

    puts("\n\nProgram Finished!");

    return 0;
}


void impressFPerson(void* data) {
    if (!data) return;

    Person* originalPerson = (Person *)data;

    printf("Person(%s, %u)", (originalPerson->name != NULL) ? originalPerson->name : "NULL", originalPerson->id);
    return;
}


int compareFPerson(void* data1, void* data2) {
    if (!data1 || !data2) {
        if (!data1 && !data2) return 0;
        return (data1 == NULL) ? (-1) : 1;
    }

    Person* aux1 = (Person *)data1;
    Person* aux2 = (Person *)data2;

    do {
        if (!(aux1->name) || !(aux2->name)) {
            if (!(aux1->name) && !(aux2->name)) break;
            return (aux1->name == NULL) ? (-1) : 1;
        } else {
            int nameComparisonResult = strcmp(aux1->name, aux2->name);
            if (nameComparisonResult != 0) return nameComparisonResult;
            break;
        }

    } while(false);

    if (aux1->id > aux2->id) return 1;
    if (aux1->id < aux2->id) return -1;
    return 0;
}


void destroyFPerson(void* data) {
    if (!data) return;

    // Deallocating the memory reserved for the name:
    if(((Person *)data)->name) free(((Person *)data)->name);
    free(data); data = NULL;

    return;
}


Person* createPerson(char* name, unsigned int id) {
    Person* newPerson = (Person *) malloc(sizeof(Person));
    if (newPerson == NULL) {
        fprintf(stderr, "Error: Failed while trying to allocate memory for a new Person.\n");
        exit(EXIT_FAILURE);
    }

    newPerson->id = id;
    if (name == NULL) { newPerson->name = NULL; return newPerson; }
    // debbuging:
    // printf("Name Size: %d\n", strlen(name) + 1);
    newPerson->name = (char *) malloc(strlen(name) + 1);
    strcpy(newPerson->name, name);

    return newPerson;
}


void* deepcopyFPerson(void* data) {
    if (!data) return NULL;

    Person* originalPerson = (Person *)data;
    Person* newPerson = createPerson(originalPerson->name, originalPerson->id);

    return newPerson;
}


void impressFIntegers(void* data) {
    if (!data) return;
    printf("%d", *(int *)data);
    return;
}


int compareFIntegers(void* data1, void* data2) {
    if (!data1 || !data2) {
        if (!data1 && !data2) return 0;
        return (data1 == NULL) ? (-1) : 1;
    }

    int aux1 = *(int *)data1;
    int aux2 = *(int *)data2;

    if (aux1 > aux2) return 1;
    if (aux1 < aux2) return -1;
    return 0;
}

*/
