#include "Fila.h"

/*
// retire somente a primeira letra da linha acima (o /) e
// complete o código ao final implementando fila com lista encadeada

#define MAX 4
Tipo vetor[MAX];
int count;
int primeiro;
int ultimo;

Logico qIn(Tipo e){
    if (qIsEmpty()){
        primeiro = ultimo = 0;
        vetor[ultimo] = e;
        count = 1;
        return TRUE;
    }
    if (qIsFull())
        return FALSE;
    count++;
    ultimo = (ultimo + 1) % MAX;//wrap around
    vetor[ultimo] = e;
    return TRUE;
}
Logico qOut(Tipo *e){
    if (qIsEmpty())
        return FALSE;
    count--;
    *e = vetor[primeiro];
    primeiro = (primeiro + 1) % MAX;//wrap around
    return TRUE;
}

Logico qCreate(){
    count = 0; // zero elementos na fila
    primeiro = ultimo = -1;
    return TRUE;
}
Logico qDestroy(){
    primeiro = ultimo = -1;
    count = 0; // zero elementos na fila
    return TRUE;
}
Logico qIsFull(){
    if (count == MAX)
        return TRUE;
    return FALSE;
}
Logico qIsEmpty(){
    if (count == 0)
        return TRUE;
    return FALSE;
}
Logico qCount(int *total){
    *total = count;
    return TRUE;
}
//*/  // fim do codigo de fila com vetor


// aqui começa o seu trabalho de fila com lista encadeada
typedef struct node {
    Tipo e;
    struct node* next;
} Node;

Node* first;
Node* last;

// implemente todas as funções de fila
// certo . . .

int count;

Logico queueCreate(){
    first = last = NULL;
    count = 0;
    return TRUE;
}

Logico queueDestroy() {
    while (first != NULL) {
        Node* temp = first;
        first = first -> next;
        free(temp);
    }
    first = last = NULL;
    count = 0;

    return TRUE;
}

Logico queueIsEmpty() {
    if (count == 0)
        return TRUE;
    return FALSE;
}

Logico queueIn(Tipo dataIn) {
    if (!queueIsEmpty()) {
        Node* aux = (Node *) malloc (sizeof(Node));
        aux -> e = dataIn;
        aux -> next = NULL;
        last -> next = aux;
        last = aux;
        count++;

        return TRUE;
    } else {
        Node* aux = (Node *) malloc (sizeof(Node));
        aux -> e = dataIn;
        aux -> next = NULL;
        first = last = aux;
        count = 1;

        return TRUE;
    }

    return FALSE;
}

Logico queueOut(Tipo *data) {
    if (queueIsEmpty())
        return FALSE;

    count--;
    *data = first -> e;
    Node* aux = first;
    first = first -> next;
    free(aux);

    return TRUE;
}

Logico queueCount(int *total) {
    *total = count;

    return TRUE;
}


