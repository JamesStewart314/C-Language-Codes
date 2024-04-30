#include "genAVLBinTree.h"

// Function used to obtain the maximum value between two size_t variables:
size_t maxSize_t(size_t a, size_t b) { return (a > b) ? a : b; }


// Function used to obtain the height of a binary tree:
size_t getSubTreeHeigt(binTreeNode* subtree) {
    if (!subtree) return (size_t)0;
    return subtree->height;
}


// Function used to recalculate the height of a tree:
size_t recalculateSubTreeHeight(binTreeNode* subtree) {
    if (!subtree) return (size_t)0;
    return 1 + maxSize_t(getSubTreeHeigt(subtree->left), getSubTreeHeigt(subtree->right));
}


// Function used to calculate the balancing 
// factor of the root of an AVL binary tree:
int getSubTreeBF(binTreeNode* subtree) {
    if (!subtree) return 0;
    return (int)getSubTreeHeigt(subtree->left) - (int)getSubTreeHeigt(subtree->right);
}


// Function whose purpose is to print the binary tree symmetrically:
void impressBinTreeSymetric(binTreeNode* subtree, binTree* originalStructure) { 
    if (!subtree || !originalStructure) return; 
    if (binTreeIsEmpty(originalStructure)) return;

    impressBinTreeSymetric(subtree->left, originalStructure);
    originalStructure->printF(subtree->data); printf(" - ");
    impressBinTreeSymetric(subtree->right, originalStructure);

    return;
}


//  Function used to apply Left-Left (L.L.) 
// rotation to a given node in the AVL binary tree:
binTreeNode* rotateLLBinTree(binTreeNode* subtree) {
    if (!subtree) return NULL;
    if (!subtree->left) return NULL;

    binTreeNode* modNode = subtree->left;
    subtree->left = modNode->right;
    modNode->right = subtree;
    subtree->height -= 2;

    return modNode;
}


//  Function used to apply Right-Right (R.R.) 
// rotation to a given node in the AVL binary tree:
binTreeNode* rotateRRBinTree(binTreeNode* subtree) {
    if (!subtree) return NULL;
    if (!subtree->right) return NULL;

    binTreeNode* modNode = subtree->right;
    subtree->right = modNode->left;
    modNode->left = subtree;
    subtree->height -= 2;

    return modNode;    
}


// Function used to rebalance a binary tree if it is not balanced:
binTreeNode* balanceBinTree(binTreeNode* subtree) {
    if (!subtree) return NULL;
    if (!subtree->left && !subtree->right) return subtree;

    //  First balancing the left and right sides of the 
    // AVL binary tree, respectively:
    subtree->left = balanceBinTree(subtree->left);
    subtree->right = balanceBinTree(subtree->right);

    //  If the balance factor modulus of the Parent node 
    // is less than two, then the tree is already balanced:
    int balanceFactor = getSubTreeBF(subtree);
    if (abs(balanceFactor) < 2) return subtree;

    //  If the modulus of the balance factor is less than two, 
    // the tree is naturally balanced. Otherwise, an obvious 
    // imbalance is identified, which can be directed to the 
    // left (BF = (+2)) or to the right (BF = (-2)):

    if (balanceFactor == 2) {

        //  The tree is unbalanced to the left. In this case,
        // there are two possible scenarios: If the Parent node
        // has a Child node branching to the left and a Grandchild
        // node equally branching to the left, this arrangement
        // corresponds directly to a combination of Parent-Child
        // Balancing Factors of ((+2), (+1)), we therefore apply
        // the L.L.(Left-Left) rotation. If, on the other hand,
        // we have that the Parent node has a Son node branching to the
        // left and a Grandson node branching to the right, resulting
        // in a combination of Parent-Child Balancing Factors of
        // ((+2), (-1)), we apply the L.R.(Left-Right) rotation, 
        // which consists of a composition of the R.R.(Right-Right) 
        // rotation applied to the CHILD node followed by an 
        // L.L.(Left-Left) rotation applied to the PARENT node.

        // Calculating Child node balancing factor:
        int subBalanceFactor = getSubTreeBF(subtree->left);

        if (subBalanceFactor == 1) {
            // In the Left-Left case, we apply just one rotation:
            return rotateLLBinTree(subtree);
            
        } else if (subBalanceFactor == (-1)) {
            //  In the Left-Right case, we apply the composition of
            // rotations mentioned previously in their respective order:

            //  Within this context, given that the Child node branching
            // to the left receives a decrement of just one unit in its 
            // height, in contrast to the decrement of two units associated 
            // with the R.R. rotation, we proceed initially by increasing 
            // its height by one unit, ensuring that the result after the 
            // execution of the operations results in the expected output:
            (subtree->left->height)++;

            // Applying R.R. rotation to the CHILD node on the left:
            subtree->left = rotateRRBinTree(subtree->left);

            //  Finishing the balancing with an L.L. 
            // rotation applied to the PARENT node:
            return rotateLLBinTree(subtree);
        }

    } else if (balanceFactor == (-2)) {

        //  The tree is unbalanced to the right. In this case,
        // there are two possible scenarios: If the Parent node 
        // has a Child node branching to the right and a Grandchild 
        // branching equally to the right, this arrangement directly 
        // corresponds to a combination of Parent-Child Balance Factors 
        // of ((-2), (-1)), we therefore apply the R.R.(Right-Right) 
        // rotation. If, on the other hand, we have that the Parent node 
        // has a Child branching to the right and a Grandson node 
        // branching to the left, resulting in a combination of 
        // Parent-Child Balancing Factors of ((-2), (+1)) , we apply the 
        // R.L.(Right-Left) rotation, which consists of a composite of 
        // the L.L.(Left-Left) rotation applied to the CHILD node followed 
        // by an R.R.(Right-Right) rotation applied to the PARENT node.

        // Calculating Child node balancing factor:
        int subBalanceFactor = getSubTreeBF(subtree->right);

        if (subBalanceFactor == (-1)) {
            // In the Right-Right case, we apply just one rotation:
            return rotateRRBinTree(subtree);

        } else if (subBalanceFactor == 1) {
            //  In the Left-Right case, we apply the composition of
            // rotations mentioned previously in their respective order:

            //  Within this context, given that the Child node branching
            // to the right receives a decrement of just one unit in its
            // height, in contrast to the decrement of two units associated
            // with the L.L. rotation, we proceed initially by increasing
            // its height by one unit, ensuring that the result after the
            // execution of the operations results in the expected output:
            (subtree->right->height)++;

            // Applying L.L. rotation to the CHILD node on the right:
            subtree->right = rotateLLBinTree(subtree->right);

            //  Finishing the balancing with an R.R.
            // rotation applied to the PARENT node:
            return rotateRRBinTree(subtree);
        }
    }

    return subtree;
}


// Auxiliary function to insert a new node into the binary tree:
int binTreeInsertNode(binTreeNode* subtree, binTreeNode* newleaf, compareFunctionBinTree comparef) {

    // Comment caption:
    /*

    (1):  Error return value; There were no changes to the tree.

    (2):  In order to indicate a change in the height of the
         current tree, the value (+1) is returned. The function
         responsible for capturing this value must then proceed
         with recalculating the height of the tree in response
         to the insertion of the new node.

    (3):  For the purpose of signaling an unchanged height, we
        return the value 0 as the function's immediate response.

    */

    // (1)
    if (!subtree) return -1;

    int result = comparef(newleaf->data, subtree->data);

    // The new node to be inserted is already present in the 
    // tree, we deallocate its memory and do not insert it:
    if (result == 0) {
        free(newleaf);
        // (1)
        return -1;
    }

    if (result > 0) {
        // The node will be inserted to the 
        // right side of the current subtree.

        // If there is no subtree on the right, 
        // we allocate its new position there:
        if (!subtree->right) {
            subtree->right = newleaf;

            //  If there is no subtree to 
            // the left of the current node, 
            // its height is increased by one 
            // after the new node is inserted:
            if (!subtree->left) {
                (subtree->height)++;
                // (2)
                return 1;
            }
            // (3)
            return 0;
        }

        // Checking if there was a change in the height 
        // of the right subtree after recursive insertion:
        if (binTreeInsertNode(subtree->right, newleaf, comparef) == 1) {
            // If there was a change, we recalculate its height:
            subtree->height = recalculateSubTreeHeight(subtree);
            // (2)
            return 1;
        } 
        // (3)
        return 0;

    } else {
        // result < 0.

        // The node will be inserted to the 
        // left side of the current subtree.

        // If there is no subtree on the left,
        // we allocate its new position there:
        if (!subtree->left) {
            subtree->left = newleaf;

            //  If there is no subtree to 
            // the right of the current node,
            // its height is increased by one 
            // after the new node is inserted:
            if (!subtree->right) {
                (subtree->height)++;
                // (2)
                return 1;
            }
            // (3)
            return 0;
        }

        // Checking if there was a change in the height
        // of the left subtree after recursive insertion:
        if (binTreeInsertNode(subtree->left, newleaf, comparef) == 1) {
            // If there was a change, we recalculate its height:
            subtree->height = recalculateSubTreeHeight(subtree);
            // (2)
            return 1;
        }
        // (3)
        return 0;
    }
}


// Auxiliary function used for the purpose of recursively 
// deallocating the memory used in the binary tree:
void freeBinTreeRecursively(binTreeNode* subtree) {
    if (!subtree) return;

    if (subtree->left && !subtree->right) {
        free(subtree);
        return;
    }

    freeBinTreeRecursively(subtree->left);
    freeBinTreeRecursively(subtree->right);
    free(subtree);

    return;
}


//  Auxiliary function used for the purpose of removing a certain element 
// from the binary tree. The return value corresponds to the pointer to 
// the tree with the element removed:
binTreeNode* removeElemBinTreeNode(binTreeNode* subtree, void* data, compareFunctionBinTree compareF) {
    if (!subtree) return NULL;

    // Result of the comparison between the node's information 
    // fields and the information to be removed:
    int result = compareF(data, subtree->data);

    // The element to be removed is on the right side of the tree:
    if (result > 0) {
        // If there are no side branches, then the
        // element to be removed is not present in the tree:
        if (!subtree->right) return subtree;

        // We recursively invoke the function on the right side 
        // of the subtree and reassign the pointer returned by 
        // the remove function to preserve the modifications of 
        // the original tree:
        subtree->right = removeElemBinTreeNode(subtree->right, data, compareF);

        // Recalculating the height of the tree 
        // to correct any changes to its value:
        subtree->height = recalculateSubTreeHeight(subtree);

        return subtree;
    }

    // The element to be removed is on the left side of the tree:
    if (result < 0) {
        // If there are no side branches, then the
        // element to be removed is not present in the tree:
        if (!subtree->left) return subtree;

        // We recursively invoke the function on the left side
        // of the subtree and reassign the pointer returned by
        // the remove function to preserve the modifications of
        // the original tree:
        subtree->left = removeElemBinTreeNode(subtree->left, data, compareF);

        // Recalculating the height of the tree
        // to correct any changes to its value:
        subtree->height = recalculateSubTreeHeight(subtree);

        return subtree;
    }

    // Otherwise, Element Found.
    // Removing the element from the root:
    binTreeNode* nodeAux = subtree;
    if (!nodeAux->left) {
        // If there are no branches to the left of the root, the 
        // new root will be the Child node to the right of the root:
        binTreeNode* returnNode = nodeAux->right;
        free(nodeAux);
        return returnNode;
    }

    if (!(nodeAux->left->right)) {
        // If there are no branches to the right of the Child node to 
        // the left of the root node, the new root will be the Child 
        // node to the left of the root:
        nodeAux->left->right = nodeAux->right;
        binTreeNode* returnNode = nodeAux->left;
        free(nodeAux);
        return returnNode;
    }

    //  If none of the previously mentioned situations occur, to replace 
    // the root node while preserving the current structure of the binary
    // tree, it is necessary to locate the node with the highest value in 
    // the subtree to the left of the root and use it as the new root:
    binTreeNode *substitute = nodeAux->left, *subsParent = NULL;
    while (substitute->right) {
        // Walking the left subtree looking for 
        // the node containing the largest value:
        subsParent = substitute;
        substitute = substitute->right;
    }

    // Overwriting the content of the root node:
    subtree->data = substitute->data;
    // Removing the replacement node recursively:
    subsParent->right = removeElemBinTreeNode(substitute, substitute->data, compareF);

    return subtree;
}


// Function responsible for properly initializing an AVL 
// binary tree structure and returning a pointer to it:
binTree* initBinTree(impressFunctionBinTree printF, compareFunctionBinTree compareF) {
    
    // Allocating memory on the Heap for the new binary tree structure:
    binTree* newtree = (binTree *) malloc (sizeof(binTree));
    
    // Checking whether the allocation was successful. 
    // Otherwise, the initialization function will 
    // terminate prematurely with an error output:
    if (newtree == NULL) {
        fprintf(stderr, "Error: Failed while trying to allocate memory for a new AVL Binary Tree.\n");
        exit(EXIT_FAILURE);
    }

    // Assigning the values and pointers to their respective fields:
    newtree->printF = printF;
    newtree->compareF = compareF;
    newtree->counter = (size_t)0;
    newtree->root = NULL;
    
    return newtree;
}


// Boolean function responsible for informing 
// whether a binary tree is empty:
bool binTreeIsEmpty(binTree* tree) {
    if (!tree) return 1;
    return (tree->counter <= 0);
}


// Function responsible for displaying the 
// binary tree through a symmetric traversal:
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


//  Boolean function whose purpose is to inform whether 
// a certain element is present in the binary tree:
bool binTreeSearch(binTree* tree, void* data) {
    if (!tree) return 0;
    if (binTreeIsEmpty(tree)) return 0;

    binTreeNode* nodeAux = tree->root;
    int result;

    // Traversing the binary tree in search of the element sought:
    while (nodeAux) {
        result = tree->compareF(data, nodeAux->data);
        if (result > 0) { nodeAux = nodeAux->right; }
        if (result < 0) { nodeAux = nodeAux->left; }
        break;
    }

    // At the end of operations, there are two possibilities that the
    // content stored by the nodeAux pointer can assume: NULL or a
    // specific memory address. If nodeAux is NULL, the returned value
    // will be 0, indicating the absence of the element sought in the tree;
    // otherwise the value 1 will be returned, signaling the finding of 
    // the desired value in the tree:
    return nodeAux ? 1 : 0;
}


//  Function whose purpose is to insert elements into the binary tree. 
// It is worth highlighting the indispensability of inserting elements 
// that mutually share the same type of data, otherwise the behavior of 
// the binary tree will be unpredictable or cause a collapse in the program:
void binTreeInsert(binTree* tree, void* data) {
    if (!tree) return;

    // Allocating the amount of memory necessary to 
    // store an AVL binary tree structure on the Heap:
    binTreeNode* newleaf = (binTreeNode *) malloc (sizeof(binTreeNode));

    // Checking whether the allocation was successful.
    // Otherwise, the initialization function will
    // terminate prematurely with an error output:
    if (newleaf == NULL) {
        fprintf(stderr, "Error: Failed when trying to allocate memory for a new Leaf of the AVL Binary Tree.\n");
        exit(EXIT_FAILURE);
    }

    // Appropriately initializing the fields of the 
    // new leaf with their respective corresponding values:
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

    // Incrementing the element count of the binary tree by unit:
    (tree->counter++);

    // Rebalancing the binary tree after inserting the new element:
    tree->root = balanceBinTree(tree->root);

    return;
}


// Function whose purpose is to create and return an independent copy 
// of the binary tree provided as the function's main parameter:
binTree* binTreeCopy(binTree* tree) {
    if (!tree) return NULL;

    // Initializing the new copy of the original tree:
    binTree *newtree = initBinTree(tree->printF, tree->compareF);
    
    // If the tree is empty, simply return a new, freshly initialized binary tree:
    if (binTreeIsEmpty(tree)) return newtree;

    //  In order to create a replica identical to the original tree, it 
    // is essential to preserve the organization of the elements contained 
    // in it. To achieve this objective, a viable strategy consists of 
    // employing an auxiliary data structure - in this case, a queue - 
    // with the aim of storing the elements and inserting them in their 
    // corresponding order.
    gQueue* treeQueue = initQueue(tree->printF, tree->compareF);
    
    // We first start by enqueuing the root node of the tree.
    enqueue(treeQueue, tree->root);
    binTreeNode* tempNode;

    do {
        // Dequeuing the elements contained in the 
        // queue to insert them into the new tree:
        tempNode = (binTreeNode *)dequeue(treeQueue);

        // If there are no more elements to be enqueued, we end the loop:
        if (!tempNode) break;

        // Introducing the newly dequeued element into the new binary tree:
        binTreeInsert(newtree, tempNode->data);

        // Checking for the existence of subtrees in the 
        // newly removed node and, if so, queuing them:
        if (tempNode->right) enqueue(treeQueue, tempNode->right);
        if (tempNode->left) enqueue(treeQueue, tempNode->left);
    } while (true);

    // Deallocate memory reserved for the queue 
    // structure before terminating the function:
    freeQueue(&treeQueue);

    return newtree;
}


//  Function whose purpose is to return a pointer to the 
// largest element contained in the binary tree. If the 
// tree is empty, a pointer to NULL is returned:
void* getBiggestElemBinTree(binTree* tree) {
    if (!tree) return NULL;
    if (binTreeIsEmpty(tree)) return NULL;

    // To identify the largest element present in the tree, 
    // it is necessary to traverse it until reaching the rightmost element:
    binTreeNode* biggestElem = tree->root;
    while (biggestElem->right) biggestElem = biggestElem->right;

    return biggestElem->data;
}


//  This function returns a Boolean value for the purpose of determining 
// equality between two AVL binary trees. The criteria for establishing 
// equality between two binary trees consist of comparing the number of 
// elements contained in each tree and the arrangement of these elements 
// within the tree structure:
bool isEqualsBinTree(binTree* tree1, binTree* tree2) {

    // If at least one of the function parameters is NULL, 
    // then the trees will only be identical if both are NULL:
    if (!tree1 || !tree2) { return (!tree1 && !tree2) ? 1 : 0; }

    // If at least one of the binary trees is empty, 
    // then both trees must be empty for equality to occur:
    if (binTreeIsEmpty(tree1) || binTreeIsEmpty(tree2)) {
        return (binTreeIsEmpty(tree1) && binTreeIsEmpty(tree2)) ? 1 : 0;
    }

    // If the number of elements present in both trees 
    // differs, consequently they will not be equal:
    if (tree1->counter != tree2->counter) return 0;

    //  If the functions responsible for comparing the elements associated 
    // with binary trees are different, it is impossible to establish a 
    // coherent comparison between the trees. This way, the function is 
    // terminated immediately, without determining a precise result for comparison:
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

    freeBinTreeRecursively((*tree)->root);
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


size_t binTreeCount(binTree *tree) {
    if (!tree) return 0;
    return tree->counter;
}
