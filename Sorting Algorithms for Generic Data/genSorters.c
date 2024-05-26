#include "genSorters.h"


void gMergeArrays(compareFunctionGenSort compareF, swapFunctionGenSort swapF, genSortArrayPtr arrayPointer, uint64_t start, uint64_t middle, uint64_t end, uint64_t dataSize) {

    uint64_t arraySize = (end - start + (uint64_t)1);

    void* auxiliarMergeArray = (void *) malloc(dataSize * arraySize);
    uint64_t auxIndexCounter = 0;

    uint64_t auxCounter1 = start, auxCounter2 = middle;

    while ((auxCounter1 < middle) && (auxCounter2 <= end)) {
        int comparisonResult = compareF(arrayPointer + auxCounter1 * dataSize, arrayPointer + auxCounter2 * dataSize);
        
        if (comparisonResult < 0) {
            swapF(auxiliarMergeArray + auxIndexCounter * dataSize, arrayPointer + auxCounter1 * dataSize);
            auxIndexCounter++;
            auxCounter1++;
            continue;
        }

        if (comparisonResult > 0) {
            swapF(auxiliarMergeArray + auxIndexCounter * dataSize, arrayPointer + auxCounter2 * dataSize);
            auxIndexCounter++;
            auxCounter2++;
            continue;
        }

        // comparisonResult == 0:
        swapF(auxiliarMergeArray + (auxIndexCounter++) * dataSize, arrayPointer + auxCounter1 * dataSize);
        swapF(auxiliarMergeArray + (auxIndexCounter++) * dataSize, arrayPointer + auxCounter2 * dataSize);
        auxCounter1++;
        auxCounter2++;
    }

    while (auxCounter1 < middle) {
        swapF(auxiliarMergeArray + auxIndexCounter * dataSize, arrayPointer + auxCounter1 * dataSize);
        auxIndexCounter++;
        auxCounter1++;
    }

    while (auxCounter2 <= end) {
        swapF(auxiliarMergeArray + auxIndexCounter * dataSize, arrayPointer + auxCounter2 * dataSize);
        auxIndexCounter++;
        auxCounter2++;
    }

    for (uint64_t i = 0; i < arraySize; i++) {
        swapF(auxiliarMergeArray + i * dataSize, arrayPointer + (start + i) * dataSize);
    }

    free(auxiliarMergeArray);
}


void gRecursiveMergeSort(compareFunctionGenSort compareF, swapFunctionGenSort swapF, genSortArrayPtr arrayPointer, uint64_t start, uint64_t end, uint64_t dataSize) {
    
    uint64_t intervalSize = end - start + (uint64_t)1;

    if (intervalSize == 0) return;
    if (intervalSize == (uint64_t)1) return;
    if (intervalSize == (uint64_t)2) {
        if (compareF(arrayPointer + start * dataSize, arrayPointer + end * dataSize) > 0) swapF(arrayPointer + start * dataSize, arrayPointer + end * dataSize);
        return;
    }

    uint64_t middlePoint = start + ((intervalSize - (uint64_t)1) / (uint64_t)2);
    
    gRecursiveMergeSort(compareF, swapF, arrayPointer, start, middlePoint - (uint64_t)1, dataSize);
    gRecursiveMergeSort(compareF, swapF, arrayPointer, middlePoint, end, dataSize);
    gMergeArrays(compareF, swapF, arrayPointer, start, middlePoint, end, dataSize);

    return;
}


void gBubbleSort(compareFunctionGenSort compareF, swapFunctionGenSort swapF, genSortArrayPtr arrayPointer, uint64_t arraySize, uint64_t dataSize) {
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


void gMergeSort(compareFunctionGenSort compareF, swapFunctionGenSort swapF, genSortArrayPtr arrayPointer, uint64_t arraySize, uint64_t dataSize) {
    if (!compareF) {
        fprintf(stderr, "Error: Cannot generic Merge Sort the Array if the compare function is NULL.\n");
        return;
    }

    if (arraySize == 0 || dataSize == 0) {
        if (arraySize == 0) fprintf(stderr, "Error: ArraySize parameter for generic Merge Sort function cannot be zero.\n");
        if (dataSize == 0) fprintf(stderr, "Error: DataSize parameter for generic Merge Sort function cannot be zero.\n");
        return;
    }

    gRecursiveMergeSort(compareF, swapF, arrayPointer, 0, arraySize - (uint64_t)1, dataSize);

    return;
}