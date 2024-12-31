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
        printf("\033[1;34m\nMenu:\033[0m\n");
        printf("\033[1;32m1. Add Node\033[0m\n");
        printf("\033[1;32m2. Search for a Node\033[0m\n");
        printf("\033[1;32m3. Delete Node\033[0m\n");
        printf("\033[1;32m4. Display the content of the tree\033[0m\n");
        printf("\033[1;32m5. Exit\033[0m\n");
        printf("\033[1;34mChoice: \033[0m");
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