#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef BINTREE_H
#define BINTREE_H

typedef struct BINTREE {
    int data;
    struct BINTREE *left, *right;
} BTT;

BTT *initTree();
void impressTree(BTT *tree);
BTT *createNodeTree(int elem, BTT *subTreeLeft, BTT *subTreeRight);
BTT *copyTree(BTT *tree);
BTT *mirrorTree(BTT *tree);
BTT *biggestElemTree(BTT *tree);
int isEqualsTree(BTT *tree1, BTT *tree2);
void impressByLevel(BTT *tree);
void freeTree(BTT *tree);
int removeElem(BTT *tree, int value);

#endif