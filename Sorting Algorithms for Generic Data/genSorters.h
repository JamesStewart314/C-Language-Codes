#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#ifndef GENERICBUBBLESORTER_H
#define GENERICBUBBLESORTER_H

typedef void* genSortVectorPtr;

typedef int (*compareFunctionGenSort)(genSortVectorPtr data1, genSortVectorPtr data2);
typedef void (*swapFunctionGenSort)(genSortVectorPtr data1, genSortVectorPtr data2);

void gBubbleSort(compareFunctionGenSort compareF, swapFunctionGenSort swapF, genSortVectorPtr arrayPointer, uint64_t arraySize, uint64_t dataSize);

#endif