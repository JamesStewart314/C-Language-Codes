#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#ifndef GENERICSORTERS_H
#define GENERICSORTERS_H

// Threads with sorting...?

typedef int (*compareFunctionGenSort)(void* data1, void* data2);

void gBubbleSort(compareFunctionGenSort compareF, void* arrayPointer, uint64_t arraySize, uint64_t dataSize);
void gMergeSort(compareFunctionGenSort compareF, void* arrayPointer, uint64_t arraySize, uint64_t dataSize);
void gQuickSort(compareFunctionGenSort compareF, void* arrayPointer, uint64_t arraySize, uint64_t dataSize);

#endif