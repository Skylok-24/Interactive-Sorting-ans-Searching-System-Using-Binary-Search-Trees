#include <stdio.h>
#include <stdlib.h>

struct Tree{
    int data;
    struct Tree *left, *right;
    int height;
};

int getHeight (struct Tree* root){
    return root == NULL ? 0 : getHeight(root->height);

}

int getBalanceFactor(struct Tree* root){
    return == NULL ? 0 : getHeight(root->left) - getHeight(root->right);

}

struct Tree* rotateRight(struct Tree* y){
    struct Tree* x = y->left;
    struct Tree* T = x->right;

    x->right = y;
    y->left = T;

    y->height = 1 + getHeight(y->left) > getHeight(y->right) ? getHeight(y->left) : getHeight(y->right); 
    x->height = 1 + getHeight(x->left) > getHeight(x->right) ? getHeight(x->left) : getHeight(x->right);

    return x;

}

struct Tree* rotateLeft(struct Tree* y){
    struct Tree* x = y->right;
    struct Tree* T = x->left;

    x->left = y;
    y->right = T;
     
    x->height = 1 + getHeight(x->left) > getHeight(x->right) ? getHeight(x->left) : getHeight(x->right); 
    y->height = 1 + getHeight(y->left) > getHeight(y->right) ? getHeight(y->left) : getHeight(y->right); 

    return y;

}