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
  Node* front;
  Node* rear;
  unsigned int counter;
} Queue;


void init_queue(Queue* q, impressFunctionQ impressfunction, compareFunctionQ comparefunction);
int is_empty(Queue* q);
void enqueue(Queue* q, void* data);
void impressQueue(Queue* q);
void free_queue(Queue* q);
int search_queue(Queue* q, void* data);
void remove_queue(Queue* q, void* data);
void* dequeue(Queue* q);

#endif