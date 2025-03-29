#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int data;
	struct Node* nextSibling;
	struct Node* child;
} Node;
