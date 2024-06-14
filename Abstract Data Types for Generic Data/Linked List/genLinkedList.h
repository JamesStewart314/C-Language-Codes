#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#ifndef GENERICLINKEDLIST_H
#define GENERICLINKEDLIST_H

/* TODO: REVIEW THE CODE COMPLETELY AND DESIGN THE INSERT FUNCTION. */

/*  
  If necessary, it is possible to specify 
 the type of pointer used in the data 
 structure by modifying the preprocessing 
 directive parameter right below:
*/
typedef void* gLinkedListDataPtr;

typedef void (*impressFunctionGenLinkedList)(gLinkedListDataPtr data);                                                                             // Function responsible for displaying each element in the list with appropriate formatting;

typedef int (*compareFunctionGenLinkedList)(gLinkedListDataPtr data1, gLinkedListDataPtr data2);                                                   //  Function whose purpose is to compare two elements in the list. Returns zero if the elements are equal, a negative value if  
                                                                                                                                                   // the first parameter is less than the second, and a positive value if the first parameter is greater than the second;

typedef void (*destroyFuntionGenLinkedList)(gLinkedListDataPtr data);                                                                              // Function intended to deallocate the memory reserved in each individual element of the linked list;

typedef gLinkedListDataPtr (*deepcopyFunctionGenLinkedList)(gLinkedListDataPtr data);                                                              // Function designed to recreate independent duplicates of each element present in the linked list.


typedef struct GENERICLINKEDLISTNODE {
    gLinkedListDataPtr data;
    struct GENERICLINKEDLISTNODE* next;
} gLinkedListNode;


typedef struct {
    gLinkedListNode *front, *rear;
    uint32_t counter;
    impressFunctionGenLinkedList printF;
    compareFunctionGenLinkedList compareF;
    destroyFuntionGenLinkedList destroyF;
    deepcopyFunctionGenLinkedList deepcopyF;
} gLinkedList;


gLinkedList* initgLinkedList(impressFunctionGenLinkedList printF, compareFunctionGenLinkedList compareF,
                             destroyFuntionGenLinkedList destroyF, deepcopyFunctionGenLinkedList deepcopyF);                                     // Initializes a generic linked list and returns a pointer to it. The function takes pointers to print and compare functions as parameters;

gLinkedList* gLinkedListCopy(gLinkedList* list);                                                                                                 // Creates an identical copy of the given linked list and returns a pointer to it. The replicated copy is completely independent of the original linked list;
void gLinkedListAppend(gLinkedList* list, gLinkedListDataPtr data);                                                                              // Appends a new node containing the provided data to the end of the linked list;
void gLinkedListClear(gLinkedList* list);                                                                                                        // Clears the linked list, removing all nodes and freeing allocated memory;
void gLinkedListDestroy(gLinkedList** listPointer);                                                                                              // Destroys the generic linked list, freeing all allocated memory for it. Receives a pointer to the pointer of the list as a parameter;
void gLinkedListImpress(gLinkedList* list);                                                                                                      // Prints the data stored in each node of the linked list;
void gLinkedListInsert(gLinkedList* list, int32_t index, gLinkedListDataPtr data);                                                               // Inserts a new element into the linked list, positioning it at the index specified by the "index" parameter;
void gLinkedListSort(gLinkedList* list);                                                                                                         // Sorts the linked list using a Merge Sort algorithm;
void gLinkedListReverse(gLinkedList* list);                                                                                                      // Inverts the ordered sequential arrangement of the elements present in the list;
void gLinkedListRemoveAll(gLinkedList* list, gLinkedListDataPtr data);                                                                           // Removes all occurrences of a given element in the linked list;
bool gLinkedListIsEmpty(gLinkedList* list);                                                                                                      // Checks if the generic linked list is empty. Returns 1 if the list is empty and 0 otherwise;
bool gLinkedListRemove(gLinkedList* list, gLinkedListDataPtr data);                                                                              // Removes the first occurrence of a given element in the linked list. Returns 1 if the element is removed and 0 otherwise;
bool gLinkedListSearch(gLinkedList* list, gLinkedListDataPtr data);                                                                              // Searches for a node containing the provided data in the linked list. Returns 1 if found and 0 otherwise;
bool gLinkedListIsEquals(gLinkedList* list1, gLinkedList* list2);                                                                                // Determines whether two linked lists are identical, returning 1 if they're identical and 0 otherwise. The judging criterion rests on determining the quantitative, qualitative and structural equivalence regarding the arrangement of the elements in the list;
bool gLinkedListHasSameElements(gLinkedList* list1, gLinkedList* list2);                                                                         // Checks whether two linked lists contain the same elements qualitatively and quantitatively, regardless of the order in which they appear. Returns 1 if the lists share the same content and 0 otherwise;
bool gLinkedListShareSameElements(gLinkedList* list1, gLinkedList* list2);                                                                       // Check whether two linked lists mutually share the same content, disregarding ordering and quantity criteria;
uint32_t gLinkedListCount(gLinkedList* list, gLinkedListDataPtr data);                                                                           // Counts and returns the number of occurrences of a given element in the linked list;
uint32_t gLinkedListSize(gLinkedList* list);                                                                                                     // Return the number of elements in the linked list;
gLinkedListDataPtr gLinkedListGetBiggest(gLinkedList* list);                                                                                     // Returns a pointer containing the largest value in the linked list;
gLinkedListDataPtr gLinkedListGetSmallest(gLinkedList* list);                                                                                    // Returns a pointer containing the smallest value in the linked list;
gLinkedListDataPtr gLinkedListGet(gLinkedList* list, int64_t index);
gLinkedListDataPtr gLinkedListPop(gLinkedList* list, int64_t index);                                                                             // Removes and returns the node at the specified index position in the linked list.

#endif


//
// Example of Using the Linked List in a Program:
/*

#include "genLinkedList.h"
#include <string.h>


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

    puts("*Creating a Linked List of Persons.");
    gLinkedList* linkedListOfPersons = initgLinkedList(impressFPerson, compareFPerson, destroyFPerson, deepcopyFPerson);
    printf("List Created: "); gLinkedListImpress(linkedListOfPersons); printf("\n");

    Person *person1 = createPerson("Ayrton", 19), *person2 = createPerson("James", 20), *person3 = createPerson(NULL, 17);
    Person *person4 = createPerson("Carlos", 21), *person5 = createPerson("Davi", 18);

    gLinkedListAppend(linkedListOfPersons, person1);
    gLinkedListAppend(linkedListOfPersons, person2);
    gLinkedListAppend(linkedListOfPersons, person3);
    gLinkedListAppend(linkedListOfPersons, person4);
    gLinkedListAppend(linkedListOfPersons, person5);

    puts("\nInserted Elements:");
    gLinkedListImpress(linkedListOfPersons); printf("\n");

    puts("\nRemoving person5 from the list:");
    gLinkedListRemove(linkedListOfPersons, person5);
    gLinkedListImpress(linkedListOfPersons); printf("\n");

    Person *poppingResult = NULL;


    //puts("\nPopping the value in index 2:");
    //poppingResult = (Person *)gLinkedListPop(linkedListOfPersons, (int32_t)2);
    //if (poppingResult) {
    //    printf("Value Popped: ");
    //    impressFPerson(poppingResult); printf("\n");
    //    destroyFPerson(poppingResult); poppingResult = NULL;
    //}
    //gLinkedListImpress(linkedListOfPersons); printf("\n");


    puts("\nPopping the value in index -1 (last element):");
    poppingResult = (Person *)gLinkedListPop(linkedListOfPersons, (int64_t)(-1));
    if (poppingResult) {
        printf("Value Popped: ");
        impressFPerson(poppingResult); printf("\n");
        destroyFPerson(poppingResult); poppingResult = NULL;
    }
    gLinkedListImpress(linkedListOfPersons); printf("\n");


    puts("\nPopping the value in index 29 (Value exceeds the maximum list index):");
    poppingResult = (Person *)gLinkedListPop(linkedListOfPersons, (int64_t)29);
    if (poppingResult) {
        printf("Value Popped: ");
        impressFPerson(poppingResult); printf("\n");
        destroyFPerson(poppingResult); poppingResult = NULL;
    }
    gLinkedListImpress(linkedListOfPersons); printf("\n");


    puts("\nPopping the value in index -10 (Value exceeds the minimum list index):");
    poppingResult = (Person *)gLinkedListPop(linkedListOfPersons, (int64_t)(-10));
    if (poppingResult) {
        printf("Value Popped: ");
        impressFPerson(poppingResult); printf("\n");
        destroyFPerson(poppingResult); poppingResult = NULL;
    }
    
    gLinkedListImpress(linkedListOfPersons); printf("\n");

    puts("\nTesting the reversing function:");
    printf("=> Before reversing: ");
    gLinkedListImpress(linkedListOfPersons); printf("\n");

    gLinkedListReverse(linkedListOfPersons);

    printf("=> After reversing: ");
    gLinkedListImpress(linkedListOfPersons); printf("\n");

    puts("\nTesting Search and Max/Min Functions: ");
    printf("=> Is the person1 in the list?: %s\n", gLinkedListSearch(linkedListOfPersons, person1) ? "Yes" : "No");

    Person* returnValue = gLinkedListGetBiggest(linkedListOfPersons);
    if (returnValue) {
        printf("=> ID from the biggest Person on the List: %u\n", returnValue->id);
    }

    returnValue = gLinkedListGetSmallest(linkedListOfPersons);
    if (returnValue) {
        printf("=> ID from the smallest Person on the List: %u\n", returnValue->id);
    }

    printf("\nBefore sorting the list: ");
    gLinkedListImpress(linkedListOfPersons); printf("\n");
    gLinkedListSort(linkedListOfPersons);
    printf("After sorting the list: ");
    gLinkedListImpress(linkedListOfPersons); printf("\n\n");


    printf("\nFinal State of the List: ");
    gLinkedListImpress(linkedListOfPersons); printf("\n\n");

    puts("*Copying the Linked List of Persons.");
    gLinkedList* copyLinkedListOfPersons = gLinkedListCopy(linkedListOfPersons);
    printf("List Copied: "); gLinkedListImpress(copyLinkedListOfPersons); printf("\n");

    puts("\n*Destroying the Original Linked List!");
    gLinkedListDestroy(&linkedListOfPersons);
    printf("*Original Linked List Destroyed.");
    gLinkedListImpress(linkedListOfPersons); printf("\n");

    printf("\nThe copy remains independent and immutable: ");
    gLinkedListImpress(copyLinkedListOfPersons); printf("\n");

    gLinkedListDestroy(&copyLinkedListOfPersons);


    puts("\n\nFor further demonstration purposes, we will create a linked list of integers, the handling of which does not require destructive or duplicate-generating functions.");

    int val1 = 1, val2 = 2, val3 = 3, val4 = 4, val5 = 5;

    printf("Creating a generic Linked List of Integers: ");
    gLinkedList* linkedListOfIntegers = initgLinkedList(impressFIntegers, compareFIntegers, NULL, NULL);
    gLinkedListImpress(linkedListOfIntegers); printf("\n");

    puts("\n*Inserting new elements.");
    gLinkedListAppend(linkedListOfIntegers, &val1);
    gLinkedListAppend(linkedListOfIntegers, &val2);
    gLinkedListAppend(linkedListOfIntegers, &val3);
    gLinkedListAppend(linkedListOfIntegers, &val4);
    gLinkedListAppend(linkedListOfIntegers, &val5);

    printf("Insertion Result: ");
    gLinkedListImpress(linkedListOfIntegers); printf("\n");

    puts("\n*Copying the Linked List of Integers.");
    gLinkedList* copyLinkedListOfIntegers = gLinkedListCopy(linkedListOfIntegers);
    printf("List Copied: ");
    gLinkedListImpress(copyLinkedListOfIntegers); printf("\n");

    puts("*Destroying the Original Linked List of Integers.");
    gLinkedListDestroy(&linkedListOfIntegers);

    printf("\nThe copy remains independent and immutable: ");
    gLinkedListImpress(copyLinkedListOfIntegers); printf("\n");

    gLinkedListDestroy(&copyLinkedListOfIntegers);


    puts("\nProgram Finished!");

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
        if (!data1 && !data2) return 0;     // Both pointers are NULL
        return (data1 == NULL) ? (-1) : 1;  // At least one pointer is NULL. The smallest is the NULL pointer.
    }

    // Pointer casting:
    Person* aux1 = (Person *)data1;
    Person* aux2 = (Person *)data2;

    do {
        if (!(aux1->name) || !(aux2->name)) {
            // At least one of the names is NULL:

            // Both are null and, consequently, equal. 
            // Ending the loop and proceeding to compare the IDs:
            if (!(aux1->name) && !(aux2->name)) break; 

            return (aux1->name == NULL) ? (-1) : 1;
        } else {
            int nameComparisonResult = strcmp(aux1->name, aux2->name);
            if (nameComparisonResult != 0) return nameComparisonResult;
            break;
        }
    } while(false);

    // Comparison of IDs if the names are the same or both are NULL:
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
