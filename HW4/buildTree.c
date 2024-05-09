#include <stdio.h>
#include <stdlib.h>
#include "buildTree.h"

treeNode *newNode(int data)
{
    treeNode *node = (treeNode *)malloc(sizeof(treeNode));
    node->val = data;
    node->left = node->right = NULL;
    return node;
}

treeNode *buildTree1() {
    /* Build Tree 1 in this function and return the root. */
    treeNode *root = newNode(20);
    root->left = newNode(17);
    root->left->left = newNode(12);
    root->left->left->left = newNode(9);
    root->right = newNode(31);
    root->right->left = newNode(22);
    return root;
}

treeNode *buildTree2() {
    /* Build Tree 2 in this function and return the root. */
    treeNode *root = newNode(21);
    root->left = newNode(5);
    root->right = newNode(25);
    root->left->right = newNode(8);
    root->left->right->left = newNode(7);
    root->left->right->right = newNode(15);    
    root->right->left = newNode(23);
    return root;
}


treeNode *buildTree3() {
    /* Build Tree 3 in this function and return the root. */
    treeNode *root = newNode(12);
    root->left = newNode(3);
    root->right = newNode(25);
    root->left->right = newNode(8);
    root->left->right->right = newNode(9);
    root->right->left = newNode(16);
    root->right->right = newNode(30);
    root->right->right->right = newNode(39);
    return root;
}
