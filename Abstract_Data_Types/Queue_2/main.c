#include "Fila.h"

int main(int argc, char *argv[]) {

    queueCreate();

    Tipo aluno_1 = {"debora", {1.1, 2.2, 3.3, 4.4}, 40028922};
    Tipo aluno_2 = {"Ysis", {3.5, 5.2, 7.3, 6.4}, 40028922};
    Tipo aluno_3 = {"Kozovits", {11.0, 12.0, 13.0, 20.0}, 40028922};

    // testes :
    Tipo temp;
    int quantidade;

    queueIn(aluno_1);

    queueCount(&quantidade);

    printf("%d\n", quantidade);

    queueIn(aluno_2);
    queueIn(aluno_3);

    queueCount(&quantidade);

    printf("%d\n", quantidade);

    queueOut(&temp);

    printf("%s\n", temp.nome);

    queueOut(&temp);

    printf("%s\n", temp.nome);

    queueOut(&temp);

    printf("%s\n", temp.nome);

    queueDestroy();

    return 0;
}
