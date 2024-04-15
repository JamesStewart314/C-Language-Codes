#include "Fila.h"

#define QTD_NOMES 3

Tipo MinhaFila[QTD_NOMES][TAM_NOME];
int idx;
int idx_saida;

Logico queueCreate() {
    idx = -1;
    idx_saida = 0;
    return TRUE;
}

Logico queueDestroy() {
    idx = -1;
    idx_saida = -1;
    return TRUE;
}

Logico queueIsFull() {
    if (idx == QTD_NOMES - 1) {
        return TRUE;
    } else {
        return FALSE;
    }
}
Logico queueIsEmpty() {
    if (idx == -1) {
        return TRUE;
    } else {
        return FALSE;
    }
}
Logico queueIn(Tipo e[TAM_NOME]) {
    if (queueIsFull()) {
        return FALSE;
    } else {
        strcpy(MinhaFila[++idx], e);
        return TRUE;
    }
}
Logico queueOut(Tipo *e){
    if (queueIsEmpty()) {
        return FALSE;
    } else {
        strcpy(e, MinhaFila[idx_saida++]);
        idx_saida %= 3;
        idx--;
        if (queueIsEmpty()) {
            idx_saida = 0;
        }
        return TRUE;
    }
}
