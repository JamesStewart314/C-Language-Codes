#include "BST_H.h"

compareFunction cfunc;
impressFunction ifunc;

BST *createBST(compareFunction compfFunc, impressFunction impFunc)
{
    cfunc = compfFunc;
    ifunc = impFunc;
    return NULL;
}

BST *createNodeBST(BST *tree, type element)
{
    BST *newtree = (BST *)malloc(sizeof(BST));
    newtree->data = element;
    newtree->left = NULL;
    newtree->right = NULL;

    if (!tree)
        return newtree;
    BST *auxtree = tree;
    int result;

    while (auxtree)
    {
        result = cfunc(element, auxtree->data);
        if (result == 0)
            return tree;

        if (result > 0)
        {
            if (auxtree->right == NULL)
            {
                auxtree->right = newtree;
                return tree;
            }
            auxtree = auxtree->right;
        }
        else
        {
            if (auxtree->left == NULL)
            {
                auxtree->left = newtree;
                return tree;
            }
            auxtree = auxtree->left;
        }
    }
    return NULL;
}

BST *removeNodeBST(BST *tree, type element)
{
    if (!tree)
        return NULL;
    int result;
    BST *auxtree = tree, *parent = NULL;

    do
    {
        result = cfunc(element, auxtree->data);

        // Traversing the tree until you find the desired element:
        if (result < 0)
        {
            // The element is on the left side:
            if (auxtree->left == NULL)
                return tree;
            parent = auxtree;
            auxtree = auxtree->left;
        }
        else if (result > 0)
        {
            // The element is on the right side:
            if (auxtree->right == NULL)
                return tree;
            parent = auxtree;
            auxtree = auxtree->right;
        }
    } while (result != 0);

    // Element found, now remove it:
    // Case 1, removing a leaf:
    if ((!auxtree->left) && (!auxtree->right))
    {
        if (!parent)
        {
            free(auxtree);
            auxtree = NULL;
            return NULL;
        }

        if (parent->right == auxtree)
            parent->right = NULL;
        if (parent->left == auxtree)
            parent->left = NULL;

        free(auxtree);
        auxtree = NULL;

        return tree;
    }

    // Case 2, removing the root:
    if (!parent)
    {
        // if there is no left subtree:
        if (!auxtree->left)
        {
            BST *temp = auxtree->right;
            free(auxtree);
            return temp;
        }

        //
        // Searching for the largest element to the left of the binary search tree:
        //
        BST *substitute = auxtree->left, *subsparent = NULL;
        while (substitute->right != NULL)
        {
            subsparent = substitute;
            substitute = substitute->right;
        }

        // If the largest element is the first subtree on the left:
        if (!subsparent)
        {
            tree->left = tree->left->left;
            tree->data = substitute->data;

            free(substitute);
            substitute = NULL;

            return tree;
        }

        tree->data = substitute->data;
        subsparent->right = substitute->left;

        free(substitute);
        substitute = NULL;

        return tree;
    }

    // Case 3, removing a subtree:
    // Removing subtree from right of auxtree parent:
    if (parent->right == auxtree)
    {
        parent->right = removeNodeBST(auxtree, auxtree->data);
    }
    else
    {
        // Removing subtree from left of auxtree parent:
        parent->left = removeNodeBST(auxtree, auxtree->data);
    }

    return tree;
}

void impressBST(BST *tree)
{
    if (!tree)
        return;
    impressBST(tree->left);
    ifunc(tree->data);
    impressBST(tree->right);
}

int isBinaryTree(BST *tree)
{
    if (!tree)
        return 1;
    if ((!tree->right) && (!tree->left))
        return 1;

    // Checking if the left side and right side are both binary search trees:
    if (isBinaryTree(tree->right) && isBinaryTree(tree->left))
    {
        // Checking if the ordering of values is correct for the RIGHT side:
        if (tree->right)
        {
            if (cfunc(tree->right->data, tree->data) <= 0)
                return 0;
        }

        // Checking if the ordering of values is correct for the LEFT side:
        if (tree->left)
        {
            if (cfunc(tree->left->data, tree->data) >= 0)
                return 0;
        }
        return 1;
    }
    else
        return 0;
}