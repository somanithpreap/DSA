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

void insert(Node** root, int data) {
	if (!*root) *root = createNode(data);
	else insert(data < (*root)->data ? &(*root)->left : &(*root)->right, data);
}

Node** search(Node** root, int data) {
	if (!*root) return NULL;
	if ((*root)->data == data) return root;
	return search((data < (*root)->data) ? &(*root)->left : &(*root)->right, data);
}

Node** searchIterative(Node** root, int data) {
	while (*root) {
		if ((*root)->data == data) return root;
		root = (data < (*root)->data) ? &(*root)->left : &(*root)->right;
	}
	return NULL;
}

void deleteNode(Node** root, int data) {
	if (!*root) return;

	Node** wanted = search(root, data);
	if (!*wanted) {
		printf("deleteNode(): Specified value not found.\n");
		exit(1);
	}

	if (!(*wanted)->left && !(*wanted)->right) {
		free(*wanted);
		*wanted = NULL;
	} else if (!((*wanted)->left || (*wanted)->right)) {
		Node* tmp  = *wanted;
		*wanted = (*wanted)->left ? (*wanted)->left : (*wanted)->right;
		free(tmp);
	} else {

	}
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

}
