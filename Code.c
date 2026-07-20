#include <stdio.h>
#include <stdlib.h>

// Structure for BST Node
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

// Helper function to create a new tree node
Node* createNode(int val) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = val;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to insert a value into the BST
Node* insert(Node* root, int val) {
    if (root == NULL) {
        return createNode(val);
    }
    if (val < root->data) {
        root->left = insert(root->left, val);
    } else {
        root->right = insert(root->right, val);
    }
    return root;
}

// Helper function to perform post-order traversal and fill the result array
void postOrderTraversal(Node* root, int* result, int* index) {
    if (root == NULL) {
        return;
    }
    postOrderTraversal(root->left, result, index);  // Explore left
    postOrderTraversal(root->right, result, index); // Explore right
    result[(*index)++] = root->data;                // Record current chamber
}

// Helper function to free the allocated tree memory
void freeTree(Node* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

// User logic implementation matching your template signature
int* recover_sequence(int* artifact_numbers, int n, int* returnSize) {
    if (n == 0) {
        *returnSize = 0;
        return NULL;
    }

    // 1. Construct the Binary Search Tree
    Node* root = NULL;
    for (int i = 0; i < n; i++) {
        root = insert(root, artifact_numbers[i]);
    }

    // 2. Allocate memory for the recovery sequence result
    int* result = (int*)malloc(n * sizeof(int));
    int index = 0;

    // 3. Perform Post-order traversal to populate the result
    postOrderTraversal(root, result, &index);

    // 4. Clean up tree memory and set return sizes
    freeTree(root);
    *returnSize = n;

    return result; 
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    
    int* artifact_numbers = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &artifact_numbers[i]) != 1) return 0;
    }

    int returnSize;
    int* recovery_sequence = recover_sequence(artifact_numbers, n, &returnSize);

    for (int i = 0; i < returnSize; i++) {
        printf("%d ", recovery_sequence[i]);
    }
    printf("\n");

    free(artifact_numbers);
    free(recovery_sequence);
    return 0;
}
