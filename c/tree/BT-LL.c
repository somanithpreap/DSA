#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int data;
	struct Node *left;
	struct Node *right;
} Node;

Node* createNode(int data) {
    Node *node = (Node*)malloc(sizeof(Node));
    if (!node) {
    	printf("newNode(): Could not allocate memory.\n");
     	exit(1);
    }
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

size_t height(Node *root) {
	if (!root) return 0;
	size_t left = height(root->left);
	size_t right = height(root->right);
	return 1 + (left > right ? left : right);
}

void insert(Node **root, int data) {
	if (!*root)
		*root = createNode(data);
	else {
		if (!(*root)->left) (*root)->left = createNode(data);
		else if (!(*root)->right) (*root)->right = createNode(data);
		else insert(height((*root)->left) <= height((*root)->right) ? &(*root)->left : &(*root)->right, data);
	}
}

void inorder(Node* root) {
	if (!root) return;
	inorder(root->left);
	printf("%d ", root->data);
	inorder(root->right);
}

void preorder(Node* root) {
	if (!root) return;
	printf("%d ", root->data);
	preorder(root->left);
	preorder(root->right);
}

void postorder(Node* root) {
	if (!root) return;
	postorder(root->left);
	postorder(root->right);
	printf("%d ", root->data);
}

void destroyTree(Node** root) {
	if (!*root) return;
	if (!(*root)->left && !(*root)->right) {
		free(*root);
		return;
	}
	destroyTree(&(*root)->left);
	destroyTree(&(*root)->right);
	free(*root);
	*root = NULL;
}

int main() {
	Node* root = NULL;
	for (size_t i = 1; i <= 10; i++) insert(&root, i);

	printf("Inorder: ");
	inorder(root);
	printf("\n");

	destroyTree(&root);
}
