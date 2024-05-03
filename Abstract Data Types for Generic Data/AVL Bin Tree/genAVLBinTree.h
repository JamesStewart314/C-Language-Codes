#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#ifndef GENERICAVLBINTREE_H
#define GENERICAVLBINTREE_H

#include "../Queue/genQueue.h"
#include "../Stack/genStack.h"

typedef void (*impressFunctionGenAVLBinTree)(void* data);
typedef int (*compareFunctionGenAVLBinTree)(void* data1, void* data2);

typedef struct AVLBINTREENODE {
    void* data;
    size_t height;
    struct AVLBINTREENODE *left, *right;
} gAVLBinTreeNode;


typedef struct {
    gAVLBinTreeNode* root;
    size_t counter;
    impressFunctionGenAVLBinTree printF;
    compareFunctionGenAVLBinTree compareF;
} gAVLBinTree;


gAVLBinTree* initgAVLBinTree(impressFunctionGenAVLBinTree printF, compareFunctionGenAVLBinTree compareF);   // Appropriately initializes the AVL Binary Tree and returns a gAVLBinTree pointer to the newly initialized instance;
bool gAVLBinTreeIsEmpty(gAVLBinTree* tree);                                                           // Checks whether an AVL Binary Tree is empty, returning 1 if it is and 0 otherwise;
void gAVLBinTreeInsert(gAVLBinTree* tree, void* data);                                                // Inserts a new element into the AVL Binary Tree if it is not already contained there;
gAVLBinTree* gAVLBinTreeCopy(gAVLBinTree* tree);                                                       // Creates an identical copy of a given AVL Binary Tree and returns a gAVLBinTree pointer to the newly created copy;
void* gAVLBinTreeGetBiggestElem(gAVLBinTree* tree);                                                   // Returns a void pointer to the largest element contained in the AVL Binary Tree;
bool gAVLBinTreeIsEquals(gAVLBinTree* tree1, gAVLBinTree* tree2);                                      // This function determines whether two AVL Binary Trees are identical. If they are equal, the function will return the value 1, otherwise it will return 0;
void gAVLBinTreeImpress(gAVLBinTree* tree);                                                           // Displays a linear textual representation of the content present in the binary tree through a symmetric traversal in its structure;
void gAVLBinTreeimpressByLevel(gAVLBinTree* tree);                                                    // Displays a linear textual representation of the content present in the binary tree through a path through levels in its structure;
                                                                                                    
void gAVLBinTreeDestroy(gAVLBinTree** tree);                                                          //  Function whose purpose is to remove memory allocated in an AVL Binary Tree structure. In order to avoid memory leaks, remember to 
                                                                                                    // invoke this function by applying it to the AVL Binary Tree(s) created when you are finished using the structure(s) in your code;

void gAVLBinTreeRemoveElem(gAVLBinTree* tree, void* data);                                            // Removes a given element from an AVL Binary Tree if it is contained therein;
bool gAVLBinTreeSearch(gAVLBinTree* tree, void* data);                                                // Determines whether an element is present in the AVL Binary Tree. If the element is present, the function returns the value 1; otherwise it will return 0;
size_t gAVLBinTreeCount(gAVLBinTree* tree);                                                           // This function calculates the number of elements present in the binary tree and returns the value resulting from this count;
void gAVLBinTreeTextRepr(gAVLBinTree* tree);                                                          // Displays an accurate linear textual representation of the structure and arrangement of the elements contained in the AVL Binary Tree;
long long int gAVLBinTreeGetNodeHeight(gAVLBinTree* tree, void* data);                                // Determines the height of a given node in the AVL Binary Tree. If the given element is not contained in the Tree, the function returns the value (-1).

#endif


/* 
             Warning: The data structure code contained in this folder has dependencies 
              on two other data structures located in the same superdirectory of this 
           directory - namely, the Queue (genQueue) and Stack (genStack) data structures. 
           Consequently, the compilation command for any project that uses this AVL Binary 
           Tree code must include the path of the directories that contain the header files 
                              of the dependencies mentioned above.

               Here is a practical example of compilation using the GCC compiler of 
                                 the program commented right below:
• gcc main.c genAVLBinTree.c ../Queue/genQueue.c ../Stack/genStack.c -o executableProgram -I ../Stack -I ../Queue

*/


//
// Example of Usage in a Program:
/*

#include "genAVLBinTree.h"


void impressf(void* data);
int comparef(void* data1, void* data2);
void clear_screen();


int main(int argc, char** argv) {

    clear_screen();

    gAVLBinTree* integerTree = initgAVLBinTree(impressf, comparef);
    int val1 = 1, val2 = 2, val3 = 3, val4 = 4, val5 = 5;
    int antiVal1 = (-1), antiVal2 = (-2), antiVal3 = (-3), antiVal4 = (-4), antiVal5 = (-5);

    printf("Integer Tree Initial State: ");
    gAVLBinTreeImpress(integerTree); printf("\n");
    
    puts("*Entering the values from (-5) to (+5) in random order.");
    gAVLBinTreeInsert(integerTree, &antiVal1);
    gAVLBinTreeInsert(integerTree, &val3);
    gAVLBinTreeInsert(integerTree, &antiVal4);
    gAVLBinTreeInsert(integerTree, &val1);
    gAVLBinTreeInsert(integerTree, &antiVal5);
    gAVLBinTreeInsert(integerTree, &val2);
    gAVLBinTreeInsert(integerTree, &antiVal2);
    gAVLBinTreeInsert(integerTree, &val4);
    gAVLBinTreeInsert(integerTree, &antiVal3);
    gAVLBinTreeInsert(integerTree, &val5);

    puts("\nAfter Insering the Elements from (-5) to (+5) in Random Order:");
    puts("/-----------------------------------------------------------\\");
    printf("-> Symetrical Impress: ");
    gAVLBinTreeImpress(integerTree); printf("\n");
    printf("-> Impress by Level:   ");
    gAVLBinTreeimpressByLevel(integerTree); printf("\n");
    puts("\\-----------------------------------------------------------/");

    puts("\n*Copying Integer Tree to Another new Tree");
    gAVLBinTree* integerTreeCopy = gAVLBinTreeCopy(integerTree);
    puts("Copy Result: ");
    puts("/-----------------------------------------------------------\\");
    printf("-> Symetrical Impress: ");
    gAVLBinTreeImpress(integerTreeCopy); printf("\n");
    printf("-> Impress by Level:   ");
    gAVLBinTreeimpressByLevel(integerTreeCopy); printf("\n");
    puts("\\-----------------------------------------------------------/");

    int* biggestValueOnTree = (int *)gAVLBinTreeGetBiggestElem(integerTreeCopy);
    if (biggestValueOnTree) {
        printf("\nThe largest value present in the tree corresponds to: %d\n", *biggestValueOnTree);
    }

    printf("\nInteger Tree and Copy of the Integer Tree are Equal?: %s\n\n", gAVLBinTreeIsEquals(integerTree, integerTreeCopy) ? "Yes" : "No");

    puts("/-----------------------------------------------\\");
    puts("Displaying them by Symetrical Impress:");
    printf("Original: ");
    gAVLBinTreeImpress(integerTree); printf("\n");
    printf("Copy:     ");
    gAVLBinTreeImpress(integerTreeCopy); printf("\n\n");

    puts("Displaying them by Level Impress:");
    printf("Original: ");
    gAVLBinTreeimpressByLevel(integerTree); printf("\n");
    printf("Copy:     ");
    gAVLBinTreeimpressByLevel(integerTreeCopy); printf("\n");
    puts("\\-----------------------------------------------/\n");

    puts("*Erasing now the Original Tree.");
    gAVLBinTreeDestroy(&integerTree);
    puts("*Original Tree Erased Sucessfuly!\n");
    printf("The Copied Tree Remains Unchanged: ");
    printf("\n-> Symetrical Impress: ");
    gAVLBinTreeImpress(integerTreeCopy); printf("\n");

    gAVLBinTreeRemoveElem(integerTreeCopy, &val3);
    puts("\nAfter Removing Val3 (+3) of the copied tree:");
    puts("/--------------------------------------------------------\\");
    printf("-> Impress by Level:   ");
    gAVLBinTreeimpressByLevel(integerTreeCopy); printf("\n");
    printf("-> Symetrical Impress: ");
    gAVLBinTreeImpress(integerTreeCopy); printf("\n");
    puts("\\--------------------------------------------------------/\n");

    gAVLBinTreeRemoveElem(integerTreeCopy, &val2);
    puts("After Removing Val2 (+2) of the copied tree:");
    puts("/-----------------------------------------------------\\");
    printf("-> Impress by Level:   ");
    gAVLBinTreeimpressByLevel(integerTreeCopy); printf("\n");
    printf("-> Symetrical Impress: ");
    gAVLBinTreeImpress(integerTreeCopy); printf("\n");
    puts("\\-----------------------------------------------------/\n");


    gAVLBinTreeRemoveElem(integerTreeCopy, &antiVal1);
    puts("After Removing antiVal1 ((-1) and also the root) of the copied tree:");
    puts("/-------------------------------------------------\\");
    printf("-> Impress by Level:   ");
    gAVLBinTreeimpressByLevel(integerTreeCopy); printf("\n");
    printf("-> Symetrical Impress: ");
    gAVLBinTreeImpress(integerTreeCopy); printf("\n");
    puts("\\-------------------------------------------------/\n");


    puts("Testing the search function in the binary tree:");
    printf("=> Is the value (-2) in the copied binary tree? : %s\n", gAVLBinTreeSearch(integerTreeCopy, &antiVal2) ? "Yes" : "No");
    printf("=> Is the value (-1) in the copied binary tree? : %s\n", gAVLBinTreeSearch(integerTreeCopy, &antiVal1) ? "Yes" : "No");
    printf("=> Total number of elements present on the tree: %zu\n", gAVLBinTreeCount(integerTreeCopy));
    printf("=> Height of the element (-2):  %lld\n", gAVLBinTreeGetNodeHeight(integerTreeCopy, &antiVal2));
    printf("=> Height of the element (-1): %lld (height == (-1) means the element is not in the tree)\n", gAVLBinTreeGetNodeHeight(integerTreeCopy, &antiVal1));

    puts("\nVisual Representation of the copied integer AVL Bin Tree:");
    puts("/---------------------------------------------------------\\");
    printf("| "); gAVLBinTreeTextRepr(integerTreeCopy); printf(" |\n");
    puts("\\---------------------------------------------------------/\n");

    puts("Erasing the Trees:");
    gAVLBinTreeDestroy(&integerTreeCopy);
    // Deleting integerTree twice, but this action does not generate an error:
    gAVLBinTreeDestroy(&integerTree);
    puts("*Trees Erased.");

    puts("End of the Program. Thanks for Using!");
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


// Function used to clean the terminal
// on Windows and Unix-Like systems:
void clear_screen() { 
    #if defined(WIN32)
        // for Windows:
        system("cls");
    #else
        // for Systems Unix-Like:
        system("clear");
    #endif

    return;
}

*/
