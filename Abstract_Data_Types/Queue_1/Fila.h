#ifndef FILA_H_INCLUDED
#define FILA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

#define Logico int
#define TAM_NOME 4

typedef char Tipo;

Logico queueCreate();
Logico queueDestroy();
Logico queueIsFull();
Logico queueIsEmpty();
Logico queueIn(Tipo e[TAM_NOME]);
Logico queueOut(Tipo *e);

#endif // FILA_H_INCLUDED
