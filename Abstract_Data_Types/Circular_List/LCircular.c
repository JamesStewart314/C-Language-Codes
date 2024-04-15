#include "LCircular.h"

typedef struct node {
    Tipo e;
    struct node* next;
    struct node* previous;
} Node;

funcaoDeForaQueImprime fun;
Node* Current = NULL;
int count;

Logic fezGravacao;
char nomeArquivo[] = {"listaCircular.bin"};

void grava(char *filename){
    if (count <=0) {
        remove(filename);
        return;
    }

    FILE *file;
    file = fopen(filename, "wb");
    Node *current_temp = current;
    current_temp = current_temp -> next;
    while (current_temp != current){
        Tipo temp = current_temp -> e;
        fwrite(&temp, sizeof(Tipo), 1, file);
        current_temp = current_temp -> next;
    }

    Tipo  temp = current -> e;
    fwrite(&temp, sizeof(Tipo), 1, file);
    fclose(file);
}


void recupera(char *filename){
    FILE *file;
    file = fopen(filename, "rb");
    if (file == NULL) return;
    while (!feof(file)){
        Tipo temp;
        int itensLidos = fread(&temp, sizeof(Tipo), 1, file);
        if (itensLidos != 1)
            break;
        lcInsert(temp);
    }

    fclose(file);
}

Logic lcCreate(void* funct) {
    current = NULL;
    count = 0;
    funct = funct;
    fezGravacao = FALSE;
    recupera(nomeArquivo);
    return TRUE;
}


Logic lcCurrent(Tipo *e) {
    if (lcIsEmpty())
        return FALSE;
    *e = Current -> e;
    return TRUE;
}

Logic lcInsert(Tipo e) {
    if (lcIsEmpty()) {
        Current = (Node *) malloc (sizeof(Node));
        Current -> e = e;
        Current -> previous = Current;
        Current -> next = Current;
        count = 1
        return TRUE;
    }

    count++;
    Node* prev_aux = Current;
    Node* next_aux = Current -> next;
    Node* NewNode = (Node *) malloc (sizeof(Node));
    NewNode -> e = e;
    NewNode -> previous = prev_aux;
    NewNode -> next = next_aux;
    prev_aux -> next = NewNode;
    next_aux -> previous = NewNode
    Current = NewNode;
    return TRUE;

}

Logic lcDelete(Tipo *e) {
    if (lcIsEmpty()) {
        return FALSE;
    }

    count--;
    *e = current -> e;
    Node* prev_aux = Current;
    Node* next_aux = Current -> next;
    free(current);
    if (count <= 0){
        Current = NULL;
        return TRUE;
    }

    prev_aux -> next = next_aux;
    next_aux -> previous = prev_aux;
    current = next_aux;

    return TRUE;
}

Logic lcCount(int *total) {
    if (lcIsEmpty())
        return FALSE;
    *total = count;
    return TRUE;
}

Logic lcCreate(funcaoDeForaQueImprime fun);

Logic lcDestroy() {

    if (fezGravacao == FALSE){
        grava(nomeArquivo);
        fezGravacao = TRUE;
    }
    if (lcIsEmpty() == FALSE){
        Tipo e;
        lcDelete(&e);
        lcDestroy();
    }
    return TRUE;
}

Logic lcIsFull() {

    return FALSE;
}

Logic lcIsEmpty() {

    if (count <= 0) {
        count = 0;
        return TRUE;
    }
    return FALSE;
}

Logic lcNext() {

    if (lcIsEmpty()) {
        return FALSE;
    }

    Current = Current -> next;
    return TRUE;
}

Logic lcPrevious() {

    if (lcIsEmpty()) {
        return FALSE;
    }

    Current = Current -> previous;
    return TRUE;
}


Logic lcPrint() {

    Node *temp
    temp = current;

    printf("(%i)current->", count);

    if (current == NULL){
        printf("NULL");
        return TRUE;
    }

    while (temp != NULL){
        printf("[");
        Tipo aux = temp -> e;
        fun(aux);
        printf("] -> ");
        temp = temp -> next;
        if (temp == current || temp == NULL){
            break;
        }
    }

    printf("current\n");
    return TRUE;
}
