//
// Created by lokman-abdelmonam on 1/13/25.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "BST.h"

//************AVL*********

int getHeight(struct Tree *root)
{
    if (root == NULL)
        return 0;
    return root->height;
}

int getBalanceFactor(struct Tree *root)
{
    if (root == NULL)
        return 0;
    return getHeight(root->left) - getHeight(root->right);
}

struct Tree *rotateRight(struct Tree *y)
{
    struct Tree *x = y->left;
    struct Tree *T = x->right;

    x->right = y;
    y->left = T;

    y->height = 1 + (getHeight(y->left) > getHeight(y->right) ? getHeight(y->left) : getHeight(y->right));
    x->height = 1 + (getHeight(x->left) > getHeight(x->right) ? getHeight(x->left) : getHeight(x->right));

    return x;
}

struct Tree *rotateLeft(struct Tree *y)
{
    struct Tree *x = y->right;
    struct Tree *T = x->left;

    x->left = y;
    y->right = T;

    y->height = 1 + (getHeight(y->left) > getHeight(y->right) ? getHeight(y->left) : getHeight(y->right));
    x->height = 1 + (getHeight(x->left) > getHeight(x->right) ? getHeight(x->left) : getHeight(x->right));

    return x;
}

//***************************

struct Tree *createNode(int value)
{

    struct Tree *newNode = (struct Tree *)malloc(sizeof(struct Tree));

    if (newNode != NULL)
    {

        newNode->data = value;
        newNode->left = NULL;
        newNode->right = NULL;
        newNode->height = 1;
    }

    return newNode;
}

struct Tree *insertNode(struct Tree *root, int value)
{
    if (root == NULL)
        return createNode(value);

    if (value < root->data)
        root->left = insertNode(root->left, value);
    else if (value > root->data)
        root->right = insertNode(root->right, value);
    else
        return root;

    root->height = 1 + (getHeight(root->left) > getHeight(root->right) ?
                       getHeight(root->left) : getHeight(root->right));

    int balance = getBalanceFactor(root);

    if (balance > 1 && value < root->left->data)
        return rotateRight(root);

    if (balance < -1 && value > root->right->data)
        return rotateLeft(root);

    if (balance > 1 && value > root->left->data)
    {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    if (balance < -1 && value < root->right->data)
    {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}
struct Tree *findPredecessor(struct Tree *root)
{
    struct Tree *currnet = root->left;
    while (currnet && currnet->right)
        currnet = currnet->right;

    return currnet;
}

struct Tree *deleteNodeWithPredecessor(struct Tree *root, int value)
{
    if (root == NULL)
        return NULL;

    if (value < root->data)
        root->left = deleteNodeWithPredecessor(root->left, value);
    else if (value > root->data)
        root->right = deleteNodeWithPredecessor(root->right, value);
    else
    {
        if (root->left == NULL)
        {
            struct Tree *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            struct Tree *temp = root->left;
            free(root);
            return temp;
        }

        struct Tree *predecessor = findPredecessor(root);
        root->data = predecessor->data;
        root->left = deleteNodeWithPredecessor(root->left, predecessor->data);
    }

    if (root == NULL)
        return NULL;

    root->height = 1 + (getHeight(root->left) > getHeight(root->right) ?
                       getHeight(root->left) : getHeight(root->right));

    int balance = getBalanceFactor(root);

    if (balance > 1 && getBalanceFactor(root->left) >= 0)
        return rotateRight(root);

    if (balance > 1 && getBalanceFactor(root->left) < 0)
    {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    if (balance < -1 && getBalanceFactor(root->right) <= 0)
        return rotateLeft(root);

    if (balance < -1 && getBalanceFactor(root->right) > 0)
    {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

struct Tree *findSuccessor(struct Tree *root)
{
    struct Tree *current = root->right;
    while (current && current->left)
        current = current->left;

    return current;
}

struct Tree *deleteNodeWithSuccessor(struct Tree *root, int value)
{
    if (root == NULL)
        return NULL;

    if (value < root->data)
        root->left = deleteNodeWithSuccessor(root->left, value);
    else if (value > root->data)
        root->right = deleteNodeWithSuccessor(root->right, value);
    else
    {
        if (root->left == NULL)
        {
            struct Tree *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            struct Tree *temp = root->left;
            free(root);
            return temp;
        }

        struct Tree *successor = findSuccessor(root);
        root->data = successor->data;
        root->right = deleteNodeWithSuccessor(root->right, successor->data);
    }

    if (root == NULL)
        return NULL;

    root->height = 1 + (getHeight(root->left) > getHeight(root->right) ?
                       getHeight(root->left) : getHeight(root->right));

    int balance = getBalanceFactor(root);

    if (balance > 1 && getBalanceFactor(root->left) >= 0)
        return rotateRight(root);

    if (balance > 1 && getBalanceFactor(root->left) < 0)
    {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    if (balance < -1 && getBalanceFactor(root->right) <= 0)
        return rotateLeft(root);

    if (balance < -1 && getBalanceFactor(root->right) > 0)
    {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

void inOrderTraversal(struct Tree *root)
{
    if (root != NULL)
    {
        inOrderTraversal(root->left);
        printf("%d ", root->data);
        inOrderTraversal(root->right);
    }
}

void freeTree(struct Tree *root)
{
    if (root != NULL)
    {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

void searchNode(struct Tree *root , int value)
{
    if (root == NULL)
    {
        printf("%d not found \n",value);
        return;
    }
    if (value < root->data)
        searchNode(root->left,value);
    else if (value > root->data)
        searchNode(root->right,value);
    else {
        printf("%d found successfully \n",root->data);
        return;
    }
}
