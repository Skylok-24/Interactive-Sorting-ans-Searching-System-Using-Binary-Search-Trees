

#ifndef TREES_h
#define TREES_h

struct Tree
{
    int data;
    struct Tree *left, *right;
    int height;
};

struct Tree *createNode(int value);
struct Tree *insertNode(struct Tree *root, int value);
struct Tree *findPredecessor(struct Tree *root);
struct Tree *deleteNodeWithPrecedecessor(struct Tree *root, int value);
struct Tree *findSuccessor(struct Tree *root);
struct Tree *deleteNodeWithSuccessor(struct Tree *root, int value);
void inOrderTraversal(struct Tree *root);
void freeTree(struct Tree *root);
int getHeight(struct Tree *root);
int getBalanceFactor(struct Tree *root);
struct Tree *rotateRight(struct Tree *y);
struct Tree *rotateLeft(struct Tree *y);

#endif