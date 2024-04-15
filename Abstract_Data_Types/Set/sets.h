#include <stdio.h>
#include <stdlib.h>

// TAD de conjuntos
#ifndef SETS_H_INCLUDED
#define SETS_H_INCLUDED


typedef int Tipo;

/*
typedef    struct {
                char nome[80]; // nome do aluno
                float notas[4];
                int cpf;
            }                   Aluno;

// vamos mudar o Tipo (de int para Aluno), mas nada precisa ser mudado em Pilha.c
//typedef Aluno Tipo;
//*/



typedef int Logic;
#define TRUE 1
#define FALSE 0

// constantes para definicao de maior, igual ou menor
#define GT 1
#define EQUAL 0
#define LT -1
typedef int Result;

typedef void (*funcaoDeForaQueImprime)(Tipo);// ponteiro para função
typedef Result (*funcaoDeForaQueCompara)(Tipo, Tipo);// ponteiro para função

Logic setsCreate(funcaoDeForaQueCompara c, funcaoDeForaQueImprime i);
Logic setsAddElement(char c1, Tipo e);
Logic setsRemoveElement(char c1, Tipo e);
Logic setsBelongsTo(char c1, Tipo e);
Logic setsUnion(char c1, char c2, char c3);
Logic setsIntersection(char c1, char c2, char c3);
Logic setsNumberOfElements(char c1, int *total);
Logic setsIsIn(char c1, char c2, Logic *result);
// exemplo de uso setsUnion('K','H','C') ;
// conjunto K unido com H produzindo o conjunto C
Logic setsDestroy();


#endif // SETS_H_INCLUDED
