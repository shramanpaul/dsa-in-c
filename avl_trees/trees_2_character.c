#include <stdio.h>
#include <stdlib.h>

struct Node {
    char data;
    struct Node* left;
    struct Node* right;
    int height;
};

int max(int a, int b) {
    return (a > b) ? a : b;
}

int getHeight(struct Node* node) {
    if (node == NULL) return 0;
    return node->height;
}

struct Node* newNode(char data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

struct Node* rightRotate(struct Node* y) {
    struct Node* x = y->left;
    struct Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

struct Node* leftRotate(struct Node* x) {
    struct Node* y = x->right;
    struct Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

int getBalance(struct Node* node) {
    if (node == NULL) return 0;
    return getHeight(node->left) - getHeight(node->right);
}

struct Node* insert(struct Node* node, char data) {
    if (node == NULL) return newNode(data);

    if (data < node->data) node->left = insert(node->left, data);
    else if (data > node->data) node->right = insert(node->right, data);
    else return node;

    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    int balance = getBalance(node);

    if (balance > 1 && data < node->left->data) return rightRotate(node);
    if (balance < -1 && data > node->right->data) return leftRotate(node);
    if (balance > 1 && data > node->left->data) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if (balance < -1 && data < node->right->data) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

struct Node* search(struct Node* root, char data) {
    if (root == NULL || root->data == data) return root;

    if (root->data < data)
        return search(root->right, data);

    return search(root->left, data);
}

struct Node* minValueNode(struct Node* node) {
    struct Node* current = node;

    while (current && current->left != NULL) current = current->left;

    return current;
}

struct Node* deleteNode(struct Node* root, char data) {
    if (root == NULL) return root;

    if (data < root->data)
        root->left = deleteNode(root->left, data);
    else if (data > root->data)
        root->right = deleteNode(root->right, data);
    else {
        if (root->left == NULL || root->right == NULL) {
            struct Node* temp = root->left ? root->left : root->right;

            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else
                *root = *temp;
            free(temp);
        } else {
            struct Node* temp = minValueNode(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
    }

    if (root == NULL) return root;

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0) return rightRotate(root);

    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0) return leftRotate(root);

    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

void inOrder(struct Node* root) {
    if (root != NULL) {
        inOrder(root->left);
        printf("%c ", root->data);
        inOrder(root->right);
    }
}

void preOrder(struct Node* root) {
    if (root != NULL) {
        printf("%c ", root->data);
        preOrder(root->left);
        preOrder(root->right);
    }
}

void postOrder(struct Node* root) {
    if (root != NULL) {
        postOrder(root->left);
        postOrder(root->right);
        printf("%c ", root->data);
    }
}

int main() {
    struct Node* root = NULL;
    char input;
    char choice;
    
    printf("Enter characters to insert into AVL tree (enter '.' to stop):\n");
    
    while (1) {
        scanf(" %c", &input);
        if (input == '.') {
            break;
        }
        root = insert(root, input);
    }

    while (1) {
        printf("Enter 'i' for inorder, 'p' for preorder, 'o' for postorder, 's' for search, 'd' for delete, or 'q' to quit: ");
        scanf(" %c", &choice);
        
        if (choice == 'q') {
            break; // Exit the loop and end the program.
        } else if (choice == 's') {
            char searchData;
            printf("Enter the character to search for: ");
            scanf(" %c", &searchData);
            struct Node* searchResult = search(root, searchData);
            if (searchResult != NULL) {
                printf("Character found: %c\n", searchResult->data);
            } else {
                printf("Character not found.\n");
            }
        } else if (choice == 'd') {
            char deleteData;
            printf("Enter the character to delete: ");
            scanf(" %c", &deleteData);
            root = deleteNode(root, deleteData);
            printf("Character deleted.\n");
        } else if (choice == 'i') {
            inOrder(root);
            printf("\n");
        } else if (choice == 'p') {
            preOrder(root);
            printf("\n");
        } else if (choice == 'o') {
            postOrder(root);
            printf("\n");
        } else {
            printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

