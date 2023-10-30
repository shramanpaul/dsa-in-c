#include <stdio.h>
#include <stdlib.h>

// Define the structure of a binary tree node
struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
};

// Function to create a new binary tree node
struct TreeNode* createNode(int data) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to insert a new node into the binary tree
struct TreeNode* insert(struct TreeNode* root, int data) {
    if (root == NULL) {
        return createNode(data);
    }

    if (data < root->data) {
        root->left = insert(root->left, data);
    } else if (data > root->data) {
        root->right = insert(root->right, data);
    }

    return root;
}

// Function to find the minimum value node in a binary tree
struct TreeNode* findMin(struct TreeNode* root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

// Function to delete a node with a given value from the binary tree
struct TreeNode* deleteNode(struct TreeNode* root, int key) {
    if (root == NULL) {
        return root;
    }

    if (key < root->data) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->data) {
        root->right = deleteNode(root->right, key);
    } else {
        if (root->left == NULL) {
            struct TreeNode* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct TreeNode* temp = root->left;
            free(root);
            return temp;
        }

        struct TreeNode* temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }

    return root;
}

// Function to perform an in-order traversal of the binary tree
void inOrderTraversal(struct TreeNode* root) {
    if (root == NULL) {
        return;
    }

    inOrderTraversal(root->left);
    printf("%d ", root->data);
    inOrderTraversal(root->right);
}

int main() {
    struct TreeNode* root = NULL;
    int value;
    char choice;

    do {
        printf("Enter a value to insert: ");
        scanf("%d", &value);
        root = insert(root, value);

        printf("Do you want to insert another value? (y/n): ");
        scanf(" %c", &choice); // Notice the space before %c to consume the newline character.

    } while (choice == 'y' || choice == 'Y');

    printf("In-order traversal of the binary tree: ");
    inOrderTraversal(root);
    printf("\n");

    do {
        printf("Enter a value to delete: ");
        scanf("%d", &value);
        root = deleteNode(root, value);

        printf("Do you want to delete another value? (y/n): ");
        scanf(" %c", &choice); // Notice the space before %c to consume the newline character.

    } while (choice == 'y' || choice == 'Y');

    printf("In-order traversal after deleting: ");
    inOrderTraversal(root);
    printf("\n");

    return 0;
}
