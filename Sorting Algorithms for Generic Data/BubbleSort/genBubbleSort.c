#include "genBubbleSort.h"

gBubbleSorter* initgBubbleSorter(compareFunctionGenBubbleSorter compareF, swapFunctionGenBubbleSorter swapF) {
    if (!compareF) {
        fprintf(stderr, "Error: Cannot create a generic Bubble Sorter without a valid comparison function.\n");
        return NULL;
    }

    gBubbleSorter* newbubblesorter = (gBubbleSorter *) malloc(sizeof(gBubbleSorter));
    if (newbubblesorter == NULL) {
        fprintf(stderr, "Error: Failed while trying to allocate memory for a new generic Bubble Sorter.\n");
        exit(EXIT_FAILURE);
    }

    newbubblesorter->compareF = compareF;
    newbubblesorter->swapF = swapF;

    return newbubblesorter;
}


void gBubbleSorterDestroy(gBubbleSorter** bubbleSorterPointer) {
    if (!bubbleSorterPointer) return;
    if (!(*bubbleSorterPointer)) return;

    free((*bubbleSorterPointer)); (*bubbleSorterPointer) = NULL;

    return;
}


void gBubbleSorterSort(gBubbleSorter* sorter, genBubbleSorterVectorPtr arrayPointer, uint64_t arraySize, uint64_t dataSize) {
    if (!arrayPointer) {
        fprintf(stderr, "Error: Given arrayPointer to gBubbleSorterSort function is NULL.\n");
        return;
    }

    if (arraySize == 0 || dataSize == 0) {
        if (arraySize == 0) fprintf(stderr, "Error: ArraySize parameter for gBubbleSorterSort function cannot be zero.\n");
        if (dataSize == 0) fprintf(stderr, "Error: DataSize parameter for gBubbleSorterSort function cannot be zero.\n");
        return;
    }

    bool changeMade = 0;
    int comparisonResult;

    for (uint64_t auxCounter1 = 0; auxCounter1 < arraySize - (uint64_t)1; auxCounter1++) {
        changeMade = 0;

        for (uint64_t auxCounter2 = 0; auxCounter2 < arraySize - auxCounter1 - (uint64_t)1; auxCounter2++) {
            comparisonResult = sorter->compareF(arrayPointer + (dataSize * auxCounter2), arrayPointer + (dataSize * (auxCounter2 + 1)));
            
            if (comparisonResult > 0) {
                sorter->swapF(arrayPointer + (dataSize * auxCounter2), arrayPointer + (dataSize * (auxCounter2 + 1)));
                changeMade = 1;
            }
        }

        if (changeMade == 0) return;
    }
}