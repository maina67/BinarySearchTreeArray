// Jesse Maina Kanyi SCT221-0246/2022
// Titus Gicheha     SCT221-0216/2022
#include <stdio.h>
#include <stdlib.h>

// Definition of a Node in the BST
typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} Node;

// Function to create a new node with given data
Node* createNode(int data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to search for a value in the in-order array
int search(int inOrder[], int inStart, int inEnd, int value) {
    for (int i = inStart; i <= inEnd; i++) {
        if (inOrder[i] == value) {
        return i;
         }
    }
    return -1;
}

// Function to construct a BST from in-order and post-order arrays
Node* bst_construct(int inOrder[], int postOrder[], int inStart, int inEnd, int *postIndex) {
    if (inStart > inEnd) {
        return NULL;
    }


    int data = postOrder[*postIndex];
    Node *node = createNode(data);
    (*postIndex)--;


    if (inStart == inEnd) {
        return node;
    }


    int inIndex = search(inOrder, inStart, inEnd, data);


    node->right = bst_construct(inOrder, postOrder, inIndex + 1, inEnd, postIndex);
    node->left = bst_construct(inOrder, postOrder, inStart, inIndex - 1, postIndex);

    return node;
}

// Function to perform breadth-first-search (BFS) traversal of the BST
void bfs_traversal(Node *root) {
    if (root == NULL) {
        return;
    }


    Node *queue[100];
    int front = 0, rear = 0;


    queue[rear++] = root;

    while (front < rear) {

        Node *currentNode = queue[front++];


        printf("%d ", currentNode->data);


        if (currentNode->left) {
            queue[rear++] = currentNode->left;
        }


         if (currentNode->right) {
            queue[rear++] = currentNode->right;
        }
    }

    printf("\n");
}

// Main function
int main() {

    int inOrder[] = {5, 10, 15, 20, 25, 30, 45};
    int postOrder[] = {5, 15, 10, 25, 45, 30, 20};
    int length = sizeof(inOrder) / sizeof(inOrder[0]);

    int postIndex = length - 1;


    Node *root = bst_construct(inOrder, postOrder, 0, length - 1, &postIndex);


    bfs_traversal(root);


    return 0;
}
