#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

void postorderTraversal(struct Node* root) {
    if (root == NULL) return;
    postorderTraversal(root->left);
    postorderTraversal(root->right);
    printf("%d ", root->data);
}

// Sample Usage
int main() {
    // Create a sample binary tree (same as before)
    struct Node* root = (struct Node*)malloc(sizeof(struct Node));
    root->data = 2;
    root->left = (struct Node*)malloc(sizeof(struct Node));
    root->left->data = 1;
    root->left->left = NULL;
    root->left->right = NULL;
    root->right = (struct Node*)malloc(sizeof(struct Node));
    root->right->data = 3;
    root->right->left = NULL;
    root->right->right = NULL;

    // Print postorder traversal
    printf("Postorder Traversal: ");
    postorderTraversal(root);
    return 0;
}
