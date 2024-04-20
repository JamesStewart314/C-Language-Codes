#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef BINSEARCHTREE_H
#define BINSEARCHTREE_H

// replace "int" by your correct element type :
typedef int type;

typedef int (*compareFunction)(type a, type b);
typedef void (*impressFunction)(type a);

typedef struct BINSEARCHTREE {
  type data;
  struct BINSEARCHTREE *left, *right;
} BST;

BST* createBST(compareFunction compfFunc, impressFunction impFunc);
BST* createNodeBST(BST* tree, type element);
BST* removeNodeBST(BST* tree, type element);
void impressBST(BST* tree);
int isBinaryTree(BST* tree);


#endif