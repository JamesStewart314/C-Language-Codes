#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef MYQUEUE_H
#define MYQUEUE_H

typedef void (*impressFunctionQ)(void* data);
typedef int (*compareFunctionQ)(void* data1, void* data2);

typedef struct node {
    void* data;
    struct node *next;
} Node;


typedef struct {
  unsigned int counter;
  Node* front;
  Node* rear;
  impressFunctionQ printF;
  compareFunctionQ compareF;
} Queue;


void init_queue(Queue* q, impressFunctionQ impressfunction, compareFunctionQ comparefunction);
int queueIsEmpty(Queue* q);
void enqueue(Queue* q, void* data);
void impressQueue(Queue* q);
void freeQueue(Queue* q);
int searchInQueue(Queue* q, void* data);
void removeFromQueue(Queue* q, void* data);
void* dequeue(Queue* q);

#endif