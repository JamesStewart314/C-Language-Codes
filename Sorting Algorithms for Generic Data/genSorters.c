#include "genSorters.h"


void gSwapVariables(void* variableA, void* variableB, uint64_t variableSize) {

    // Function used to swap the content of two variables of any type.
    // The main idea is to swap each byte of the variables, that is, 
    // swap each 8-bit block until all bytes of both variables have 
    // their contents swapped.

    int8_t tempContentSwapper;

    // Casting the pointers to 1 byte-pointers:
    int8_t* auxVariableA = (int8_t *)variableA;
    int8_t* auxVariableB = (int8_t *)variableB;

    // Swapping the Content:
    while ((variableSize--) > 0) {
        tempContentSwapper = *auxVariableA;
        *auxVariableA = *auxVariableB;
        *auxVariableB = tempContentSwapper;

        // Advancing to the next memory address:
        auxVariableA += 1;
        auxVariableB += 1;
    }

    return;
}

/*
void gSwapVariables(void* variableA, void* variableB, uint64_t variableSize) {
    void* auxVariable = malloc(variableSize);
    memcpy(auxVariable, variableA, variableSize);
    memcpy(variableA, variableB, variableSize);
    memcpy(variableB, auxVariable, variableSize);
    free(auxVariable);

    return;
}
*/


void gMergeArrays(compareFunctionGenSort compareF, void* arrayPointer, uint64_t start, uint64_t middle, uint64_t end, uint64_t dataSize) {
    if (!arrayPointer) return;

    uint64_t arraySize = (end - start + 1);

    void* auxiliarMergeArray = (void *) malloc(dataSize * arraySize);
    if (auxiliarMergeArray == NULL) {
        fprintf(stderr, "Error: Cannot allocate memory for the auxiliar array in generic Merge Sort.\n");
        return;
    }

    uint64_t auxIndexCounter = 0;

    uint64_t auxCounter1 = start, auxCounter2 = middle;

    while ((auxCounter1 < middle) && (auxCounter2 <= end)) {
        int comparisonResult = compareF(arrayPointer + auxCounter1 * dataSize, arrayPointer + auxCounter2 * dataSize);
        
        if (comparisonResult < 0) {
            gSwapVariables(auxiliarMergeArray + auxIndexCounter * dataSize, arrayPointer + auxCounter1 * dataSize, dataSize);
            auxIndexCounter++;
            auxCounter1++;
            continue;
        }

        if (comparisonResult > 0) {
            gSwapVariables(auxiliarMergeArray + auxIndexCounter * dataSize, arrayPointer + auxCounter2 * dataSize, dataSize);
            auxIndexCounter++;
            auxCounter2++;
            continue;
        }

        // comparisonResult == 0:
        gSwapVariables(auxiliarMergeArray + (auxIndexCounter++) * dataSize, arrayPointer + auxCounter1 * dataSize, dataSize);
        gSwapVariables(auxiliarMergeArray + (auxIndexCounter++) * dataSize, arrayPointer + auxCounter2 * dataSize, dataSize);
        auxCounter1++;
        auxCounter2++;
    }

    while (auxCounter1 < middle) {
        gSwapVariables(auxiliarMergeArray + auxIndexCounter * dataSize, arrayPointer + auxCounter1 * dataSize, dataSize);
        auxIndexCounter++;
        auxCounter1++;
    }

    while (auxCounter2 <= end) {
        gSwapVariables(auxiliarMergeArray + auxIndexCounter * dataSize, arrayPointer + auxCounter2 * dataSize, dataSize);
        auxIndexCounter++;
        auxCounter2++;
    }

    for (uint64_t i = 0; i < arraySize; i++) {
        gSwapVariables(auxiliarMergeArray + i * dataSize, arrayPointer + (start + i) * dataSize, dataSize);
    }

    free(auxiliarMergeArray);
}


void gRecursiveMergeSort(compareFunctionGenSort compareF, void* arrayPointer, uint64_t arraySize, uint64_t dataSize) {
    if (!arrayPointer) return;

    if (arraySize == 0 || arraySize == 1) return;
    if (arraySize == 2) {
        if (compareF(arrayPointer, arrayPointer + dataSize) > 0) gSwapVariables(arrayPointer, arrayPointer + dataSize, dataSize);
        return;
    }

    uint64_t halfArraySize = arraySize / 2;

    gRecursiveMergeSort(compareF, arrayPointer, halfArraySize, dataSize);
    gRecursiveMergeSort(compareF, arrayPointer + dataSize * halfArraySize, arraySize - halfArraySize, dataSize);

    gMergeArrays(compareF, arrayPointer, 0, halfArraySize, arraySize - 1, dataSize);

    return;
}


void gRecursiveQuickSort(compareFunctionGenSort compareF, void* arrayPointer, uint64_t arraySize, uint64_t dataSize) {
    if (!arrayPointer) return;

    if (arraySize == 0 || arraySize == 1) return;
    if (arraySize == 2) {
        if (compareF(arrayPointer, arrayPointer + dataSize) > 0) gSwapVariables(arrayPointer, arrayPointer + dataSize, dataSize);
        return;
    }

    /* Strategically choosing the pivot based on the median between the first, last and central element of the array.
     This technique, known as "median of three", helps reduce the likelihood of unbalanced partitions, which can lead 
     to poor algorithm performance — O(n²) case. By using the median of these three elements, we increase the chance of 
     obtaining a pivot closer to the central value, promoting more balanced partitions and substantially improving the 
     overall efficiency of Quicksort.
    */

    uint64_t medianIndex = arraySize / 2;

    void* startPointer = arrayPointer;
    void* medianPointer = arrayPointer + dataSize * medianIndex;
    void* endPointer = arrayPointer + dataSize * (arraySize - 1);
    
    if (compareF(startPointer, medianPointer) >= 0) gSwapVariables(startPointer, medianPointer, dataSize);
    if (compareF(medianPointer, endPointer) >= 0) gSwapVariables(medianPointer, endPointer, dataSize);
    if (compareF(startPointer, medianPointer) >= 0) gSwapVariables(startPointer, medianPointer, dataSize);

    if (arraySize == 3) return;

    // Ensuring that the best pivot of the median between the first, 
    // last and middle elements of the array is at the end of the array:
    gSwapVariables(medianPointer, endPointer, dataSize);
    void* pivotPointer = endPointer;

    void* auxIndexI = arrayPointer;
    void* auxIndexJ = arrayPointer + (arraySize - 2) * dataSize;

    while (compareF(auxIndexI, pivotPointer) <= 0 && auxIndexI < auxIndexJ) auxIndexI += dataSize;
    while (compareF(auxIndexJ, pivotPointer) > 0 && auxIndexI < auxIndexJ) auxIndexJ -= dataSize;

    while (auxIndexI < auxIndexJ) {
        gSwapVariables(auxIndexI, auxIndexJ, dataSize);
        while (compareF(auxIndexI, pivotPointer) <= 0 && auxIndexI < auxIndexJ) auxIndexI += dataSize;
        while (compareF(auxIndexJ, pivotPointer) > 0 && auxIndexI < auxIndexJ) auxIndexJ -= dataSize;
    }

    uint64_t auxIndexIFinalIndex = (uint64_t)(auxIndexI - arrayPointer) / dataSize;

    if (compareF(auxIndexI, pivotPointer) >= 0) {
        gSwapVariables(auxIndexI, pivotPointer, dataSize);
        gRecursiveQuickSort(compareF, arrayPointer, auxIndexIFinalIndex, dataSize);
    } else {
        gRecursiveQuickSort(compareF, arrayPointer, auxIndexIFinalIndex + 1, dataSize);
    }

    gRecursiveQuickSort(compareF, auxIndexI + dataSize, arraySize - (auxIndexIFinalIndex + 1), dataSize);

    return;  
}


void gBubbleSort(compareFunctionGenSort compareF, void* arrayPointer, uint64_t arraySize, uint64_t dataSize) {
    if (!arrayPointer) return;

    if (!compareF) {
        fprintf(stderr, "Error: Cannot generic Bubble Sort the Array if the compare function is NULL.\n");
        return;
    }

    if (arraySize == 0 || dataSize == 0) {
        if (arraySize == 0) fprintf(stderr, "Error: ArraySize parameter for generic Bubble Sort function cannot be zero.\n");
        if (dataSize == 0) fprintf(stderr, "Error: DataSize parameter for generic Bubble Sort function cannot be zero.\n");
        return;
    }

    // Trivial Cases:
    if (arraySize == 0 || arraySize == 1) return;
    if (arraySize == 2) {
        if (compareF(arrayPointer, arrayPointer + dataSize) > 0) gSwapVariables(arrayPointer, arrayPointer + dataSize, dataSize);
        return;
    }

    bool changeMade = 0;
    int comparisonResult;

    for (uint64_t auxCounter1 = 0; auxCounter1 < arraySize - (uint64_t)1; auxCounter1++) {
        // Variable to determine whether there was a swap between values.
        // If there are no changes in a loop iteration, then the
        // array is already sorted and we can terminate the
        // function prematurely:
        changeMade = 0;

        for (uint64_t auxCounter2 = 0; auxCounter2 < (arraySize - 1) - auxCounter1; auxCounter2++) {
            comparisonResult = compareF(arrayPointer + (dataSize * auxCounter2), arrayPointer + (dataSize * (auxCounter2 + 1)));
            
            if (comparisonResult > 0) {
                gSwapVariables(arrayPointer + (dataSize * auxCounter2), arrayPointer + (dataSize * (auxCounter2 + 1)), dataSize);
                changeMade = 1;
            }
        }

        if (changeMade == 0) return;
    }

    return;
}


void gMergeSort(compareFunctionGenSort compareF, void* arrayPointer, uint64_t arraySize, uint64_t dataSize) {
    if (!arrayPointer) return;

    if (!compareF) {
        fprintf(stderr, "Error: Cannot generic Merge Sort the Array if the compare function is NULL.\n");
        return;
    }

    if (arraySize == 0 || dataSize == 0) {
        if (arraySize == 0) fprintf(stderr, "Error: ArraySize parameter for generic Merge Sort function cannot be zero.\n");
        if (dataSize == 0) fprintf(stderr, "Error: DataSize parameter for generic Merge Sort function cannot be zero.\n");
        return;
    }

    gRecursiveMergeSort(compareF, arrayPointer, arraySize, dataSize);

    return;
}


void gQuickSort(compareFunctionGenSort compareF, void* arrayPointer, uint64_t arraySize, uint64_t dataSize) {
    if (!arrayPointer) return;

    if (!compareF) {
        fprintf(stderr, "Error: Cannot generic Quick Sort the Array if the compare function is NULL.\n");
        return;
    }
    
    if (arraySize == 0 || dataSize == 0) {
        if (arraySize == 0) fprintf(stderr, "Error: ArraySize parameter for generic Quick Sort function cannot be zero.\n");
        if (dataSize == 0) fprintf(stderr, "Error: DataSize parameter for generic Quick Sort function cannot be zero.\n");
        return;
    }

    gRecursiveQuickSort(compareF, arrayPointer, arraySize, dataSize);

    return;
}