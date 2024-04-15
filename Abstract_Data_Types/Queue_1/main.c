#include "Fila.h"

int main() {
    char nomes[3][4] = {"ana", "bia", "edu"};
    queueCreate(); //criacao da fila
    char nome_temp[TAM_NOME]; //nome temporario

    //colocando os nomes na fila
    for (int i = 0; i < sizeof(nomes) / sizeof(*nomes) ; i++) {
        queueIn(nomes[i]);
    }

    //exibindo os nomes da fila
    while (!(queueIsEmpty())) {
        queueOut(nome_temp);
        printf("%s\n", nome_temp);
    }

    //testes da fila :

    //queueIn("das");
    //queueOut(nome_temp);
    //printf("%s\n", nome_temp);
    //queueIn("per");
    //queueIn("pet");
    //queueOut(nome_temp);
    //printf("%s\n", nome_temp);
    //queueOut(nome_temp);
    //printf("%s\n", nome_temp);

    queueDestroy();

    return 0;
}
