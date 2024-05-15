#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef GENERICLINKEDLIST_H
#define GENERICLINKEDLIST_H


/* TODO: CREATE THE DEEP COPY FUNCTIONALITY FOR EVERY DATA STRUCTURE. */
/* TODO: Refine the comparison function to individualize comparisons between each element in the list. */
/* TODO: FIX FUNCTION “HAS SAME ELEMENTS” FROM LINKED LIST. */
/* TODO: Create a set of functions to redefine the functions responsible for performing operations on each data structure individually. */
/* HASSAMEELEMENTS AND SHARESAMEELEMENTS */


/*  
  If necessary, it is possible to specify 
 the type of pointer used in the data 
 structure by modifying the preprocessing 
 directive parameter right below:
*/
typedef void* gLkLsPointerData;

typedef void (*impressFunctionGenLinkedList)(gLkLsPointerData data);                                                                             // Function responsible for displaying each element in the list with appropriate formatting;

typedef int (*compareFunctionGenLinkedList)(gLkLsPointerData data1, gLkLsPointerData data2);                                                     //  Function whose purpose is to compare two elements in the list. Returns zero if the elements are equal, a negative value if  
                                                                                                                                                 // the first parameter is less than the second, and a positive value if the first parameter is greater than the second;

typedef void (*destroyFuntionGenLinkedList)(gLkLsPointerData data);                                                                              // Function intended to deallocate the memory reserved in each individual element of the linked list.

typedef struct GENERICLINKEDLISTNODE {
    gLkLsPointerData data;
    struct GENERICLINKEDLISTNODE* next;
} gLinkedListNode;


typedef struct {
    gLinkedListNode *front, *rear;
    size_t counter;
    impressFunctionGenLinkedList printF;
    compareFunctionGenLinkedList compareF;
    destroyFuntionGenLinkedList destroyF;
} gLinkedList;


gLinkedList* initgLinkedList(impressFunctionGenLinkedList printF, compareFunctionGenLinkedList compareF, destroyFuntionGenLinkedList destroyF);  // Initializes a generic linked list and returns a pointer to it. The function takes pointers to print and compare functions as parameters;
gLinkedList* gLinkedListCopy(gLinkedList* list);
void gLinkedListDestroy(gLinkedList** listPointer);                                                                                              // Destroys the generic linked list, freeing all allocated memory for it. Receives a pointer to the pointer of the list as a parameter;
void gLinkedListImpress(gLinkedList* list);                                                                                                      // Prints the data stored in each node of the linked list;
void gLinkedListReverse(gLinkedList* list);                                                                                                      // Inverts the ordered sequential arrangement of the elements present in the list;
void gLinkedListAppend(gLinkedList* list, gLkLsPointerData data);                                                                                // Appends a new node containing the provided data to the end of the linked list;
void gLinkedListClear(gLinkedList* list);                                                                                                        // Clears the linked list, removing all nodes and freeing allocated memory;
void gLinkedListRemove(gLinkedList* list, gLkLsPointerData data);                                                                                // Removes the first node containing the provided data from the linked list and returns it;
bool gLinkedListIsEmpty(gLinkedList* list);                                                                                                      // Checks if the generic linked list is empty;
bool gLinkedListSearch(gLinkedList* list, gLkLsPointerData data);                                                                                // Searches for a node containing the provided data in the linked list. Returns true if found, false otherwise;
bool gLinkedListIsEquals(gLinkedList* list1, gLinkedList* list2);                                                                                // Determines whether two linked lists are identical. The judging criterion rests on determining the quantitative, qualitative and structural equivalence regarding the arrangement of the elements in the list;
bool gLinkedListHasSameElements(gLinkedList* list1, gLinkedList* list2);                                                                         // Check whether two linked lists mutually share the same content
size_t gLinkedListSize(gLinkedList* list);                                                                                                       // Return the number of elements in the linked list;
size_t gLinkedListCount(gLinkedList* list, gLkLsPointerData data);                                                                               // Counts and returns the number of occurrences of a given element in the linked list;
gLkLsPointerData gLinkedListPop(gLinkedList* list, long int index);                                                                              // Removes and returns the node at the specified index position in the linked list;
gLkLsPointerData gLinkedListGetBiggest(gLinkedList* list);                                                                                       // Returns a pointer containing the largest value in the linked list;
gLkLsPointerData gLinkedListGetSmallest(gLinkedList* list);                                                                                      // Returns a pointer containing the smallest value in the linked list.

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


void impressf(void* data);
int comparef(void* data1, void* data2);
void destroyf(void* data);
Person* createPerson(char* name, unsigned int id); // Function determined to speed up the process of creating persons.


int main(int argc, char** argv) {

    puts("*Creating a Linked List of Persons.");
    gLinkedList* linkedListOfPersons = initgLinkedList(impressf, comparef, destroyf);
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

    puts("\nPopping the value in index 2:");
    Person* poppingResult = (Person *)gLinkedListPop(linkedListOfPersons, 2);
    if (poppingResult) {
        printf("Value Popped: ");
        impressf(poppingResult); printf("\n");
    }
    gLinkedListImpress(linkedListOfPersons); printf("\n");


    puts("\nPopping the value in index -1 (last element):");
    poppingResult = (Person *)gLinkedListPop(linkedListOfPersons, -1);
    if (poppingResult) {
        printf("Value Popped: ");
        impressf(poppingResult); printf("\n");
    }
    gLinkedListImpress(linkedListOfPersons); printf("\n");


    puts("\nPopping the value in index 29 (Exceeds the maximum list index):");
    poppingResult = (Person *)gLinkedListPop(linkedListOfPersons, 29);
    if (poppingResult) {
        printf("Value Popped: ");
        impressf(poppingResult); printf("\n");
    }
    gLinkedListImpress(linkedListOfPersons); printf("\n");


    puts("\nPopping the value in index -10 (Exceeds the minimum list index):");
    poppingResult = (Person *)gLinkedListPop(linkedListOfPersons, -10);
    if (poppingResult) {
        printf("Value Popped: ");
        impressf(poppingResult); printf("\n");
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
    printf("=> Is the person5 in the list?: %s\n", gLinkedListSearch(linkedListOfPersons, person5) ? "Yes" : "No");

    Person* returnValue = gLinkedListGetBiggest(linkedListOfPersons);
    if (returnValue) {
        printf("=> Current Biggest Person ID on the List: %u\n", returnValue->id);
    }

    returnValue = gLinkedListGetSmallest(linkedListOfPersons);
    if (returnValue) {
        printf("=> Current Smallest Person ID on the List: %u\n", returnValue->id);
    }

    puts("\nFinal State of the List:");
    gLinkedListImpress(linkedListOfPersons); printf("\n");


    puts("\n*Destroying the Linked List!");
    gLinkedListDestroy(&linkedListOfPersons);
    printf("Linked List Destroyed: "); gLinkedListImpress(linkedListOfPersons); printf("\n");


    puts("\nProgram Finished!");

    return 0;
}


void impressf(void* data) {
    printf("Person(%s, %u)", (((Person *)data)->name != NULL) ? ((Person *)data)->name : "NULL", ((Person *)data)->id);
    return;
}


int comparef(void* data1, void* data2) {
    Person aux1 = *((Person *)data1);
    Person aux2 = *((Person *)data2);

    if (!aux1 || !aux2) {
        if (!aux1 && !aux2) return 1;
        return 0;
    }

    if (aux1.id > aux2.id) return 1;
    if (aux1.id < aux2.id) return -1;
    return 0;
}


void destroyf(void* data) {
    if(!data) return;

    // Deallocating the memory reserved for the name:
    if(((Person *)data)->name) free(((Person *)data)->name);
    return;
}


Person* createPerson(char* name, unsigned int id) {
    Person* newPerson = (Person *)malloc(sizeof(Person));
    if (newPerson == NULL) {
        fprintf(stderr, "Error: Failed while trying to allocate memory for a new Person.\n");
        exit(EXIT_FAILURE);
    }

    newPerson->id = id;
    if (name == NULL) { newPerson->name = NULL; return newPerson; }
    // debbuging:
    // printf("Name Size: %d\n", strlen(name) + 1);
    newPerson->name = (char *)malloc(strlen(name) + 1);
    strcpy(newPerson->name, name);

    return newPerson;
}

*/
