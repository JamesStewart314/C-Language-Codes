#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define tamanho_nome 50

struct Pessoa {
    char nome[tamanho_nome];
    uint8_t idade;
    float peso;
};

typedef struct Pessoa tipo_pessoa;

void preencher_formulario(tipo_pessoa *formulario, unsigned int pagina);
void exibir_formulario(tipo_pessoa *formulario, unsigned int pagina);

int main(int argc, char *argv[]) {
    const unsigned int quantidade_pessoas = 3;
    int index;

    tipo_pessoa lista_prontuarios[quantidade_pessoas];

    for (index = 0; index < quantidade_pessoas; index++) {
        preencher_formulario(lista_prontuarios, index);
        system("cls");
    }

    system("cls");

    for (index = 0; index < quantidade_pessoas; index++) {
        exibir_formulario(lista_prontuarios, index);
    }

    getchar();

    return 0;
}


void preencher_formulario(tipo_pessoa *formulario, unsigned int pagina) {
    printf("Informe o nome da pessoa designada (%i):\n", pagina + 1);
    fgets(formulario[pagina].nome, sizeof(formulario[pagina].nome), stdin);
    fflush(stdin);

    printf("\nInforme a idade da pessoa designada (%i):\n", pagina + 1);
    scanf("%hhu", &formulario[pagina].idade);
    fflush(stdin);

    printf("\nInforme o peso da pessoa designada (%i):\n", pagina + 1);
    scanf("%f", &formulario[pagina].peso);
    fflush(stdin);

    printf("Pressione Enter para prosseguir . . .\n");
    getchar();
}

void exibir_formulario(tipo_pessoa *formulario, unsigned int pagina) {
    printf("/---------------------PESSOA (%i)---------------------\\\n", pagina + 1);
    printf("\tNome : %s\n", formulario[pagina].nome);
    printf("\tIdade : %u\n", formulario[pagina].idade);
    printf("\tPeso : %.2f\n", formulario[pagina].peso);
    printf("\\----------------------------------------------------/\n");
    puts("");
}
