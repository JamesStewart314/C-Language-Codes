#include "genAVLBinTree.h"

int max(int a, int b) { return (a > b) ? a : b; }


int getSubTreeHeigt(binTreeNode* subtree) {
    if (!subtree) return 0;
    return subtree->height;
}


int getSubTreeBF(binTreeNode* subtree) {
    if (!subtree) return 0;
    return getSubTreeHeigt(subtree->left) - getSubTreeHeigt(subtree->right);
}


void impressBinTreeSymetric(binTreeNode* subtree, binTree* originalStructure) { 
    if (!subtree || !originalStructure) return; 
    if (binTreeIsEmpty(originalStructure)) return;

    impressBinTreeSymetric(subtree->left, originalStructure);
    originalStructure->printF(subtree->data); printf(", ");
    impressBinTreeSymetric(subtree->right, originalStructure);

    return;
}


binTreeNode* rotateLLBinTree(binTreeNode* subtree) {
    if (!subtree) return NULL;
    if (!subtree->left) return NULL;

    binTreeNode* modNode = subtree->left;
    subtree->left = modNode->right;
    modNode->right = subtree;
    subtree->height -= 2;

    return modNode;
}


binTreeNode* rotateRRBinTree(binTreeNode* subtree) {
    if (!subtree) return NULL;
    if (!subtree->right) return NULL;

    binTreeNode* modNode = subtree->right;
    subtree->right = modNode->left;
    modNode->left = subtree;
    subtree->height -= 2;

    return modNode;    
}


binTreeNode* balanceBinTree(binTreeNode* subtree) {
    if (!subtree) return NULL;
    if (!subtree->left && !subtree->right) return subtree;

    subtree->left = balanceBinTree(subtree->left);
    subtree->right = balanceBinTree(subtree->right);

    int balanceFactor = getSubTreeBF(subtree);
    if (balanceFactor == 1 || balanceFactor == (-1)) return subtree;

    if (balanceFactor == 2) {
        int subBalanceFactor = getSubTreeBF(subtree->left);

        if (subBalanceFactor == 1) {
            return rotateLLBinTree(subtree);
            
        } else if (subBalanceFactor == (-1)) {
            (subtree->left->height)++;
            subtree->left = rotateRRBinTree(subtree->left);
            return rotateLLBinTree(subtree);
        }

    } else if (balanceFactor == (-2)) {
        int subBalanceFactor = getSubTreeBF(subtree->right);

        if (subBalanceFactor == (-1)) {
            return rotateRRBinTree(subtree);

        } else if (subBalanceFactor == 1) {
            (subtree->right->height)++;
            subtree->right = rotateLLBinTree(subtree->right);
            return rotateRRBinTree(subtree);
        }
    }

    return subtree;
}


int binTreeInsertNode(binTreeNode* subtree, binTreeNode* newleaf, compareFunctionBinTree comparef) {
    if (!subtree) return -1;

    int result = comparef(newleaf->data, subtree->data);

    if (result == 0) {
        free(newleaf);
        return -1;
    }

    if (result > 0) {
        if (!subtree->right) {
            subtree->right = newleaf;
            if (!subtree->left) {
                (subtree->height)++;
                return 1;
            }
            return 0;
        }

        if (binTreeInsertNode(subtree->right, newleaf, comparef) == 1) {
            (subtree->height)++;
            return 1;
        } else { return 0; }

    } else {
        // result < 0:
        if (!subtree->left) {
            subtree->left = newleaf;
            if (!subtree->right) {
                (subtree->height)++;
                return 1;
            }

            return 0;
        }

        if (binTreeInsertNode(subtree->left, newleaf, comparef) == 1) {
            (subtree->height)++;
            return 1;
        } else { return 0; }
    }
}


void freeNodeBinTree(binTreeNode* subtree) {
    if (!subtree) return;

    if (!subtree->left && !subtree->right) {
        free(subtree);
        return;
    }

    freeNodeBinTree(subtree->left);
    freeNodeBinTree(subtree->right);
    free(subtree);

    return;
}


binTreeNode* removeElemBinTreeNode(binTreeNode* subtree, void* data, compareFunctionBinTree compareF) {
    if (!subtree) return NULL;

    int result = compareF(data, subtree->data);
    if (result > 0) {
        if (!subtree->right) return subtree;

        subtree->right = removeElemBinTreeNode(subtree->right, data, compareF);
        subtree->height = 1 + max(getSubTreeHeigt(subtree->left), getSubTreeHeigt(subtree->right));

        return subtree;
    }

    if (result < 0) {
        if (!subtree->left) return subtree;
        
        subtree->left = removeElemBinTreeNode(subtree->left, data, compareF);
        subtree->height = 1 + max(getSubTreeHeigt(subtree->left), getSubTreeHeigt(subtree->right));

        return subtree;
    }
    
    // Otherwise, Element Found:
    // Removing the Root:
    binTreeNode* nodeAux = subtree;
    if (!nodeAux->left) {
        binTreeNode* returnNode = nodeAux->right;
        free(nodeAux);
        return returnNode;
    }

    if (!(nodeAux->left->right)) {
        nodeAux->left->right = nodeAux->right;
        binTreeNode* returnNode = nodeAux->left;
        free(nodeAux);
        return returnNode;
    }

    binTreeNode *substitute = nodeAux->left, *subsParent = NULL;
    while (substitute->right) { 
        subsParent = substitute;
        substitute = substitute->right;
    }

    subtree->data = substitute->data;
    subsParent->right = removeElemBinTreeNode(substitute, substitute->data, compareF);

    return subtree;
}


binTree* initBinTree(impressFunctionBinTree printF, compareFunctionBinTree compareF) {
    binTree* newtree = (binTree *) malloc (sizeof(binTree));
    if (newtree == NULL) {
        fprintf(stderr, "Error: Failed while trying to allocate memory for a new Binary Tree.\n");
        exit(EXIT_FAILURE);
    }

    newtree->printF = printF;
    newtree->compareF = compareF;
    newtree->counter = (size_t)0;
    newtree->root = NULL;
    
    return newtree;
}


bool binTreeIsEmpty(binTree* tree) {
    if (!tree) return 1;
    return (tree->counter <= 0);
}


void binTreeImpress(binTree* tree) {
    if (!tree) return;
    if (binTreeIsEmpty(tree)) {
        printf("<>");
        return;
    }

    printf("< ");
    impressBinTreeSymetric(tree->root, tree);
    printf("\b\b >");
    return;
}


bool binTreeSearch(binTree* tree, void* data) {
    if (!tree) return 0;
    if (binTreeIsEmpty(tree)) return 0;

    binTreeNode* nodeAux = tree->root;
    while (nodeAux) {
        if (tree->compareF(data, nodeAux->data) > 0) {
            nodeAux = nodeAux->right;
        } else if (tree->compareF(data, nodeAux->data) < 0) {
            nodeAux = nodeAux->left;
        } else { break; }
    }

    if (!nodeAux) return 0;
    return 1;

}


void binTreeInsert(binTree* tree, void* data) {
    if (!tree) return;

    binTreeNode* newleaf = (binTreeNode *) malloc (sizeof(binTreeNode));
    if (newleaf == NULL) {
        fprintf(stderr, "Error: Failed while trying to allocate memory for a new Leaf.\n");
        exit(EXIT_FAILURE);
    }

    newleaf->data = data;
    newleaf->height = 1;
    newleaf->left = NULL;
    newleaf->right = NULL;

    // If the Tree is Empty:
    if (binTreeIsEmpty(tree)) {
        (tree->counter)++;
        tree->root = newleaf;
        return;
    }

    // Inserting the New Node on the Tree:
    binTreeInsertNode(tree->root, newleaf, tree->compareF);

    (tree->counter++);
    tree->root = balanceBinTree(tree->root);

    return;
}


binTree* binTreeCopy(binTree* tree) {
    if (!tree) return NULL;
    if (binTreeIsEmpty(tree)) return initBinTree(tree->printF, tree->compareF);

    binTree* newtree = initBinTree(tree->printF, tree->compareF);
    
    gQueue* treeQueue = initQueue(tree->printF, tree->compareF);
    enqueue(treeQueue, tree->root);

    binTreeNode* tempNode;

    do {
        tempNode = (binTreeNode *)dequeue(treeQueue);
        if (!tempNode) break;
        
        binTreeInsert(newtree, tempNode->data);

        if (tempNode->right) enqueue(treeQueue, tempNode->right);
        if (tempNode->left) enqueue(treeQueue, tempNode->left);
    } while (true);

    freeQueue(&treeQueue);

    return newtree;
}


void* getBiggestElemBinTree(binTree* tree) {
    if (!tree) return NULL;
    if (binTreeIsEmpty(tree)) return NULL;

    gStack* treeStack = stInit(tree->printF, tree->compareF);
    stPush(treeStack, tree->root);

    binTreeNode* tempNode;
    binTreeNode* biggestElem = tree->root;

    do {
        tempNode = (binTreeNode *)stPop(treeStack);
        if (!tempNode) break;

        if (tree->compareF(tempNode->data, biggestElem->data)) {
            biggestElem = tempNode;
        }

        if (tempNode->right) stPush(treeStack, tempNode->right);
        if (tempNode->left) stPush(treeStack, tempNode->left);
    } while (true);

    stDestroy(&treeStack);
    return biggestElem->data;
}


bool isEqualsBinTree(binTree* tree1, binTree* tree2) {
    if (!tree1 || !tree2) {
        if (!tree1 && !tree2) return 1;
        return 0;
    }

    if (binTreeIsEmpty(tree1) || binTreeIsEmpty(tree2)) {
        if (binTreeIsEmpty(tree1) && binTreeIsEmpty(tree2)) return 1;
        return 0;
    }

    if (tree1->counter != tree2->counter) return 0;

    if (tree1->compareF != tree2->compareF) {
        fprintf(stderr, "Error: It is not possible to compare two binary trees whose comparison functions differ from each other.\n");
        exit(EXIT_FAILURE);
    }

    impressFunctionBinTree impFunction = tree1->printF;
    compareFunctionBinTree compFunction = tree1->compareF;

    gStack* treeStack1 = stInit(impFunction, compFunction);
    gStack* treeStack2 = stInit(impFunction, compFunction);

    stPush(treeStack1, tree1->root);
    stPush(treeStack2, tree2->root);

    binTreeNode* tempNode1;
    binTreeNode* tempNode2;

    do {
        tempNode1 = (binTreeNode *)stPop(treeStack1);
        tempNode2 = (binTreeNode *)stPop(treeStack2);

        if (!tempNode1 || !tempNode2) {
            if (!tempNode1 && !tempNode2) break;
            stDestroy(&treeStack1);
            stDestroy(&treeStack2);
            return 0;
        }

        if (compFunction(tempNode1->data, tempNode2->data) != 0) {
            stDestroy(&treeStack1);
            stDestroy(&treeStack2);
            return 0;
        }

        if (tempNode1->right) stPush(treeStack1, tempNode1->right);
        if (tempNode1->left) stPush(treeStack1, tempNode1->left);

        if (tempNode2->right) stPush(treeStack2, tempNode2->right);
        if (tempNode2->left) stPush(treeStack2, tempNode2->left);

    } while (true);
    
    
    stDestroy(&treeStack1);
    stDestroy(&treeStack2);

    return 1;
}


void impressByLevelBinTree(binTree* tree) {
    if (!tree) return;
    if (binTreeIsEmpty(tree)) {
        printf("<>");
        return;
    }

    gQueue* treeQueue = initQueue(tree->printF, tree->compareF);
    enqueue(treeQueue, tree->root);

    printf("< ");

    binTreeNode* tempNode;
    do {
        tempNode = (binTreeNode *)dequeue(treeQueue);
        if (!tempNode) break;

        tree->printF(tempNode->data);
        printf(", ");

        if (tempNode->left) enqueue(treeQueue, tempNode->left);
        if (tempNode->right) enqueue(treeQueue, tempNode->right);
    } while (true);

    printf("\b\b >");

    freeQueue(&treeQueue);
    return;
}


void freeBinTree(binTree** tree) {
    if (!tree) return;
    if (!(*tree)) return;

    if (binTreeIsEmpty(*tree)) {
        free(*tree); (*tree) = NULL;
        return;
    }

    freeNodeBinTree((*tree)->root);
    free(*tree); (*tree) = NULL;

    return;
}


void removeElemBinTree(binTree* tree, void* data) {
    if (!tree) return;
    if (binTreeIsEmpty(tree)) return;

    // Element is Not in the Tree:
    if (!binTreeSearch(tree, data)) return;

    (tree->counter)--;
    binTreeNode* result = removeElemBinTreeNode(tree->root, data, tree->compareF);
    if (result == NULL) return;
    tree->root = result;

    balanceBinTree(tree->root);
    return;
}

size_t countBinTree(binTree *tree) {
    if (!tree) return 0;
    return tree->counter;
}