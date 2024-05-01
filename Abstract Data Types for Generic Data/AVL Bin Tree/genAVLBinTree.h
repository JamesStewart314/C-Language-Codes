#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "../Queue/genQueue.h"
#include "../Stack/genStack.h"

typedef void (*impressFunctionBinTree)(void* data);
typedef int (*compareFunctionBinTree)(void* data1, void* data2);

typedef struct BINTREENODE {
    void* data;
    size_t height;
    struct BINTREENODE *left, *right;
} binTreeNode;


typedef struct BINTREE {
    binTreeNode* root;
    size_t counter;
    impressFunctionBinTree printF;
    compareFunctionBinTree compareF;
} binTree;


binTree* initBinTree(impressFunctionBinTree printF, compareFunctionBinTree compareF);
bool binTreeIsEmpty(binTree* tree);
void binTreeImpress(binTree* tree);
void binTreeInsert(binTree* tree, void* data);
binTree* binTreeCopy(binTree* tree);
void* getBiggestElemBinTree(binTree* tree);
bool isEqualsBinTree(binTree* tree1, binTree* tree2);
void impressByLevelBinTree(binTree* tree);
void freeBinTree(binTree** tree);
void removeElemBinTree(binTree* tree, void* data);
bool binTreeSearch(binTree* tree, void* data);
size_t binTreeCount(binTree* tree);
void binTreeTextRepr(binTree* tree);


//
// Example of Usage in a Program:
/*

#include "genAVLBinTree.h"


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


int main(int argc, char** argv) {

    binTree* integerTree = initBinTree(impressf, comparef);
    int val1 = 1, val2 = 2, val3 = 3, val4 = 4, val5 = 5;
    int antiVal1 = (-1), antiVal2 = (-2), antiVal3 = (-3), antiVal4 = (-4), antiVal5 = (-5);

    printf("Integer Tree Initial State: ");
    binTreeImpress(integerTree); printf("\n\n");
    
    binTreeInsert(integerTree, &antiVal1);
    binTreeInsert(integerTree, &val3);
    binTreeInsert(integerTree, &antiVal4);
    binTreeInsert(integerTree, &val1);
    binTreeInsert(integerTree, &antiVal5);
    binTreeInsert(integerTree, &val2);
    binTreeInsert(integerTree, &antiVal2);
    binTreeInsert(integerTree, &val4);
    binTreeInsert(integerTree, &antiVal3);
    binTreeInsert(integerTree, &val5);

    puts("After Insering the Elements from (-5) to (+5) in Random Order:");
    printf("-> Symetrical Impress: ");
    binTreeImpress(integerTree); printf("\n");
    printf("-> Impress by Level:   ");
    impressByLevelBinTree(integerTree); printf("\n");

    puts("\nCopying Integer Tree to Another new Tree:");
    binTree* integerTreeCopy = binTreeCopy(integerTree);
    printf("Copy Result: ");
    binTreeImpress(integerTree); printf("\n\n");

    int* biggestValueOnTree = (int *)getBiggestElemBinTree(integerTreeCopy);
    if (biggestValueOnTree) {
        printf("The largest value present in the tree corresponds to: %d\n", *biggestValueOnTree);
    }

    printf("Integer Tree and Copy of the Integer Tree are Equal?: %s\n\n", isEqualsBinTree(integerTree, integerTreeCopy) ? "Yes" : "No");

    puts("Displaying them by Symetrical Impress:");
    printf("Original: ");
    binTreeImpress(integerTree); printf("\n");
    printf("Copy:     ");
    binTreeImpress(integerTreeCopy); printf("\n\n");

    puts("Displaying them by Level Impress:");
    printf("Original: ");
    impressByLevelBinTree(integerTree); printf("\n");
    printf("Copy:     ");
    impressByLevelBinTree(integerTreeCopy); printf("\n\n");

    puts("*Erasing now the Original Tree.");
    freeBinTree(&integerTree);
    puts("*Original Tree Erased Sucessfuly!\n");
    printf("The Copied Tree Remains Unchanged: ");
    binTreeImpress(integerTreeCopy); printf("\n");

    removeElemBinTree(integerTreeCopy, &val3);
    puts("\nAfter Removing Val3 (+3):");
    puts("/--------------------------------------------------------\\");
    printf("-> Impress by Level:   ");
    impressByLevelBinTree(integerTreeCopy); printf("\n");
    printf("-> Symetrical Impress: ");
    binTreeImpress(integerTreeCopy); printf("\n");
    puts("\\--------------------------------------------------------/\n");

    removeElemBinTree(integerTreeCopy, &val2);
    puts("After Removing Val2 (+2):");
    puts("/-----------------------------------------------------\\");
    printf("-> Impress by Level:   ");
    impressByLevelBinTree(integerTreeCopy); printf("\n");
    printf("-> Symetrical Impress: ");
    binTreeImpress(integerTreeCopy); printf("\n");
    puts("\\-----------------------------------------------------/\n");


    removeElemBinTree(integerTreeCopy, &antiVal1);
    puts("After Removing antiVal3 (-1) (also the root):");
    puts("/-------------------------------------------------\\");
    printf("-> Impress by Level:   ");
    impressByLevelBinTree(integerTreeCopy); printf("\n");
    printf("-> Symetrical Impress: ");
    binTreeImpress(integerTreeCopy); printf("\n");
    puts("\\-------------------------------------------------/\n");


    puts("Erasing the Trees:");
    freeBinTree(&integerTreeCopy);
    freeBinTree(&integerTree);
    puts("*Trees Erased.");


    puts("End of the Program. Thanks for Using!");
    return 0;
}

*/
