#include <stdio.h>
#include <stdlib.h>

struct TreeNode{
    int key;
    struct TreeNode* left;
    struct TreeNode *right;
}

struct TreeNode *createnode(int key){
    struct TreeNode *newwNode=(struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->key=key;
    newNode->left=newNode->right=NULL;
    return newNode;
    
}