#include <stdio.h>
#include <stdlib.h>

typedef enum { RED, BLACK } Color;

typedef struct Node {
	int data;
	Color color;
	struct Node *left;
	struct Node *right;
	struct Node *parent;
} Node;

Node* createNode(int data) {
	Node* node = (Node*)malloc(sizeof(Node));
	if (!node) {
		printf("newNode(): Could not allocate memory.\n");
		exit(1);
	}
	node->data = data;
	node->color = RED;
	node->left = NULL;
	node->right = NULL;
	node->parent = NULL;
	return node;
}

// The tree satifies the following properties:
// 1. Every node is either red or black.
// 2. The root is black.
// 3. Every leaf (NIL) is black.
// 4. If a red node has children, then the children are black.
// 5. For each node, all simple paths from the node to descendant leaves contain the same number of black nodes.

// Insertion
// 1. Perform a standard BST insertion and make the color of the newly inserted nodes as RED.
// 2. If the newly inserted node is the root, change the color of the node to BLACK.
// 3. If the parent of the newly inserted node is BLACK, then the tree is still valid.
// 4. If the parent of the newly inserted node is RED, then there are two cases to consider:
//  a. The parent of the newly inserted node is the left child of the grandparent of the newly inserted node.
//  b. The parent of the newly inserted node is the right child of the grandparent of the newly inserted node.
// 5. If the parent of the newly inserted node is RED and the uncle of the newly inserted node is also RED, then:
// a. Change the color of the parent of the newly inserted node to BLACK.
// b. Change the color of the uncle of the newly inserted node to BLACK.
// c. Change the color of the grandparent of the newly inserted node to RED.
// d. Set the newly inserted node to the grandparent of the newly inserted node.
// e. Repeat steps 3 and 4 until the tree is valid.
// 6. If the parent of the newly inserted node is RED and the uncle of the newly inserted node is BLACK, then:
// a. Perform a rotation on the newly inserted node and its parent.
// b. Set the newly inserted node to its parent.
// c. Repeat step 5.
// 7. If the parent of the newly inserted node is RED and the uncle of the newly inserted node is BLACK, then:
// a. Perform a rotation on the newly inserted node and its grandparent.
// b. Change the color of the parent of the newly inserted node to BLACK.
// c. Change the color of the grandparent of the newly inserted node to RED.
// d. Set the newly inserted node to the parent of the newly inserted node.
// e. Repeat steps 3 and 4 until the tree is valid.
// 8. If the newly inserted node is the root, change the color of the node to BLACK.
