#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#ifndef GENERICBUBBLESORTER_H
#define GENERICBUBBLESORTER_H

typedef void* genSortArrayPtr;
typedef void* genSortDataPtr;

typedef int (*compareFunctionGenSort)(genSortDataPtr data1, genSortDataPtr data2);
typedef void (*swapFunctionGenSort)(genSortDataPtr data1, genSortDataPtr data2);

void gBubbleSort(compareFunctionGenSort compareF, swapFunctionGenSort swapF, genSortArrayPtr arrayPointer, uint64_t arraySize, uint64_t dataSize);
void gMergeSort(compareFunctionGenSort compareF, swapFunctionGenSort swapF, genSortArrayPtr arrayPointer, uint64_t arraySize, uint64_t dataSize);

#endif