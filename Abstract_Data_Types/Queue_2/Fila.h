#include <stdio.h>
#include <stdlib.h>

#ifndef FILA_H_INCLUDED
#define FILA_H_INCLUDED

#define TRUE 1
#define FALSE 0

typedef struct {
    char nome[80]; // nome do aluno
    float notas[4];
    int matricula;
} Aluno;

typedef Aluno Tipo;

typedef int Logico;

Logico queueCreate(); // cria a fila
Logico queueDestroy(); // destroi a fila
Logico queueIn(Tipo dataIn); // entrada de elementos do tipo 'Tipo'
Logico queueOut(Tipo *dataOut); // saida de elementos do tipo 'Tipo'
Logico queueIsEmpty(); // informa se a fila esta vazia
Logico queueCount(int *total); // atribui a quantidade de elementos da lista a variavel total




#endif // FILA_H_INCLUDED
