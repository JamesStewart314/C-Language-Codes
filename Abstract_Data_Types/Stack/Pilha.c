#include "Pilha.h"

Node* topo = NULL;
int count;

Logico stCreate(){
    count = 0;

    return TRUE;
}

Logico stDestroy(){
    Node* temp;

    while (topo != NULL) {
        temp = topo;
        topo = topo -> next;
        free(temp);
    }

    topo = NULL;
    count = 0;

    return TRUE;
}

Logico stIsEmpty() {
    if (count == 0)
        return TRUE;

    return FALSE;
}

Logico stPush(Tipo e) {
    Node* NewNode = (Node *) malloc (sizeof(Node));
    NewNode -> data = e;

    if (stIsEmpty()) {
        (*NewNode).next = NULL;
        topo = NewNode;
        count = 1;

        return TRUE;
    }

    NewNode -> next = topo;
    topo = NewNode;
    count++;

    return TRUE;
}

Logico stPop(Tipo *e) {
    if (stIsEmpty())
        return FALSE;

    count--;
    *e = topo -> data;
    Node* temp = topo;
    topo = topo -> next;
    free(temp);

    return TRUE;
}

Logico stCount(int *total) {
    *total = count;

    return TRUE;
}
