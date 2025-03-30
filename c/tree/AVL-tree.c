#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int data;
	size_t height;
	struct Node *left;
	struct Node *right;
} Node;

Node* createNode(int data) {
	Node* node = (Node*)malloc(sizeof(Node));
	if (!node) {
		printf("newNode(): Could not allocate memory.\n");
		exit(1);
	}
	node->data = data;
	node->height = 1;
	node->left = NULL;
	node->right = NULL;
	return node;
}

void destroyTree(Node** root) {
	if (!*root) return;
	destroyTree(&(*root)->left);
	destroyTree(&(*root)->right);
	free(*root);
	*root = NULL;
}
