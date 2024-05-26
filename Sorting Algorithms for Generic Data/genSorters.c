#include "genSorters.h"

void gBubbleSort(compareFunctionGenSort compareF, swapFunctionGenSort swapF, genSortVectorPtr arrayPointer, uint64_t arraySize, uint64_t dataSize) {
    if (!compareF) {
        fprintf(stderr, "Error: Cannot generic Bubble Sort the Array if the compare function is NULL.\n");
        return;
    }

    if (arraySize == 0 || dataSize == 0) {
        if (arraySize == 0) fprintf(stderr, "Error: ArraySize parameter for generic Bubble Sort function cannot be zero.\n");
        if (dataSize == 0) fprintf(stderr, "Error: DataSize parameter for generic Bubble Sort function cannot be zero.\n");
        return;
    }

    bool changeMade = 0;
    int comparisonResult;

    for (uint64_t auxCounter1 = 0; auxCounter1 < arraySize - (uint64_t)1; auxCounter1++) {
        changeMade = 0;

        for (uint64_t auxCounter2 = 0; auxCounter2 < arraySize - auxCounter1 - (uint64_t)1; auxCounter2++) {
            comparisonResult = compareF(arrayPointer + (dataSize * auxCounter2), arrayPointer + (dataSize * (auxCounter2 + 1)));
            
            if (comparisonResult > 0) {
                swapF(arrayPointer + (dataSize * auxCounter2), arrayPointer + (dataSize * (auxCounter2 + 1)));
                changeMade = 1;
            }
        }

        if (changeMade == 0) return;
    }
}