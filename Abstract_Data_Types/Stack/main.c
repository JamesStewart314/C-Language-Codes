#include "Pilha.h"

int main(int argc, char *argv[]) {

    stCreate();

    Tipo aux;
    int contador;

    Aluno vet[] = {
        { "Ana", {8,7,0,0}, 1234567},
        { "Bia", {8,10,0,0}, 1234568},
        { "Dri", {8,10,0,0}, 1234570},
        { "Juli", {8,10,0,0}, 1234571},
        { "Edu", {9,8,0,0}, 1234569}
    };

    for (int i = 0 ; i < (int)(sizeof(vet) / sizeof(*vet)) ; ++i) {
        stPush(vet[i]);
    }

    // testes :

    while (!stIsEmpty()) {
        stCount(&contador);
        stPop(&aux);
        printf("%s\n", aux.nome);
        printf("%d\n", contador);
    }

    stDestroy();

    return 0;
}
