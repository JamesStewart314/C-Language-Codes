#include <stdio.h>
#include <stdlib.h>

#ifndef PILHA_H_DEFINED
#define PILHA_H_DEFINED

#define TRUE 1
#define FALSE 0

typedef struct {
    char nome[80]; // nome do aluno
    float notas[4]; // notas do aluno
    int matricula; // matricula do aluno
} Aluno;

typedef Aluno Tipo;

typedef struct node {

    Tipo data;
    struct node* next;

} Node;

typedef int Logico;

Logico stCreate(); // criação ou construção
Logico stDestroy(); // destruição
Logico stIsEmpty(); // se a pilha está  vazia
Logico stPush(Tipo e); // colocar coisas na pilha
Logico stPop(Tipo *e); // retirar coisas da pilha
Logico stCount(int *total); // retorna a quantidade de elementos na pilha

#endif // PILHA_H_DEFINED
