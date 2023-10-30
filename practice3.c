#include <stdio.h>
#include <stdlib.h>

struct TreeNode{
    int key;
    struct TreeNode* left;
    struct TreeNode *right;
};

struct TreeNode *createnode(int key){
    struct TreeNode *newNode=(struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->key=key;
    newNode->left=newNode->right=NULL;
    return newNode;
}
struct TreeNode *insert(struct TreeNode* root,int key){
    if(root==NULL){
        return createnode(key);
    }
    if(key<root->key){
        root->left=insert(root)
    }
}