#include <stdio.h>
#include <stdlib.h>

#ifndef LCIRCULAR_H_INCLUDED
#define LCIRCULAR_H_INCLUDED

typedef struct {
    char nome[80]; // nome do aluno
    float notas[4]; // Notas do aluno
    int cpf; // cpf do aluno
} Aluno;

typedef Aluno Tipo;

typedef int Logic;

#define TRUE 1
#define FALSE 0

Logic lcCurrent(Tipo *e);// retorna o elemento atual da lista circular
Logic lcInsert(Tipo e);// inserir elemento apos o corrente
Logic lcDelete(); // remove elemento corrente, retornando-o opcionalmente
Logic lcDelete(Tipo *e); // remove elemento corrente, retornando-o opcionalmente
                         // o corrente passa a ser o proximo
Logic lcCount(int *total); //retorna o total de elementos da lista circular

Logic lcCreate(void* funct);// inicializacoes
Logic lcDestroy();// limpar a memoria
Logic lcIsFull();// saber se está cheio
Logic lcIsEmpty();// saber se está vazio
Logic lcNext();// muda o corrente para o proximo
Logic lcPrevious();// muda o corrente para o anterior

Logic lcPrint();


#endif // LCIRCULAR_H_INCLUDED
