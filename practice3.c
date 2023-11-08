#include <stdio.h>
#include <stdlib.h>

struct TreeNode{
    int key;
    struct TreeNode* left;
    struct TreeNode *right;
};

struct TreeNode* createnode(int key){
    struct TreeNode *newNode=malloc(sizeof(struct TreeNode));
    newNode->key=key;
    newNode->left=newNode->right=NULL;
    return newNode;
}

struct TreeNode* insert(struct TreeNode* root,int key){
    if(root==NULL){
        return createnode(key);
    }
    if(key<root->key){
        root->left=insert(root->left,key);
    }
    else if(key>root->key){
        root->right=insert(root->right,key);
    }
    return root;
}

void preorderTraversal(struct TreeNode *root){
    if(root!=NULL){
        printf("%d",root->key);
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }
}
void inorderTraversal(struct TreeNode *root){
    if(root!=NULL){
        inorderTraversal(root->left);
        printf("%d",root->key);
        inorderTraversal(root->right);
    }
}
void postorderTraversal(struct TreeNode* root){
    if(root!=NULL){
        postorderTraversal(root->left);
        postorderTraversal(root->right);
        printf("%d",root->key);
    }
}

struct TreeNode* search(struct TreeNode* root,int key){
    if(root==NULL||root->key==key){
        return root;
    }
    if(key<root->key){
        search(root->left,key);
    }
    else if(key>root->key){
        search(root->right,key);
    }


}
struct TreeNode * minValueNode(struct TreeNode *root){
    struct TreeNode *current=root;
    while(current->left!=NULL){
        current=current->left;
    }
    return current;
}

int main() {
    struct TreeNode* root = NULL;
    int choice, key;

    do {
        printf("\nBinary Search Tree Operations:\n");
        printf("1. Insertion\n");
        printf("2. Deletion\n");
        printf("3. Searching\n");
        printf("4. Inorder Traversal\n");
        printf("5. Postorder Traversal\n");
        printf("6. Preorder Traversal\n");
        printf("7. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter key to insert: ");
                scanf("%d", &key);
                root = insert(root, key);
                break;

            case 2:
                // printf("Enter key to delete: ");
                // scanf("%d", &key);
                // root = deleteNode(root, key);
                if(root!=NULL)
                {struct TreeNode *min=minValueNode(root);
                printf("%d",min->key);}
                break;

            case 3:
                printf("Enter element to search");
                scanf("%d",&key);
                if(search(root,key)==NULL){
                    printf("NOT FOUND");
                }
                else {
                    printf("Found in this BST");
                }
                break;
            case 4:
               printf("Inorder Traversal");
               inorderTraversal(root);
                printf("\n");
                break;

            case 5:
               printf("PostOrder Traversal");
               postorderTraversal(root);
               printf("\n");
               break;

            case 6:
                printf("Preorder Traversal: ");
                preorderTraversal(root);
                printf("\n");
                break;

            case 7:
                printf("Exiting the program.\n");
                break;

            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 7);

    return 0;
}
