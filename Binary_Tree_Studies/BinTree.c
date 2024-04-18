#include "binTree.h"
#include "Queue.h"

void impressQueueFunctionBT(void* data) {
    // No Need to Print in this Case.
    return;
}

int compareQueueFunctionBT(void *data1, void *data2) {
    int aux1 = ((BTT *)data1)->data;
    int aux2 = ((BTT *)data2)->data;

    if (aux1 > aux2) return 1;
    if (aux1 < aux2) return -1;
    return 0;
}

BTT *initTree() { return NULL; }

BTT *createNodeTree(int elem, BTT *subTreeLeft, BTT *subTreeRight) {

    BTT *newtree = (BTT *) malloc (sizeof(BTT));
    if (NULL == newtree) {
        fprintf(stderr, "Memory allocation failure.\n");
        exit(EXIT_FAILURE);
    }

    newtree->data = elem;
    newtree->left = subTreeLeft;
    newtree->right = subTreeRight;

    return newtree;
}

void impressByLevel(BTT *tree) {
    if (!tree) {
        printf("[]\n");
        return;
    }
    
    Queue *treeQueue = (Queue *) malloc (sizeof(Queue));
    init_queue(treeQueue, impressQueueFunctionBT, compareQueueFunctionBT);
    
    enqueue(treeQueue, tree);
    BTT* temptree = (BTT *)dequeue(treeQueue);
    
    printf("Impress by Level: [");
    while (temptree) {
        printf("%d, ", temptree->data);
        
        if (temptree->left) {
            enqueue(treeQueue, temptree->left);
        }

        if (temptree->right) {
            enqueue(treeQueue, temptree->right);
        }
        
        temptree = (BTT *)dequeue(treeQueue);
    }
    
    freeQueue(treeQueue);
    printf("\b\b]\n");

    return;
}

void freeTree(BTT *tree) {
    if (!tree) return;

    if (tree->left) freeTree(tree->left);
    if (tree->right) freeTree(tree->right);

    free(tree);
    tree = NULL;

    return;
}

BTT *copyTree(BTT *tree) {
    if (!tree) return NULL;

    if (!(tree->left) && !(tree->right)) {
        return createNodeTree(tree->data, NULL, NULL);
    }

    return createNodeTree(tree->data, copyTree(tree->left), copyTree(tree->right));
}

BTT *mirrorTree(BTT *tree) {
    if (!tree) return NULL;

    BTT *aux = tree->left;
    tree->left = tree->right;
    tree->right = aux;

    mirrorTree(tree->left);
    mirrorTree(tree->right);

    return tree;
}

BTT *biggestElemTree(BTT *tree) {
    if (!tree) return NULL;

    Queue *treeQueue = (Queue *)malloc(sizeof(Queue));
    init_queue(treeQueue, impressQueueFunctionBT, compareQueueFunctionBT);
    enqueue(treeQueue, tree);

    BTT *aux = (BTT *)dequeue(treeQueue);
    BTT *maximum_value = createNodeTree(INT_MIN, NULL, NULL);

    while (aux) {
        if (aux->data > maximum_value->data) {
            maximum_value->data = aux->data;
        }

        if (aux->left) {
            enqueue(treeQueue, aux->left);
        }
        if (aux->right) {
            enqueue(treeQueue, aux->right);
        }

        aux = (BTT *)dequeue(treeQueue);
    }
    
    freeQueue(treeQueue);
    return maximum_value;
}

int isEqualsTree(BTT *tree1, BTT *tree2) {
    if (!tree1 || !tree2) {
        if (!tree1 && !tree2) return 1;
        return 0;
    }

    Queue *treeQueue1 = (Queue *)malloc(sizeof(Queue));
    Queue *treeQueue2 = (Queue *)malloc(sizeof(Queue));

    init_queue(treeQueue1, impressQueueFunctionBT, compareQueueFunctionBT);
    init_queue(treeQueue2, impressQueueFunctionBT, compareQueueFunctionBT);

    enqueue(treeQueue1, tree1);
    enqueue(treeQueue2, tree2);

    BTT *temptree1 = (BTT *)dequeue(treeQueue1);
    BTT *temptree2 = (BTT *)dequeue(treeQueue2);

    while (temptree1 && temptree2) {
        if ((temptree1->data) != (temptree2->data)) {
            freeQueue(treeQueue1); freeQueue(treeQueue2);
            return 0;
        }

        if (temptree1->left) enqueue(treeQueue1, temptree1->left);
        if (temptree1->right) enqueue(treeQueue1, temptree1->right);

        if (temptree2->left) enqueue(treeQueue2, temptree2->left);
        if (temptree2->right) enqueue(treeQueue2, temptree2->right);

        temptree1 = (BTT *)dequeue(treeQueue1);
        temptree2 = (BTT *)dequeue(treeQueue2);
    }

    if (!temptree1 && !temptree2) return 1;
    return 0;
}

void impressTree(BTT *tree) {
    if (!tree) return;

    impressTree(tree->left);
    printf("%d ;\n", tree->data);
    impressTree(tree->right);

    return;
}

int removeElem(BTT *tree, int value) {
    if (!tree) return 0;
    
    // If the Value Desired is in the Root:
    if (value == tree->data) {
        if (!(tree->left) && !(tree->right)) {
            // Returning the value 1 during 
            //recursion to indicate that the 
            // removed value corresponds to a leaf:
            return 1;
        }

        // Searching the First Leaf to Substitute the Node:
        BTT* temptree = tree->left ? tree->left : tree->right;
        BTT* parent = tree;

        while (temptree) {
            // If Reached a Leaf, Stop:
            if (!(temptree->left) && !(temptree->right)) break;

            if (temptree->left) {
                parent = temptree; 
                temptree = temptree->left; 
            } else {
                parent = temptree;
                temptree = temptree->right;
            }
        }

        tree->data = temptree->data;
        if (parent->left == temptree) { parent->left = NULL; } else { parent->right = NULL; }
        free(temptree);
    
    }
    
    // Searching on Left and Right SubTrees:
    if (tree->right) { 
        if (removeElem(tree->right, value)) {
            free(tree->right);
            tree->right = NULL;
        }
    }
    if (tree->left) { 
        if (removeElem(tree->left, value)) {
            free(tree->left);
            tree->left = NULL;
        }
    }

    return 0;
}
