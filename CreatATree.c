#include <stdio.h>
#include <stdlib.h>

struct Tree {
    int data;
    struct Tree* left;
    struct Tree* right;
};

struct Tree* createNode(int value) {

    struct Tree* newNode = (struct Tree*)malloc(sizeof(struct Tree));

    if (newNode != NULL) {
        
        newNode->data = value;
        newNode->left = NULL;
        newNode->right = NULL;
    }

    return newNode;
}

struct Tree* insertNode(struct Tree* root, int value) {
    
    if (root == NULL) {
        return createNode(value);
    }

    if (value < root->data) {
        root->left = insertNode(root->left, value);
    }
    else if (value > root->data) {
        root->right = insertNode(root->right, value);
    }

    return root;
}

struct Tree *findPredecessor(struct Tree *root){
    struct Tree *currnet = root->left;
    while (currnet && currnet->right)
        currnet = currnet->right;

    return currnet;
}

struct Tree *deleteNodeWithPrecedecessor(struct Tree *root , int value){
    if(root == NULL) return NULL;

    if(value < root->data)
        root->left = deleteNodeWithPrecedecessor(root->left , value);
    else if (value > root->data)
        root->right = deleteNodeWithPrecedecessor(root->right , value);
    else {

        if(root->left == NULL){
            struct Tree *temp = root->right;
            free(root);
            return temp;
        }
        else if(root->right == NULL){
            struct Tree* temp = root->left;
            free(root);
            return temp;
        }
        struct Tree* predecessor = findPredecessor(root);
        root->data = predecessor->data;
        root->left = deleteNodeWithPrecedecessor(root->left, predecessor->data);

    }

    return root;
    
}

struct Tree* findSuccessor(struct Tree* root){
    struct Tree* current = root->right;
    while(current && current->left)
        current = current->left;
    
    return current;
}


struct Tree* deleteNodeWithSuccessor(struct Tree* root ,int value){
  if(!root) return NULL;

  if (value < root->data)
        root->left =  deleteNodeWithSuccessor(root->left ,value);
    else if (value > root->data)
        root->right =  deleteNodeWithSuccessor(root->right ,value); 
  else {
    if (!root->left){
        struct Tree* temp = root->right;
        free(root);
        return temp;

    }

    else if(!root->right){
        struct Tree* temp = root->left;
        free(root);
        return temp;

    }

    struct Tree* successor = findSuccessor(root);
    root->data = successor->data;
    root->right = deleteNodeWithSuccessor(root->right ,successor->data);

  }
  
  return root;
  
}

void inOrderTraversal(struct Tree* root) {
    if (root != NULL) {
        inOrderTraversal(root->left);
        printf("%d ", root->data);
        inOrderTraversal(root->right);
    }
}



void freeTree(struct Tree* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

int main() {

    struct Tree* root = NULL;
    
    int nodeValue;
    char choice;

    do {
        printf("Input a value to insert into the binary tree: ");
        scanf("%d", &nodeValue);

        root = insertNode(root, nodeValue);

        printf("Want to insert another node? (y/n): ");
        scanf(" %c", &choice);

    } while (choice == 'y' || choice == 'Y');

    printf("\nIn-order Traversal of the Binary Tree: ");
    inOrderTraversal(root);
    printf("\n");

    do {
        printf("Input a value to deleted into the binary tree: ");
        scanf("%d", &nodeValue);
        printf("Want to insert another node? (y/n): ");
        scanf(" %c", &choice);

    } while (choice == 'y' || choice == 'Y');
    

    freeTree(root);
    return 0;
}