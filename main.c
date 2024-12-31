#include <stdio.h>
#include <stdlib.h>
#include "Trees.h"

int main()
{
    struct Tree *root = NULL;

    int nodeValue;
    char choice;

    do
    {
        printf("Input a value to insert into the binary tree: ");
        scanf("%d", &nodeValue);

        root = insertNode(root, nodeValue);

        printf("Want to insert another node? (y/n): ");
        scanf(" %c", &choice);

    } while (choice == 'y' || choice == 'Y');

    printf("\nIn-order Traversal of the Binary Tree: ");
    inOrderTraversal(root);
    printf("\n");

    do
    {
        printf("Input a value to deleted into the binary tree: ");
        scanf("%d", &nodeValue);
        printf("Want to insert another node? (y/n): ");
        scanf(" %c", &choice);

    } while (choice == 'y' || choice == 'Y');

    freeTree(root);
    return 0;
}