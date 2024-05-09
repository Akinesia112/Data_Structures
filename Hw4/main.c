#include <stdio.h>
#include <stdlib.h>
#include "buildTree.h"

#define MAX_STACK_SIZE 100

// Iterative inorder traversal function
void iter_inorder(treeNode *node) {
    treeNode *stack[MAX_STACK_SIZE];
    int top = -1;
    treeNode *current = node;

    while (current != NULL || top != -1) {
        if (current != NULL) {
            stack[++top] = current;  // Push the node
            current = current->left;  // Move to the left child
        } else {
            current = stack[top--];  // Pop the node
            printf("%d ", current->val);  // Process the current node
            current = current->right;  // Move to the right child
        }
    }
    printf("\n");
}


int main()
{
    /* You should not edit the code here. */
    printf("Inorder Traversal of Tree 1:\n");
    treeNode *tree1 = buildTree1();
    iter_inorder(tree1);
    printf("\nInorder Traversal of Tree 2:\n");
    treeNode *tree2 = buildTree2();
    iter_inorder(tree2);
    printf("\nInorder Traversal of Tree 3:\n");
    treeNode *tree3 = buildTree3();
    iter_inorder(tree3);
    return 0;
}