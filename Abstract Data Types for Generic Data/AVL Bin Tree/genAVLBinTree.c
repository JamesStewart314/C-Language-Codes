#include "genAVLBinTree.h"

/*

For sake of convenience, I chose to consider in this code that the height of a 
leaf in any tree is defined as one. I fully recognize that this representation 
is inconsistent with reality, since the height of a leaf is, in fact, zero. 
However, this decision was made to improve the readability, understanding and 
maintainability of the code as a whole, which facilitates various calculations 
related to the procedures performed in the tree. I apologize in advance if this 
choice may partially impair the understanding of the algorithm. 

                     Thank you for your attention!

*/

// Function used to obtain the maximum value between two size_t variables:
size_t maxSize_t(size_t a, size_t b) { return (a > b) ? a : b; }


// Function used to obtain the height of a binary tree:
size_t getSubTreeHeigt(avlBinTreeNode* subtree) {
    if (!subtree) return (size_t)0;
    return subtree->height;
}


// Function used to recalculate the height of a tree:
size_t recalculateSubTreeHeight(avlBinTreeNode* subtree) {
    if (!subtree) return (size_t)0;
    return 1 + maxSize_t(getSubTreeHeigt(subtree->left), getSubTreeHeigt(subtree->right));
}


// Function used to calculate the balancing 
// factor of the root of an AVL binary tree:
int getSubTreeBF(avlBinTreeNode* subtree) {
    if (!subtree) return 0;
    return (int)getSubTreeHeigt(subtree->left) - (int)getSubTreeHeigt(subtree->right);
}


// Function whose purpose is to print the binary tree symmetrically:
void impressBinTreeSymetric(avlBinTreeNode* subtree, impressFunctionAVLBinTree printF) { 
    if (!subtree || !printF) return; 

    impressBinTreeSymetric(subtree->left, printF);
    printF(subtree->data); printf(", ");
    impressBinTreeSymetric(subtree->right, printF);

    return;
}


//  Function used to apply Left-Left (L.L.) 
// rotation to a given node in the AVL binary tree:
avlBinTreeNode* rotateLLBinTree(avlBinTreeNode* subtree) {
    if (!subtree) return NULL;
    if (!subtree->left) return NULL;

    avlBinTreeNode* modNode = subtree->left;
    subtree->left = modNode->right;
    modNode->right = subtree;
    subtree->height -= 2;

    return modNode;
}


//  Function used to apply Right-Right (R.R.) 
// rotation to a given node in the AVL binary tree:
avlBinTreeNode* rotateRRBinTree(avlBinTreeNode* subtree) {
    if (!subtree) return NULL;
    if (!subtree->right) return NULL;

    avlBinTreeNode* modNode = subtree->right;
    subtree->right = modNode->left;
    modNode->left = subtree;
    subtree->height -= 2;

    return modNode;    
}


// Function used to rebalance a binary tree if it is not balanced:
avlBinTreeNode* balanceBinTree(avlBinTreeNode* subtree) {
    if (!subtree) return NULL;
    if (!subtree->left && !subtree->right) return subtree;

    //  If the balance factor modulus of the Parent node 
    // is less than two, then the tree is already balanced:
    int balanceFactor = getSubTreeBF(subtree);
    if (abs(balanceFactor) < 2) return subtree;

    /*
      If the modulus of the balance factor is less than two, 
     the tree is naturally balanced. Otherwise, an obvious 
     imbalance is identified, which can be directed to the 
     left (BF = (+2)) or to the right (BF = (-2)):
    */

    if (balanceFactor == 2) {
        
        /*
          The tree is unbalanced to the left. In this case,
         there are two possible scenarios: If the Parent node
         has a Child node branching to the left and a Grandchild
         node equally branching to the left, this arrangement
         corresponds directly to a combination of Parent-Child
         Balancing Factors of ((+2), (+1)), we therefore apply
         the L.L.(Left-Left) rotation. If, on the other hand,
         we have that the Parent node has a Son node branching to the
         left and a Grandson node branching to the right, resulting
         in a combination of Parent-Child Balancing Factors of
         ((+2), (-1)), we apply the L.R.(Left-Right) rotation, 
         which consists of a composition of the R.R.(Right-Right) 
         rotation applied to the CHILD node followed by an 
         L.L.(Left-Left) rotation applied to the PARENT node.
        */

        // Calculating Child node balancing factor:
        int subBalanceFactor = getSubTreeBF(subtree->left);

        if (subBalanceFactor == 1) {
            // In the Left-Left case, we apply just one rotation:
            return rotateLLBinTree(subtree);
            
        } else if (subBalanceFactor == (-1)) {
            //  In the Left-Right case, we apply the composition of
            // rotations mentioned previously in their respective order:

            /*
              Within this context, given that the Child node branching
             to the left receives a decrement of just one unit in its 
             height, in contrast to the decrement of two units associated 
             with the R.R. rotation, we proceed initially by increasing 
             its height by one unit, ensuring that the result after the 
             execution of the operations results in the expected output:
            */
            (subtree->left->height)++;

            // Applying R.R. rotation to the CHILD node on the left:
            subtree->left = rotateRRBinTree(subtree->left);

            //  Finishing the balancing with an L.L. 
            // rotation applied to the PARENT node:
            return rotateLLBinTree(subtree);
        }

    } else if (balanceFactor == (-2)) {
        
        /*
          The tree is unbalanced to the right. In this case,
         there are two possible scenarios: If the Parent node 
         has a Child node branching to the right and a Grandchild 
         branching equally to the right, this arrangement directly 
         corresponds to a combination of Parent-Child Balance Factors 
         of ((-2), (-1)), we therefore apply the R.R.(Right-Right) 
         rotation. If, on the other hand, we have that the Parent node 
         has a Child branching to the right and a Grandson node 
         branching to the left, resulting in a combination of 
         Parent-Child Balancing Factors of ((-2), (+1)) , we apply the 
         R.L.(Right-Left) rotation, which consists of a composite of 
         the L.L.(Left-Left) rotation applied to the CHILD node followed 
         by an R.R.(Right-Right) rotation applied to the PARENT node.
        */

        // Calculating Child node balancing factor:
        int subBalanceFactor = getSubTreeBF(subtree->right);

        if (subBalanceFactor == (-1)) {
            // In the Right-Right case, we apply just one rotation:
            return rotateRRBinTree(subtree);

        } else if (subBalanceFactor == 1) {
            //  In the Left-Right case, we apply the composition of
            // rotations mentioned previously in their respective order:

            /*
              Within this context, given that the Child node branching
             to the right receives a decrement of just one unit in its
             height, in contrast to the decrement of two units associated
             with the L.L. rotation, we proceed initially by increasing
             its height by one unit, ensuring that the result after the
             execution of the operations results in the expected output:
            */
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


// Auxiliary function to insert a new node 
// recursively into the binary tree:
avlBinTreeNode* avlBinTreeInsertNode(avlBinTreeNode* subtree, avlBinTreeNode* newleaf, compareFunctionAVLBinTree comparef) {
    if (!subtree) return NULL;

    int result = comparef(newleaf->data, subtree->data);

    // The new node to be inserted is already present in the 
    // tree, we deallocate its memory and do not insert it:
    if (result == 0) {
        free(newleaf);
        return NULL;
    }

    if (result > 0) {
        // The node will be inserted to the 
        // right side of the current subtree.

        // If there is no subtree on the right, 
        // we allocate its new position there:
        if (!subtree->right) {
            subtree->right = newleaf;

            /*
              If there is no subtree to 
             the left of the current node, 
             subtree's height is increased 
             by one unit after the new node 
             is inserted:
            */
            if (!subtree->left) (subtree->height)++;
            return subtree;
        }

        //  Inserting recursively into the right side of the tree. If the 
        // element already exists, the function returns NULL and no changes 
        // to the tree structure are performed:
        avlBinTreeNode* insertionResult = avlBinTreeInsertNode(subtree->right, newleaf, comparef);
        if (insertionResult == NULL) return NULL;

        //  Assigning the result of the recursive 
        // insertion to the right side of the tree:
        subtree->right = insertionResult;
        // Recalculating height after insertion:
        subtree->height = recalculateSubTreeHeight(subtree);

        // Returning the balanced tree:
        return balanceBinTree(subtree);

    } else {
        // result < 0:

        // The node will be inserted to the 
        // left side of the current subtree.

        // If there is no subtree on the left,
        // we allocate its new position there:
        if (!subtree->left) {
            subtree->left = newleaf;

            /*
              If there is no subtree to 
             the right of the current node,
             its height is increased by one 
             after the new node is inserted:
            */
            if (!subtree->right) (subtree->height)++;
            return subtree;
        }

        //  Inserting recursively into the left side of the tree. If the 
        // element already exists, the function returns NULL and no changes 
        // to the tree structure are performed:
        avlBinTreeNode* insertionResult = avlBinTreeInsertNode(subtree->left, newleaf, comparef);
        if (insertionResult == NULL) return NULL;

        //  Assigning the result of the recursive
        // insertion to the left side of the tree:
        subtree->left = insertionResult;
        // Recalculating height after insertion:
        subtree->height = recalculateSubTreeHeight(subtree);

        // Returning the balanced tree:
        return balanceBinTree(subtree);
    }
}


// Auxiliary function used for the purpose of recursively 
// deallocating the memory used in the binary tree:
void avlBinTreeFreeRecursively(avlBinTreeNode* subtree) {
    if (!subtree) return;

    if (subtree->left && !subtree->right) {
        free(subtree);
        return;
    }

    avlBinTreeFreeRecursively(subtree->left);
    avlBinTreeFreeRecursively(subtree->right);
    free(subtree);

    return;
}


//  Auxiliary function used for the purpose of removing a 
// certain element from the binary tree. The return value 
// corresponds to the pointer to  the tree with the element removed:
avlBinTreeNode* avlBinTreeRemoveElemNode(avlBinTreeNode* subtree, void* data, compareFunctionAVLBinTree compareF) {
    if (!subtree) return NULL;

    // Result of the comparison between the node's information 
    // fields and the information to be removed:
    int result = compareF(data, subtree->data);

    // The element to be removed is on the right side of the tree:
    if (result > 0) {
        // If there are no side branches, then the
        // element to be removed is not present in the tree:
        if (!subtree->right) return subtree;

        /*
         We recursively invoke the function on the right side 
         of the subtree and reassign the pointer returned by 
         the remove function to preserve the modifications of 
         the original tree:
        */
        subtree->right = avlBinTreeRemoveElemNode(subtree->right, data, compareF);

        // Recalculating the height of the tree 
        // to correct any changes to its value:
        subtree->height = recalculateSubTreeHeight(subtree);

        // Rebalancing tree after removing the value and 
        // returning the tree balanced:
        return balanceBinTree(subtree);
    }

    // The element to be removed is on the left side of the tree:
    if (result < 0) {
        // If there are no side branches, then the
        // element to be removed is not present in the tree:
        if (!subtree->left) return subtree;

        /*
         We recursively invoke the function on the left side
         of the subtree and reassign the pointer returned by
         the remove function to preserve the modifications of
         the original tree:
        */
        subtree->left = avlBinTreeRemoveElemNode(subtree->left, data, compareF);

        // Recalculating the height of the tree
        // to correct any changes to its value:
        subtree->height = recalculateSubTreeHeight(subtree);

        //  Rebalancing tree after removing 
        // the value and returning the
        // tree balanced:
        return balanceBinTree(subtree);
    }

    // Otherwise, Element Found.
    // Removing the element from the root:
    avlBinTreeNode* nodeAux = subtree;
    if (!nodeAux->left) {
        // If there are no branches to the left of the root, the 
        // new root will be the Child node to the right of the root:
        avlBinTreeNode* returnNode = nodeAux->right;
        free(nodeAux); nodeAux = NULL;
        if (returnNode != NULL) { returnNode->height = recalculateSubTreeHeight(returnNode); }

        return balanceBinTree(returnNode);
    }

    if (!(nodeAux->left->right)) {
        // If there are no branches to the right of the Child node to 
        // the left of the root node, the new root will be the Child 
        // node to the left of the root:
        nodeAux->left->right = nodeAux->right;
        avlBinTreeNode* returnNode = nodeAux->left;
        free(nodeAux); nodeAux = NULL;
        if (returnNode != NULL) { returnNode->height = recalculateSubTreeHeight(returnNode); }
        
        return balanceBinTree(returnNode);
    }

    /*
      If none of the previously mentioned situations occur, to replace 
     the root node while preserving the current structure of the binary
     tree, it is necessary to locate the node with the highest value in 
     the subtree to the left of the root and use it as the new root:
    */
    avlBinTreeNode *substitute = nodeAux->left, *subsParent = NULL;
    while (substitute->right) {
        // Walking the left subtree looking for 
        // the node containing the largest value:
        subsParent = substitute;
        substitute = substitute->right;
    }

    // Overwriting the content of the root node:
    subtree->data = substitute->data;
    // Removing the replacement node recursively:
    subsParent->right = avlBinTreeRemoveElemNode(substitute, substitute->data, compareF);
    // Recalculating the height of the tree to 
    // correct for any possible changes in its 
    // value after removal:
    subsParent->height = recalculateSubTreeHeight(subsParent);
    subsParent->right = balanceBinTree(subsParent->right);

    return subtree;
}


/*
     This function is used to generate a linear textual representation 
     of the binary tree directly in the terminal. The interpretation of 
  this representation is carried out according to the following structure:

       <(root content) <(left side subtree)> <(right side subtree)>>

    When the displayed node corresponds to a leaf in the tree, its textual 
                          representation will be :

                         <(leaf node content) <> <>>

    Additionally, I implemented a color application on the side delimiters 
       of each tree to help identify the beginning and end of each tree, 
     respectively. Following this convention, empty trees - that is, trees 
   whose representation corresponds to < <> <>>, or simply <> - will always 
     be colored white, aiming to avoid a visual overload of colors in the 
                          tree representation.
*/
void binTreeTextReprRecursively(avlBinTreeNode* subtree, impressFunctionAVLBinTree printF) {
    if (!subtree) { printf("<>"); return; }

    /*
      Drawing a random number between 31 and 36 - with inclusive limits -
     to represent a bounding color combination for the current tree. 
     The color representation is given by the following values, respectively:
     31: Red ; 32: Green ; 33: Yellow ; 34: Blue ; 35: Magenta ; 36: Cyan.
    */
    
    int randColor = (rand() % 6) + 31;

    //  Using ANSI codes to change the color of 
    // the tree border with the random number 
    // obtained previously:
    printf("\033[%dm<\033[0m", randColor);

    // Displaying the information contained 
    // in the tree node:
    printF(subtree->data); printf(" ");

    // Recursively displaying the sides of the tree:
    binTreeTextReprRecursively(subtree->left, printF); printf(" ");
    binTreeTextReprRecursively(subtree->right, printF);

    // Displaying the left side of the tree 
    // with the same color obtained previously:
    printf("\033[%dm>\033[0m", randColor);

    return;
}


// Function responsible for properly initializing an AVL 
// binary tree structure and returning a pointer to it:
avlBinTree* initAVLBinTree(impressFunctionAVLBinTree printF, compareFunctionAVLBinTree compareF) {
    
    // Allocating memory on the Heap for the new binary tree structure:
    avlBinTree* newtree = (avlBinTree *) malloc (sizeof(avlBinTree));
    
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
bool avlBinTreeIsEmpty(avlBinTree* tree) {
    if (!tree) return 1;
    return (tree->counter <= 0);
}


// Function responsible for displaying the 
// binary tree through a symmetric traversal:
void avlBinTreeImpress(avlBinTree* tree) {
    if (!tree) return;
    if (avlBinTreeIsEmpty(tree)) {
        printf("<>");
        return;
    }

    printf("< ");
    impressBinTreeSymetric(tree->root, tree->printF);
    printf("\b\b >");
    return;
}


//  Boolean function whose purpose is to inform whether 
// a certain element is present in the binary tree:
bool avlBinTreeSearch(avlBinTree* tree, void* data) {
    if (!tree) return 0;
    if (avlBinTreeIsEmpty(tree)) return 0;

    avlBinTreeNode* nodeAux = tree->root;
    int result;

    // Traversing the binary tree in search of the element sought:
    while (nodeAux) {
        result = tree->compareF(data, nodeAux->data);
        if (result > 0) { nodeAux = nodeAux->right; continue; }
        if (result < 0) { nodeAux = nodeAux->left; continue; }

        // result == 0 => Element Found:
        break;
    }

    /*
     At the end of operations, there are two possibilities that the
     content stored by the nodeAux pointer can assume: NULL or a
     specific memory address. If nodeAux is NULL, the returned value
     will be 0, indicating the absence of the element sought in the tree;
     otherwise the value 1 will be returned, signaling the finding of 
     the desired value in the tree:
    */
    return ((nodeAux != NULL) ? 1 : 0);
}


/*
  Function whose purpose is to insert elements into the binary tree. 
 It is worth highlighting the indispensability of inserting elements 
 that mutually share the same type of data, otherwise the behavior of 
 the binary tree will be unpredictable or cause a collapse in the program:
*/
void avlBinTreeInsert(avlBinTree* tree, void* data) {
    if (!tree) return;

    // Allocating the amount of memory necessary to 
    // store an AVL binary tree structure on the Heap:
    avlBinTreeNode* newleaf = (avlBinTreeNode *) malloc (sizeof(avlBinTreeNode));

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
    if (avlBinTreeIsEmpty(tree)) {
        (tree->counter)++;
        tree->root = newleaf;
        return;
    }

    // Inserting the New Node on the Tree:
    avlBinTreeNode* insertionResult = avlBinTreeInsertNode(tree->root, newleaf, tree->compareF);

    // Newnode is already in the tree:
    if (insertionResult == NULL) return;

    // Incrementing the element count of the binary tree by unit:
    (tree->counter++);

    tree->root = insertionResult;
    // Rebalancing the binary tree after inserting the new element:
    tree->root->height = recalculateSubTreeHeight(tree->root);
    tree->root = balanceBinTree(tree->root);

    return;
}


// Function whose purpose is to create and return an independent copy 
// of the binary tree provided as the function's main parameter:
avlBinTree* avlBinTreeCopy(avlBinTree* tree) {
    if (!tree) return NULL;

    // Initializing the new copy of the original tree:
    avlBinTree* newtree = initAVLBinTree(tree->printF, tree->compareF);
    
    // If the tree is empty, simply return a new, freshly initialized binary tree:
    if (avlBinTreeIsEmpty(tree)) return newtree;

    /*
      In order to create a replica identical to the original tree, it 
     is essential to preserve the organization of the elements contained 
     in it. To achieve this objective, a viable strategy consists of 
     employing an auxiliary data structure - in this case, a queue - 
     with the aim of storing the elements and inserting them in their 
     corresponding order.
    */
    gQueue* treeQueue = initQueue(tree->printF, tree->compareF);
    
    // We first start by enqueuing the root node of the tree.
    enqueue(treeQueue, tree->root);
    avlBinTreeNode* tempNode;

    do {
        // Dequeuing the elements contained in the 
        // queue to insert them into the new tree:
        tempNode = (avlBinTreeNode *)dequeue(treeQueue);

        // If there are no more elements to be enqueued, we end the loop:
        if (!tempNode) break;

        // Introducing the newly dequeued element into the new binary tree:
        avlBinTreeInsert(newtree, tempNode->data);

        // Checking for the existence of subtrees in the 
        // newly removed node and, if so, queuing them:
        if (tempNode->right) enqueue(treeQueue, tempNode->right);
        if (tempNode->left) enqueue(treeQueue, tempNode->left);

    } while (tempNode);

    // Deallocate memory reserved for the queue 
    // structure before terminating the function:
    freeQueue(&treeQueue);

    return newtree;
}


//  Function whose purpose is to return a pointer to the 
// largest element contained in the binary tree. If the 
// tree is empty, a pointer to NULL is returned:
void* avlBinTreeGetBiggestElem(avlBinTree* tree) {
    if (!tree) return NULL;
    if (avlBinTreeIsEmpty(tree)) return NULL;

    // To identify the largest element present in the tree, 
    // it is necessary to traverse it until reaching the rightmost element:
    avlBinTreeNode* biggestElem = tree->root;
    while (biggestElem->right != NULL) { biggestElem = biggestElem->right; }

    return biggestElem->data;
}


/*
  This function returns a Boolean value for the purpose of determining 
 equality between two AVL binary trees. The criteria for establishing 
 equivalence between two binary trees consist of comparing the number of 
 elements contained in each tree and the arrangement of these elements 
 within the tree structure:
*/
bool avlBinTreeIsEquals(avlBinTree* tree1, avlBinTree* tree2) {

    // If at least one of the function parameters is NULL, 
    // then the trees will only be identical if both are NULL:
    if (!tree1 || !tree2) { return (!tree1 && !tree2) ? 1 : 0; }

    // If at least one of the binary trees is empty, 
    // then both trees must be empty for equality to occur:
    if (avlBinTreeIsEmpty(tree1) || avlBinTreeIsEmpty(tree2)) {
        return (avlBinTreeIsEmpty(tree1) && avlBinTreeIsEmpty(tree2)) ? 1 : 0;
    }

    // If the number of elements present in both trees 
    // differs, consequently they will not be equal:
    if (tree1->counter != tree2->counter) return 0;

    /* 
      If the functions responsible for comparing the elements associated 
     with binary trees are different, it is impossible to establish a 
     coherent comparison between the trees. This way, the function is 
     terminated immediately, without determining a precise result for comparison:
    */
    if (tree1->compareF != tree2->compareF) {
        fprintf(stderr, "Error: It is not possible to compare two binary trees whose comparison functions differ from each other.\n");
        exit(EXIT_FAILURE);
    }

    /*
      In order to check equality between two Binary Trees, we must 
     traverse their elements simultaneously in the same order and 
     proportion. To make this task feasible, we will be resorting to 
     the use of auxiliary data structures - specifically, two Stacks 
     that store generic data types. Each Stack will be responsible for 
     storing and providing the elements of one, and only one, Binary Tree.
     Upon detection of any disparity in the arrangement of elements between
     the Trees, the stacks will be immediately discarded and the function 
     will return 1 to indicate the equivalence between them. On the other 
     hand, if any of the stacks are exhausted prematurely, the function 
     will return the value 0, signaling inequality between the structures.
    */

    // Extracting the element display and comparison 
    // functions from Binary Trees to initialize Stacks:
    impressFunctionAVLBinTree impFunction = tree1->printF;
    compareFunctionAVLBinTree compFunction = tree1->compareF;

    // Initializing two distinct Stacks to allocate the Binary Trees:
    gStack* treeStack1 = stInit(impFunction, compFunction);
    gStack* treeStack2 = stInit(impFunction, compFunction);

    // initially inserting the roots of the Binary Trees:
    stPush(treeStack1, tree1->root);
    stPush(treeStack2, tree2->root);

    avlBinTreeNode* tempNode1;
    avlBinTreeNode* tempNode2;

    do {
        tempNode1 = (avlBinTreeNode *)stPop(treeStack1);
        tempNode2 = (avlBinTreeNode *)stPop(treeStack2);

        // Checking whether any of the batteries 
        // have been exhausted prematurely:
        if (!tempNode1 || !tempNode2) {
            // The simultaneous exhaustion of the 
            // batteries indicates equality between 
            // the Trees:
            if (!tempNode1 && !tempNode2) break;

            // On the other hand, if this is 
            // not the case, the trees are unequal:
            stDestroy(&treeStack1); stDestroy(&treeStack2);

            return 0;
        }

        if (compFunction(tempNode1->data, tempNode2->data) != 0) {
            // The Trees differ in some element, 
            // consequently they are not the same:
            stDestroy(&treeStack1); stDestroy(&treeStack2);

            return 0;
        }

        // Inserting the remaining elements of both Trees 
        // to continue with the remaining comparisons:
        if (tempNode1->right) stPush(treeStack1, tempNode1->right);
        if (tempNode1->left) stPush(treeStack1, tempNode1->left);

        if (tempNode2->right) stPush(treeStack2, tempNode2->right);
        if (tempNode2->left) stPush(treeStack2, tempNode2->left);

    } while (true);

    // Loop fully covered, trees are the same.

    // Correctly disposing of created Stacks:
    stDestroy(&treeStack1); stDestroy(&treeStack2);

    // Finally returning the value 1 to 
    // indicate equality between the Trees:
    return 1;
}


// Function responsible for displaying in the terminal 
// a view of the AVL Binary Tree provided through a level 
// traversal of the elements contained therein:
void avlBinTreeimpressByLevel(avlBinTree* tree) {
    if (!tree) return;
    if (avlBinTreeIsEmpty(tree)) { printf("<>"); return; }

    /*
     In order to traverse the elements contained in the 
     AVL Binary Tree by level, we will need an auxiliary 
     structure to store and obtain the nodes in an orderly 
     manner, since the nature of this ordering (traversal by level) 
     makes the task recursively unfeasible. In this way, a generic 
     data queue will be created to perform this function and assist 
     in the execution of this task:
    */
    gQueue* treeQueue = initQueue(tree->printF, tree->compareF);
    // initially enqueuing the root of the tree:
    enqueue(treeQueue, tree->root);

    printf("< ");

    // Traversing the Tree elements through the 
    // Queue and displaying them orderly:
    avlBinTreeNode* tempNode;
    do {
        tempNode = (avlBinTreeNode *)dequeue(treeQueue);
        if (!tempNode) break;

        tree->printF(tempNode->data);
        printf(", ");

        if (tempNode->left) enqueue(treeQueue, tempNode->left);
        if (tempNode->right) enqueue(treeQueue, tempNode->right);
    
    } while (tempNode);

    printf("\b\b >");

    // Deallocating the queue 
    // structure before terminating 
    // the function to avoid memory leaks:
    freeQueue(&treeQueue);


    return;
}


//  Function whose purpose is to recursively free the 
// allocated memory present in the AVL Binary Tree:
void avlBinTreeDestroy(avlBinTree** tree) {
    if (!tree) return;
    if (!(*tree)) return;

    if (avlBinTreeIsEmpty(*tree)) {
        free(*tree); (*tree) = NULL;
        return;
    }

    avlBinTreeFreeRecursively((*tree)->root);
    free(*tree); (*tree) = NULL;

    return;
}


// Function responsible for removing any element from the 
// AVL Binary Tree if it is contained therein:
void avlBinTreeRemoveElem(avlBinTree* tree, void* data) {
    if (!tree) return;
    if (avlBinTreeIsEmpty(tree)) return;

    // Element is Not in the Tree:
    if (!avlBinTreeSearch(tree, data)) return;

    // Removing the element from the Tree:
    avlBinTreeNode* result = avlBinTreeRemoveElemNode(tree->root, data, tree->compareF);

    //  Performing a check to determine that the removed element was not the 
    // last one in the tree. If this condition is true, the height of the tree 
    // is recalculated and subsequently readjusted to balance:
    if (result != NULL) {
        result->height = recalculateSubTreeHeight(result);
        result = balanceBinTree(result);
    }

    // Assigning the removal result to the root of the Binary Tree:
    tree->root = result;
    (tree->counter)--;

    return;
}


//  Function used to inform the number of 
// elements present in an AVL binary tree:
size_t avlBinTreeCount(avlBinTree *tree) {
    if (!tree) return 0;
    return tree->counter;
}


//  Function responsible for displaying a linear textual 
// representation of the provided AVL Binary Tree on the terminal:
void avlBinTreeTextRepr(avlBinTree* tree) {
    if (!tree) return;
    if (avlBinTreeIsEmpty(tree)) { printf("< <> <>>"); return; }

    srand((unsigned)time(NULL));

    binTreeTextReprRecursively(tree->root, tree->printF);
    return;
}


// Function used to obtain the height
// of a node in the binary tree:
long long int avlBinTreeGetNodeHeight(avlBinTree* tree, void* data) {
    if (!tree || avlBinTreeIsEmpty(tree)) return (-1);
    
    avlBinTreeNode* auxNode = tree->root;
    int result;

    // Searching for the element through the tree:
    do {
        result = tree->compareF(data, auxNode->data);

        if (result > 0) { auxNode = auxNode->right; continue; }
        if (result < 0) { auxNode = auxNode->left; continue; }
        break;

    } while (auxNode);

    // Element is not in the tree:
    if (auxNode == NULL) return (-1);

    /*
      Subtracting one height unit to correct 
     the convention adopted at the beginning
     of this code and return the true height 
     of the searched node:
    */
    return ((long long int)getSubTreeHeigt(auxNode) - (long long int)(1));
}