#ifndef BUILDTREE_H
#define BUILDTREE_H

typedef struct treeNode
{
    /* You MUST use this struct when you build a binary tree. */
    /* You should not edit the code here. */
    int val;
    struct treeNode *left;
    struct treeNode *right;
} treeNode;

// If you add another function in “buildTree.c” , please declare its Function Prototype here.

treeNode *newNode(int data);
treeNode *buildTree1();
treeNode *buildTree2();
treeNode *buildTree3();

#endif