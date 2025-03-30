#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

typedef struct BinaryTree {
	int *arr;
	size_t size;
	size_t curr;
} BinaryTree;

// Takes in the number of nodes and returns a pointer to a BinaryTree struct
BinaryTree* createBinaryTree(size_t nodes) {
	BinaryTree* bt = (BinaryTree*)malloc(sizeof(BinaryTree));
	if (!bt) {
		printf("createBinaryTree(): Could not allocate memory.\n");
		exit(1);
	}

	// Calculates the suitable array size for the specified number of nodes
	size_t height = (size_t)ceil(log2f(nodes + 1));
	bt->size = (size_t)pow(2, height) - 1;

	bt->arr = (int*)calloc(bt->size, sizeof(int));
	for (size_t i = 0; i < bt->size; i++) bt->arr[i] = INT_MIN;
	bt->curr = 0;
	return bt;
}

void insert(BinaryTree *bt, int data) {
	if (!bt) return;
	if (bt->curr < bt->size) bt->arr[bt->curr++] = data;
	else {
		printf("insert(): Tree is full.\n");
		exit(1);
	}
}

void destroyTree(BinaryTree** bt) {
	if (!(bt && *bt)) return;
	free((*bt)->arr);
	free(*bt);
	*bt = NULL;
}

void inorderTraversal(BinaryTree *bt, size_t index) {
    if (!bt || index >= bt->size || bt->arr[index] == INT_MIN) return;
    inorderTraversal(bt, 2 * index + 1); // Left child
    printf("%d ", bt->arr[index]);
    inorderTraversal(bt, 2 * index + 2); // Right child
}

void preorderTraversal(BinaryTree *bt, size_t index) {
    if (!bt || index >= bt->size || bt->arr[index] == INT_MIN) return;
    printf("%d ", bt->arr[index]);
    preorderTraversal(bt, 2 * index + 1);
    preorderTraversal(bt, 2 * index + 2);
}

void postorderTraversal(BinaryTree *bt, size_t index) {
    if (!bt || index >= bt->size || bt->arr[index] == INT_MIN) return;
    postorderTraversal(bt, 2 * index + 1);
    postorderTraversal(bt, 2 * index + 2);
    printf("%d ", bt->arr[index]);
}

size_t treeHeight(BinaryTree *bt, size_t index) {
    if (!bt || index >= bt->size || bt->arr[index] == INT_MIN) return 0;

    // Compute height of left and right subtrees
    size_t leftHeight = treeHeight(bt, 2 * index + 1);
    size_t rightHeight = treeHeight(bt, 2 * index + 2);

    // Return the maximum height + 1 for the current level
    return 1 + ((leftHeight > rightHeight) ? leftHeight : rightHeight);
}

size_t countLeaves(BinaryTree *bt, int index) {
    if (!bt || index >= bt->size || bt->arr[index] == INT_MIN) return 0;

    size_t leftIndex = 2 * index + 1;
    size_t rightIndex = 2 * index + 2;
    // If the current node has no children, it is a leaf node
    if (leftIndex >= bt->size || rightIndex >= bt->size ||
        (bt->arr[leftIndex] == INT_MIN && bt->arr[rightIndex] == INT_MIN))
        return 1;

    return countLeaves(bt, leftIndex) + countLeaves(bt, rightIndex);
}

int main() {
	BinaryTree* bt = createBinaryTree(10);
	for (size_t i = 1; i <= 10; i++) insert(bt, i);

	printf("Inorder: ");
    inorderTraversal(bt, 0);
    printf("\n");

    printf("Preorder: ");
    preorderTraversal(bt, 0);
    printf("\n");

    printf("Postorder: ");
    postorderTraversal(bt, 0);
    printf("\n");

	destroyTree(&bt);
}
