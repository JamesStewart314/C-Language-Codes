#include "LCircular.h"

void imprime(Tipo t);

char codigoTecla = 0;
void menu() {
    system("cls");
    if (codigoTecla != 0)
        printf("%d\n", codigoTecla);
    printf("Menu:\n");
    printf("digite c(cadastro) f(fim) \n");
    printf("d(delete)  \n");
    printf("ou setas dir e esq\n");
    printf("\nLista Circular:\n");
    lcPrint();
    printf("\n\n");
}

void interacao() {
    char ch;

    lcCreate(imprime);
    menu();
    while (TRUE){
        ch = getch();
        codigoTecla = ch;
        if (ch == 'f' || ch == 'e'){
            break;
        } else if (ch == 'c'){
            Tipo e;
            printf("digite um nome ");
            scanf("%s", &(e.nome) );
            lcInsert(e);
            codigoTecla = 0;
        } else if (ch == 77){
            lcNext();
            codigoTecla = 0;
        } else if (ch == 75){
            lcPrevious();
            codigoTecla = 0;
        } else if (ch == 'd'){
            Tipo e;
            lcDelete(&e);
            codigoTecla = 0;
        } else {
            codigoTecla = ch;
        }
        menu();
    }
    lcDestroy();
}

void main(){
    interacao();
}


void imprime(Tipo t){
    printf("%s", t.nome);
}
