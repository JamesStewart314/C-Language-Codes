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
static inline size_t maxSize_t(size_t a, size_t b) { return (a > b) ? a : b; }


// Function used to obtain the height of a binary tree:
static inline size_t getGenAVLSubTreeHeigt(gAVLBinTreeNode* subtree) {
    if (!subtree) return (size_t)0;
    return subtree->height;
}


// Function used to recalculate the height of a tree:
size_t recalculateGenAVLSubTreeHeight(gAVLBinTreeNode* subtree) {
    if (!subtree) return (size_t)0;
    return 1 + maxSize_t(getGenAVLSubTreeHeigt(subtree->left), getGenAVLSubTreeHeigt(subtree->right));
}


// Function used to calculate the balancing 
// factor of the root of an AVL binary tree:
int getGenAVLSubTreeBF(gAVLBinTreeNode* subtree) {
    if (!subtree) return 0;
    return (int)getGenAVLSubTreeHeigt(subtree->left) - (int)getGenAVLSubTreeHeigt(subtree->right);
}


// Function whose purpose is to print the binary tree symmetrically:
void impressGenAVLBinTreeSymetric(gAVLBinTreeNode* subtree, impressFunctionGenAVLBinTree printF) { 
    if (!subtree || !printF) return; 

    impressGenAVLBinTreeSymetric(subtree->left, printF);
    printF(subtree->data); printf(", ");
    impressGenAVLBinTreeSymetric(subtree->right, printF);

    return;
}


//  Function used to apply Left-Left (L.L.) 
// rotation to a given node in the AVL binary tree:
gAVLBinTreeNode* rotateLLGenAVLBinTree(gAVLBinTreeNode* subtree) {
    if (!subtree) return NULL;
    if (!subtree->left) return NULL;

    gAVLBinTreeNode* modNode = subtree->left;
    subtree->left = modNode->right;
    modNode->right = subtree;
    subtree->height -= 2;

    return modNode;
}


//  Function used to apply Right-Right (R.R.) 
// rotation to a given node in the AVL binary tree:
gAVLBinTreeNode* rotateRRGenAVLBinTree(gAVLBinTreeNode* subtree) {
    if (!subtree) return NULL;
    if (!subtree->right) return NULL;

    gAVLBinTreeNode* modNode = subtree->right;
    subtree->right = modNode->left;
    modNode->left = subtree;
    subtree->height -= 2;

    return modNode;    
}


// Function used to rebalance a binary tree if it is not balanced:
gAVLBinTreeNode* balanceGenAVLBinTree(gAVLBinTreeNode* subtree) {
    if (!subtree) return NULL;
    if (!subtree->left && !subtree->right) return subtree;

    //  If the balance factor modulus of the Parent node 
    // is less than two, then the tree is already balanced:
    int balanceFactor = getGenAVLSubTreeBF(subtree);
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
        int subBalanceFactor = getGenAVLSubTreeBF(subtree->left);

        if (subBalanceFactor == 1) {
            // In the Left-Left case, we apply just one rotation:
            return rotateLLGenAVLBinTree(subtree);
            
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
            subtree->left = rotateRRGenAVLBinTree(subtree->left);

            //  Finishing the balancing with an L.L. 
            // rotation applied to the PARENT node:
            return rotateLLGenAVLBinTree(subtree);
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
        int subBalanceFactor = getGenAVLSubTreeBF(subtree->right);

        if (subBalanceFactor == (-1)) {
            // In the Right-Right case, we apply just one rotation:
            return rotateRRGenAVLBinTree(subtree);

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
            subtree->right = rotateLLGenAVLBinTree(subtree->right);

            //  Finishing the balancing with an R.R.
            // rotation applied to the PARENT node:
            return rotateRRGenAVLBinTree(subtree);
        }
    }

    return subtree;
}


// Auxiliary function to insert a new node 
// recursively into the binary tree:
gAVLBinTreeNode* avlBinTreeInsertNode(gAVLBinTreeNode* subtree, gAVLBinTreeNode* newleaf, gAVLBinTree* originalTree) {
    if (!subtree) return NULL;

    int result = originalTree->compareF(newleaf->data, subtree->data);

    // The new node to be inserted is already present in the 
    // tree, we deallocate its memory and do not insert it:
    if (result == 0) {
        if (originalTree->destroyF) originalTree->destroyF(newleaf->data);
        free(newleaf); newleaf = NULL;
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
        gAVLBinTreeNode* insertionResult = avlBinTreeInsertNode(subtree->right, newleaf, originalTree);
        if (insertionResult == NULL) return NULL;

        //  Assigning the result of the recursive 
        // insertion to the right side of the tree:
        subtree->right = insertionResult;
        // Recalculating height after insertion:
        subtree->height = recalculateGenAVLSubTreeHeight(subtree);

        // Returning the balanced tree:
        return balanceGenAVLBinTree(subtree);

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
        gAVLBinTreeNode* insertionResult = avlBinTreeInsertNode(subtree->left, newleaf, originalTree);
        if (insertionResult == NULL) return NULL;

        //  Assigning the result of the recursive
        // insertion to the left side of the tree:
        subtree->left = insertionResult;
        // Recalculating height after insertion:
        subtree->height = recalculateGenAVLSubTreeHeight(subtree);

        // Returning the balanced tree:
        return balanceGenAVLBinTree(subtree);
    }
}


// Auxiliary function used for the purpose of recursively 
// deallocating the memory used in the binary tree:
void avlBinTreeFreeRecursively(gAVLBinTreeNode* subtree, destroyFunctionGenAVLBinTree destroyF) {
    if (!subtree) return;

    if (subtree->left && !subtree->right) {
        if (destroyF) destroyF(subtree->data);
        free(subtree); subtree = NULL;
        return;
    }

    avlBinTreeFreeRecursively(subtree->left, destroyF);
    avlBinTreeFreeRecursively(subtree->right, destroyF);
    
    if (destroyF) destroyF(subtree->data);
    free(subtree); subtree = NULL;

    return;
}


//  Auxiliary function used for the purpose of removing a 
// certain element from the binary tree. The return value 
// corresponds to the pointer to  the tree with the element removed:
gAVLBinTreeNode* gAVLBinTreeRemoveNode(gAVLBinTreeNode* subtree, gAVLBinTrPointerData data, gAVLBinTree* originalTree) {
    if (!subtree) return NULL;

    // Result of the comparison between the node's information 
    // fields and the information to be removed:
    int result = originalTree->compareF(data, subtree->data);

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
        subtree->right = gAVLBinTreeRemoveNode(subtree->right, data, originalTree);

        // Recalculating the height of the tree 
        // to correct any changes to its value:
        subtree->height = recalculateGenAVLSubTreeHeight(subtree);

        // Rebalancing tree after removing the value and 
        // returning the tree balanced:
        return balanceGenAVLBinTree(subtree);
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
        subtree->left = gAVLBinTreeRemoveNode(subtree->left, data, originalTree);

        // Recalculating the height of the tree
        // to correct any changes to its value:
        subtree->height = recalculateGenAVLSubTreeHeight(subtree);

        //  Rebalancing tree after removing 
        // the value and returning the
        // tree balanced:
        return balanceGenAVLBinTree(subtree);
    }

    // Otherwise, Element Found.
    // Removing the element from the root:
    gAVLBinTreeNode* auxNode = subtree;
    if (!auxNode->left) {
        // If there are no branches to the left of the root, the 
        // new root will be the Child node to the right of the root:
        gAVLBinTreeNode* returnNode = auxNode->right;
        
        if (originalTree->destroyF) originalTree->destroyF(auxNode->data);
        free(auxNode); auxNode = NULL;
        
        if (returnNode != NULL) { returnNode->height = recalculateGenAVLSubTreeHeight(returnNode); }

        return balanceGenAVLBinTree(returnNode);
    }

    if (!(auxNode->left->right)) {
        // If there are no branches to the right of the Child node to 
        // the left of the root node, the new root will be the Child 
        // node to the left of the root:
        auxNode->left->right = auxNode->right;
        gAVLBinTreeNode* returnNode = auxNode->left;
        
        if (originalTree->destroyF) originalTree->destroyF(auxNode->data);
        free(auxNode); auxNode = NULL;

        if (returnNode != NULL) { returnNode->height = recalculateGenAVLSubTreeHeight(returnNode); }
        
        return balanceGenAVLBinTree(returnNode);
    }

    /*
      If none of the previously mentioned situations occur, to replace 
     the root node while preserving the current structure of the binary
     tree, it is necessary to locate the node with the highest value in 
     the subtree to the left of the root and use it as the new root:
    */
    gAVLBinTreeNode *substitute = auxNode->left, *subsParent = NULL;
    while (substitute->right) {
        // Walking the left subtree looking for 
        // the node containing the largest value:
        subsParent = substitute;
        substitute = substitute->right;
    }

    // Overwriting the content of the root node:
    subtree->data = substitute->data;
    // Removing the replacement node recursively:
    subsParent->right = gAVLBinTreeRemoveNode(substitute, substitute->data, originalTree);
    // Recalculating the height of the tree to 
    // correct for any possible changes in its 
    // value after removal:
    subsParent->height = recalculateGenAVLSubTreeHeight(subsParent);
    subsParent->right = balanceGenAVLBinTree(subsParent->right);

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
void gAVLBinTreeTextReprRecursively(gAVLBinTreeNode* subtree, impressFunctionGenAVLBinTree printF) {
    if (!printF) return;
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
    gAVLBinTreeTextReprRecursively(subtree->left, printF); printf(" ");
    gAVLBinTreeTextReprRecursively(subtree->right, printF);

    // Displaying the left side of the tree 
    // with the same color obtained previously:
    printf("\033[%dm>\033[0m", randColor);

    return;
}


// Function responsible for properly initializing an AVL 
// binary tree structure and returning a pointer to it:
gAVLBinTree* initgAVLBinTree(impressFunctionGenAVLBinTree printF, compareFunctionGenAVLBinTree compareF, destroyFunctionGenAVLBinTree destroyF) {

    if (!compareF) {
        fprintf(stderr, "Error: Compare Function is NULL when creating a new generic AVL Bin Tree.\n");
        return NULL;
    }
    
    // Allocating memory on the Heap for the new binary tree structure:
    gAVLBinTree* newtree = (gAVLBinTree *) malloc (sizeof(gAVLBinTree));
    
    // Checking whether the allocation was successful. 
    // Otherwise, the initialization function will 
    // terminate prematurely with an error output:
    if (newtree == NULL) {
        fprintf(stderr, "Error: Failed while trying to allocate memory for a new generic AVL Binary Tree.\n");
        exit(EXIT_FAILURE);
        return NULL;
    }

    // Assigning the values and pointers to their respective fields:
    newtree->counter = (size_t)0;
    newtree->root = NULL;
    newtree->printF = printF;
    newtree->compareF = compareF;
    newtree->destroyF = destroyF;

    return newtree;
}


// Boolean function responsible for informing 
// whether a binary tree is empty:
bool gAVLBinTreeIsEmpty(gAVLBinTree* tree) {
    if (!tree) return 1;
    return (tree->counter <= (size_t)0);
}


// Function responsible for displaying the 
// binary tree through a symmetric traversal:
void gAVLBinTreeImpressSymmetric(gAVLBinTree* tree) {
    if (!tree) return;
    if (!tree->printF) { printf("Unable to Display AVL Bin Tree: PrintF Function Does Not Exist.\n"); return; }

    if (gAVLBinTreeIsEmpty(tree)) {
        printf("<>");
        return;
    }

    printf("< ");
    impressGenAVLBinTreeSymetric(tree->root, tree->printF);
    printf("\b\b >");

    return;
}


//  Boolean function whose purpose is to inform whether 
// a certain element is present in the binary tree:
bool gAVLBinTreeSearch(gAVLBinTree* tree, gAVLBinTrPointerData data) {
    if (!tree) return 0;
    if (gAVLBinTreeIsEmpty(tree)) return 0;

    gAVLBinTreeNode* auxNode = tree->root;
    int result;

    // Traversing the binary tree in search of the element sought:
    while (auxNode) {
        result = tree->compareF(data, auxNode->data);
        if (result > 0) { auxNode = auxNode->right; continue; }
        if (result < 0) { auxNode = auxNode->left; continue; }

        // result == 0 => Element Found:
        return 1;
    }

    return 0;
}


/*
  Function whose purpose is to insert elements into the binary tree. 
 It is worth highlighting the indispensability of inserting elements 
 that mutually share the same type of data, otherwise the behavior of 
 the binary tree will be unpredictable or cause a collapse in the program:
*/
void gAVLBinTreeInsert(gAVLBinTree* tree, gAVLBinTrPointerData data) {
    if (!tree) return;

    // Allocating the amount of memory necessary to 
    // store an AVL binary tree structure on the Heap:
    gAVLBinTreeNode* newleaf = (gAVLBinTreeNode *) malloc (sizeof(gAVLBinTreeNode));

    // Checking whether the allocation was successful.
    // Otherwise, the initialization function will
    // terminate prematurely with an error output:
    if (newleaf == NULL) {
        fprintf(stderr, "Error: Unable to allocate memory to a new Leaf of the generic AVL Binary Tree.\n");
        exit(EXIT_FAILURE);
        return;
    }

    // Appropriately initializing the fields of the 
    // new leaf with their respective corresponding values:
    newleaf->data = data;
    newleaf->height = (size_t)1;
    newleaf->left = NULL;
    newleaf->right = NULL;

    // If the Tree is Empty:
    if (gAVLBinTreeIsEmpty(tree)) {
        (tree->counter)++;
        tree->root = newleaf;
        return;
    }

    // Inserting the New Node on the Tree:
    gAVLBinTreeNode* insertionResult = avlBinTreeInsertNode(tree->root, newleaf, tree);

    // Newnode is already in the tree:
    if (insertionResult == NULL) return;

    // Incrementing the element count of the binary tree by unit:
    (tree->counter++);

    tree->root = insertionResult;
    // Rebalancing the binary tree after inserting the new element:
    tree->root->height = recalculateGenAVLSubTreeHeight(tree->root);
    tree->root = balanceGenAVLBinTree(tree->root);

    return;
}


// Function whose purpose is to create and return an independent copy 
// of the binary tree provided as the function's main parameter:
gAVLBinTree* gAVLBinTreeCopy(gAVLBinTree* tree) {
    if (!tree) return NULL;

    // Initializing the new copy of the original tree:
    gAVLBinTree* newtree = initgAVLBinTree(tree->printF, tree->compareF, tree->destroyF);
    
    // If the tree is empty, simply return a new, freshly initialized binary tree:
    if (gAVLBinTreeIsEmpty(tree)) return newtree;

    /*
      In order to create a replica identical to the original tree, it 
     is essential to preserve the organization of the elements contained 
     in it. To achieve this objective, a viable strategy consists of 
     employing an auxiliary data structure - in this case, a queue - 
     with the aim of storing the elements and inserting them in their 
     corresponding order.
    */

    // We do not provide a function to destroy elements during stack 
    // creation in order to preserve the information contained in each element:
    gQueue* treeQueue = initgQueue(tree->printF, tree->compareF, NULL, NULL);
    
    // We first start by enqueuing the root node of the tree.
    gQueueEnqueue(treeQueue, tree->root);
    gAVLBinTreeNode* tempNode;

    do {
        // Dequeuing the elements contained in the 
        // queue to insert them into the new tree:
        tempNode = (gAVLBinTreeNode *)gQueueDequeue(treeQueue);
        // If there are no more elements to be inserted 
        // into the tree copy, we end the loop:
        if (!tempNode) break;

        // Introducing the newly dequeued element into the new binary tree:
        gAVLBinTreeInsert(newtree, tempNode->data);

        // Checking for the existence of subtrees in the 
        // newly removed node and, if so, queuing them:
        if (tempNode->right) gQueueEnqueue(treeQueue, tempNode->right);
        if (tempNode->left) gQueueEnqueue(treeQueue, tempNode->left);

    } while (true);

    // Deallocate memory reserved for the queue 
    // structure before terminating the function:
    gQueueDestroy(&treeQueue);

    return newtree;
}


//  Function whose purpose is to return a pointer to the 
// largest element contained in the binary tree. If the 
// tree is empty, a pointer to NULL is returned:
gAVLBinTrPointerData gAVLBinTreeGetBiggest(gAVLBinTree* tree) {
    if (!tree) return NULL;
    if (gAVLBinTreeIsEmpty(tree)) return NULL;

    // To identify the largest element present in the tree, 
    // it is necessary to traverse it until reaching the rightmost element:
    gAVLBinTreeNode* biggestElem = tree->root;
    while (biggestElem->right != NULL) { biggestElem = biggestElem->right; }

    return biggestElem->data;
}


//  Function whose purpose is to return a pointer to the 
// smallest element contained in the binary tree. If the 
// tree is empty, a pointer to NULL is returned:
gAVLBinTrPointerData gAVLBinTreeGetSmallest(gAVLBinTree* tree) {
    if (!tree) return NULL;
    if (gAVLBinTreeIsEmpty(tree)) return NULL;

    // To identify the smallest element present in the tree, 
    // it is necessary to traverse it until reaching the leftmost element:
    gAVLBinTreeNode* smallestElem = tree->root;
    while (smallestElem->left != NULL) { smallestElem = smallestElem->left; }

    return smallestElem->data;
}


/*
  This function returns a Boolean value for the purpose of determining 
 equality between two AVL binary trees. The criteria for establishing 
 equivalence between two binary trees consist of comparing the number of 
 elements contained in each tree and the arrangement of these elements 
 within the tree structure:
*/
bool gAVLBinTreeIsEquals(gAVLBinTree* tree1, gAVLBinTree* tree2) {

    // If at least one of the function parameters is NULL, 
    // then the trees will only be identical if both are NULL:
    if (!tree1 || !tree2) return (!tree1 && !tree2);

    /* 
      If the functions responsible for comparing the elements associated 
     with binary trees are different, it is impossible to establish a 
     coherent comparison between the trees. This way, the function is 
     terminated immediately, without determining a precise result for comparison:
    */
    if (tree1->compareF != tree2->compareF) {
        fprintf(stderr, "Error: It is not possible to compare two binary trees whose comparison functions differ from each other.\n");
        return 0;
    }


    // If at least one of the binary trees is empty, 
    // then both trees must be empty for equality to occur:
    if (gAVLBinTreeIsEmpty(tree1) || gAVLBinTreeIsEmpty(tree2)) {
        return (gAVLBinTreeIsEmpty(tree1) && gAVLBinTreeIsEmpty(tree2));
    }

    // If the number of elements present in both trees 
    // differs, consequently they will not be equal:
    if (tree1->counter != tree2->counter) return 0;

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
    impressFunctionGenAVLBinTree impFunction = tree1->printF;
    compareFunctionGenAVLBinTree compFunction = tree1->compareF;

    // Initializing two distinct Stacks to allocate the Binary Trees:
    gStack* treeStack1 = initgStack(impFunction, compFunction, NULL);
    gStack* treeStack2 = initgStack(impFunction, compFunction, NULL);

    // initially inserting the roots of the Binary Trees:
    gStackPush(treeStack1, tree1->root);
    gStackPush(treeStack2, tree2->root);

    gAVLBinTreeNode* tempNode1;
    gAVLBinTreeNode* tempNode2;

    do {
        tempNode1 = (gAVLBinTreeNode *)gStackPop(treeStack1);
        tempNode2 = (gAVLBinTreeNode *)gStackPop(treeStack2);

        // Checking whether any of the batteries 
        // have been exhausted prematurely:
        if (!tempNode1 || !tempNode2) {
            // The simultaneous exhaustion of the 
            // batteries indicates equality between 
            // the Trees:
            if (!tempNode1 && !tempNode2) break;

            // On the other hand, if this is 
            // not the case, the trees are unequal:
            gStackDestroy(&treeStack1); gStackDestroy(&treeStack2);

            return 0;
        }

        if (compFunction(tempNode1->data, tempNode2->data) != 0) {
            // The Trees differ in some element, 
            // consequently they are not the same:
            gStackDestroy(&treeStack1); gStackDestroy(&treeStack2);

            return 0;
        }

        // Inserting the remaining elements of both Trees 
        // to continue with the remaining comparisons:
        if (tempNode1->right) gStackPush(treeStack1, tempNode1->right);
        if (tempNode1->left) gStackPush(treeStack1, tempNode1->left);

        if (tempNode2->right) gStackPush(treeStack2, tempNode2->right);
        if (tempNode2->left) gStackPush(treeStack2, tempNode2->left);

    } while (true);

    // Loop fully covered, trees are the same.

    // Correctly disposing of created Stacks:
    gStackDestroy(&treeStack1); gStackDestroy(&treeStack2);

    // Finally returning the value 1 to 
    // indicate equality between the Trees:
    return 1;
}


// Function responsible for displaying in the terminal 
// a view of the AVL Binary Tree provided through a level 
// traversal of the elements contained therein:
void gAVLBinTreeImpressByLevel(gAVLBinTree* tree) {
    if (!tree) return;
    if (!tree->printF) { printf("Unable to Display AVL Bin Tree: PrintF Function Does Not Exist.\n"); return; }

    if (gAVLBinTreeIsEmpty(tree)) { printf("<>"); return; }

    /*
     In order to traverse the elements contained in the 
     AVL Binary Tree by level, we will need an auxiliary 
     structure to store and obtain the nodes in an orderly 
     manner, since the nature of this ordering (traversal by level) 
     makes the task recursively unfeasible. In this way, a generic 
     data queue will be created to perform this function and assist 
     in the execution of this task:
    */
    gQueue* treeQueue = initgQueue(tree->printF, tree->compareF, NULL, NULL);
    // initially enqueuing the root of the tree:
    gQueueEnqueue(treeQueue, tree->root);

    printf("< ");

    // Traversing the Tree elements through the 
    // Queue and displaying them orderly:
    gAVLBinTreeNode* tempNode;
    do {
        tempNode = (gAVLBinTreeNode *)gQueueDequeue(treeQueue);
        if (!tempNode) break;

        tree->printF(tempNode->data); printf(", ");

        if (tempNode->left) gQueueEnqueue(treeQueue, tempNode->left);
        if (tempNode->right) gQueueEnqueue(treeQueue, tempNode->right);
    
    } while (true);

    printf("\b\b >");

    // Deallocating the queue 
    // structure before terminating 
    // the function to avoid memory leaks:
    gQueueDestroy(&treeQueue);

    return;
}


//  Function whose purpose is to recursively free the 
// allocated memory present in the AVL Binary Tree:
void gAVLBinTreeDestroy(gAVLBinTree** treePointer) {
    if (!treePointer) return;
    if (!(*treePointer)) return;

    if (gAVLBinTreeIsEmpty(*treePointer)) {
        free(*treePointer); (*treePointer) = NULL;
        return;
    }

    avlBinTreeFreeRecursively((*treePointer)->root, (*treePointer)->destroyF);
    free(*treePointer); (*treePointer) = NULL;

    return;
}


// Function responsible for removing any element from the 
// AVL Binary Tree if it is contained therein:
void gAVLBinTreeRemove(gAVLBinTree* tree, gAVLBinTrPointerData data) {
    if (!tree) return;
    if (gAVLBinTreeIsEmpty(tree)) return;

    if (gAVLBinTreeSize(tree) == (size_t)1) {
        gAVLBinTreeNode* auxNode = tree->root;

        if (tree->compareF(auxNode->data, data) == 0) {
            if (tree->destroyF) tree->destroyF(auxNode->data);
            free(auxNode); auxNode = NULL;
            tree->root = NULL;
            tree->counter = (size_t)0;
        }

        return;
    }

    // Element is Not in the Tree:
    if (!gAVLBinTreeSearch(tree, data)) return;

    // Removing the element from the Tree:
    gAVLBinTreeNode* result = gAVLBinTreeRemoveNode(tree->root, data, tree);

    //  Performing a check to determine that the removed element was not the 
    // last one in the tree. If this condition is true, the height of the tree 
    // is recalculated and subsequently readjusted to balance:
    if (result != NULL) {
        result->height = recalculateGenAVLSubTreeHeight(result);
        result = balanceGenAVLBinTree(result);
    }

    // Assigning the removal result to the root of the Binary Tree:
    tree->root = result;
    (tree->counter)--;

    return;
}


//  Function used to inform the number of 
// elements present in an AVL binary tree:
size_t gAVLBinTreeSize(gAVLBinTree* tree) {
    if (!tree) return (size_t)0;
    return tree->counter;
}


//  Function responsible for displaying a linear textual 
// representation of the provided AVL Binary Tree on the terminal:
void gAVLBinTreeTextRepr(gAVLBinTree* tree) {
    if (!tree) return;
    if (!tree->printF) { printf("Unable to Display AVL Bin Tree: PrintF Function Does Not Exist.\n"); return; }

    if (gAVLBinTreeIsEmpty(tree)) { printf("< <> <>>"); return; }

    srand((unsigned)time(NULL));

    gAVLBinTreeTextReprRecursively(tree->root, tree->printF);
    return;
}


// Function used to obtain the height of a node in the binary tree:
long long int gAVLBinTreeGetNodeHeight(gAVLBinTree* tree, gAVLBinTrPointerData data) {
    if (!tree || gAVLBinTreeIsEmpty(tree)) return (-1);
    
    gAVLBinTreeNode* auxNode = tree->root;
    int result;

    // Searching for the element through the tree:
    while (auxNode) {
        result = tree->compareF(data, auxNode->data);

        if (result > 0) { auxNode = auxNode->right; continue; }
        if (result < 0) { auxNode = auxNode->left; continue; }

        break;

    }

    // Element is not in the tree:
    if (auxNode == NULL) return (-1);

     /*
      Subtracting one height unit to correct 
     the convention adopted at the beginning
     of this code and return the true height 
     of the searched node:
     */
    return ((long long int)getGenAVLSubTreeHeigt(auxNode) - (long long int)(1));
}