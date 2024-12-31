#include <stdio.h>
#include <stdlib.h>
#include "Trees.h"

int main()
{
    struct Tree *root = NULL;
    int nodeValue;
    int choice;

    do {
        // Menu
        printf("\nMenu:\n");
        printf("1. Add Node\n");
        printf("2. Search for a Node\n");
        printf("3. Delete Node\n");
        printf("4. Display the content of the tree\n");
        printf("5. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                printf("Enter the value: ");
                scanf("%d", &nodeValue);
                root = insertNode(root, nodeValue);
                break;
            }

            case 2: {
                printf("Enter the value of the node: ");
                scanf("%d", &nodeValue);
                searchNode(root, nodeValue);
                break;
            }

            case 3: {
                printf("Enter the value: ");
                scanf("%d", &nodeValue);
                if (nodeValue < root->data)
                    root = deleteNodeWithPrecedecessor(root, nodeValue);
                else if (nodeValue > root->data)
                    root = deleteNodeWithSuccessor(root, nodeValue);
                else
                {
                    root = deleteNodeWithSuccessor(root->right, nodeValue);
                }
                break;
            }

            case 4:
                if (root == NULL) {
                    printf("The tree is empty.\n");
                } else {
                    printf("Tree contents: ");
                    inOrderTraversal(root);
                    printf("\n");
                }
            break;

            case 5:
                printf("Goodbye.\n");
            break;

            default:
                printf("Invalid choice.\n");
        }

        printf("Press enter to continue ...");
        getchar();
        getchar();

    } while (choice != 5);

    freeTree(root);
    return 0;
}