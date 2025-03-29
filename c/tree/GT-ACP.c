#include <stdio.h>
#include <stdlib.h>

#define MAX_CHILD 5

typedef struct Node {
	int data;
	struct Node* child[MAX_CHILD];
} Node;
