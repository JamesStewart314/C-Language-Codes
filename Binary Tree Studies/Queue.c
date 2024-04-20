#include "Queue.h"

void init_queue(Queue* q, impressFunctionQ impressfunction, compareFunctionQ comparefunction) {
  
  q->counter = (unsigned int)0;
  q->front = q->rear = NULL;
  q->printF = impressfunction;
  q->compareF = comparefunction;

  return;
}


int queueIsEmpty(Queue* q) {
  return (q->front == NULL);
}


void enqueue(Queue* q, void* data) {
  Node* newnode = (Node *) malloc (sizeof(Node));
  if (newnode == NULL) {
    fprintf(stderr, "Error: Unable to allocate memory for new node.\n");
    exit(EXIT_FAILURE);
  }

  newnode->data = data;
  newnode->next = NULL;
  (q->counter)++;

  if (queueIsEmpty(q)) {
    q->front = q->rear = newnode;
  } else {
    q->rear->next = newnode;
    q->rear = newnode;
  }

  return;
}


void impressQueue(Queue* q) {
  if (!q) return;
  if (queueIsEmpty(q)) { printf("[]\n"); return; }
  
  printf("[");
  Node* aux = q->front;
  while (aux) {
    q->printF(aux->data);
    printf(", ");
    aux = aux->next;
  }
  printf("\b\b]\n");
}


void freeQueue(Queue* q) {
  if (!q) return;
  if (queueIsEmpty(q)) return;

  Node* aux = q->front;

  do {
    q->front = q->front->next;
    free(aux);
    aux = q->front;
  } while (aux);

  q->counter = 0;

  return;
}


int searchInQueue(Queue* q, void* data) {
  if (!q) return 0;
  if (queueIsEmpty(q)) return 0;

  Node* aux = q->front;
  while(aux) {
    if (q->compareF(aux->data, data) == 0) return 1;
    aux = aux->next;
  }

  return 0;
}


void removeFromQueue(Queue* q, void* data) {
  if (!q) return;
  if (queueIsEmpty(q)) return;

  Node* aux = q->front, *previous = NULL;
  (q->counter)--;
  while(aux) {
    if (q->compareF(aux->data, data) == 0) {
      // Removing First Element:
      if (!previous) {
        q->front = q->front->next;
        free(aux);
        return;
      }

      // Removing Last Element:
      if (aux->next == NULL) {
        q->rear = previous;
        previous->next = NULL;
        free(aux);
        return;
      }
      
      previous->next = aux->next;
      free(aux);
      return;
    }
    previous = aux;
    aux = aux->next;
  }
  return;
}


void* dequeue(Queue* q) {
  if (!q) return NULL;
  if (queueIsEmpty(q)) return NULL;

  (q->counter)--;
  Node* aux = q->front;
  q->front = q->front->next;

  return aux->data;
}