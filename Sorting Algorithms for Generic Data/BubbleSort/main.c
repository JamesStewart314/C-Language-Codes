#include "genBubbleSort.h"
#include <string.h>
#include <time.h>

#define ARRAY_SIZE 100

typedef struct {
    char* name;
    unsigned int id;
} Person;


void impressFPerson(void* data);
int compareFPerson(void* data1, void* data2);
void destroyFPerson(void* data);
void swapFPerson(void* data1, void* data2);
int compareFIntegers(void* data1, void* data2);
void swapFIntegers(void* data1, void* data2);
Person createPerson(char* name, unsigned int id); // Function determined to speed up the process of creating persons.
char* getRandomName();
unsigned int getRandomID();


int main(int argc, char** argv) {

    srand((unsigned int)time(NULL));

    gBubbleSorter* bubbleSorterOfIntegers = initgBubbleSorter(compareFIntegers, swapFIntegers);

    int random_numbers[ARRAY_SIZE];

    // Inserting random values in the array:
    for (int i = 0; i < ARRAY_SIZE; i++) {
        random_numbers[i] = rand() % 10;
    }

    puts("Array of Integers Generated Before Sorting:\n");
    printf("[");
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%d, ", random_numbers[i]);
    }
    printf("\b\b]");

    gBubbleSorterSort(bubbleSorterOfIntegers, random_numbers, (uint64_t)ARRAY_SIZE, (uint64_t)sizeof(int));

    puts("\n\n\nArray of Integers Generated After Sorting:\n");
    printf("[");
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%d, ", random_numbers[i]);
    }
    printf("\b\b]\n");

    gBubbleSorterDestroy(&bubbleSorterOfIntegers);


    gBubbleSorter* bubbleSorterOfPersons = initgBubbleSorter(compareFPerson, swapFPerson);

    Person personArray[ARRAY_SIZE];
    for (int i = 0; i < 100; i++) {
        char* name = getRandomName();
        unsigned int id = getRandomID();
        personArray[i] = createPerson(name, id);
    }

    puts("\n\n\nArray of Persons Generated Before Sorting:");
    printf("\n[");
    for (int i = 0; i < 100; i++) {
        impressFPerson(personArray + i);
        printf(", ");
    }
    printf("\b\b]\n");

    gBubbleSorterSort(bubbleSorterOfPersons, personArray, (uint64_t)ARRAY_SIZE, (uint64_t)(sizeof(Person)));

    puts("\n\n\nArray of Persons Generated After Sorting:");
    printf("\n[");
    for (int i = 0; i < 100; i++) {
        impressFPerson(personArray + i);
        printf(", ");
    }
    printf("\b\b]\n");

    gBubbleSorterDestroy(&bubbleSorterOfPersons);

    puts("\nProgram Finished. Thanks for Using!");

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


Person createPerson(char* name, unsigned int id) {
    Person* newPerson = (Person *) malloc(sizeof(Person));
    if (newPerson == NULL) {
        fprintf(stderr, "Error: Failed while trying to allocate memory for a new Person.\n");
        exit(EXIT_FAILURE);
    }

    newPerson->id = id;
    if (name == NULL) { newPerson->name = NULL; return *newPerson; }
    // debbuging:
    // printf("Name Size: %d\n", strlen(name) + 1);
    newPerson->name = (char *) malloc(strlen(name) + 1);
    strcpy(newPerson->name, name);

    return *newPerson;
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


void swapFIntegers(void* data1, void* data2) {
    int* aux1 = (int *)data1;
    int* aux2 = (int *)data2;

    int temp = *aux1;
    *aux1 = *aux2;
    *aux2 = temp;

    return;
}


void swapFPerson(void* data1, void* data2) {
    Person* aux1 = (Person *)data1;
    Person* aux2 = (Person *)data2;

    Person temp = *aux1;
    *aux1 = *aux2;
    *aux2 = temp;

    return;
}


char* getRandomName() {
    char* names[] = {"Alice", "Bob", "Charlie", "David", "Eve", "Frank", "Grace", "Henry", "Ivy", "Jack"};
    int numNames = sizeof(names) / sizeof(names[0]);
    int index = rand() % numNames;
    return names[index];
}


unsigned int getRandomID() {
    return rand() % 1000 + 1; // IDs entre 1 e 1000
}