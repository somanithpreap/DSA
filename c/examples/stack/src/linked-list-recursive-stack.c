#include <stdio.h>
#include <stdlib.h>

typedef struct StackNode {
	int data;
	struct StackNode *next;
} StackNode;

StackNode* createNode(int data);

void push(StackNode** stack, int data);
int pop(StackNode** stack);

void printStack(StackNode* stack);
void destroyStack(StackNode** stack);

int main() {
	StackNode* r_stack = NULL;
	push(&r_stack, 1);
	push(&r_stack, 2);
	push(&r_stack, 3);

	printf("Stack: ");
	printStack(r_stack);

	printf("Popped: %d\n", pop(&r_stack));
	printf("Stack: ");
	printStack(r_stack);

	destroyStack(&r_stack);
}

StackNode* createNode(int data) {
	StackNode* node = (StackNode*)malloc(sizeof(StackNode));
	if (!node) {
		printf("Memory allocation failed.\n");
		exit(1);
	}

	node->data = data;
	node->next = NULL;
	return node;
}

void push(StackNode** stack, int data) {
	StackNode* new_node = createNode(data);
	if (!new_node) {
		printf("Memory allocation failed.\n");
		exit(1);
	}

	if (!*stack)
		*stack = new_node;
	else {
		new_node->next = *stack;
		*stack = new_node;
	}
}

int pop(StackNode** stack) {
	if (!*stack) {
		printf("No element to pop. Stack is empty.\n");
		exit(1);
	}
	StackNode* tmp = *stack;
	*stack = (*stack)->next;

	int data = tmp->data;
	free(tmp);
	return data;
}

void printStack(StackNode* stack) {
	if (!stack) {
		printf("\n");
		return;
	}
	printf("%d ", stack->data);
	printStack(stack->next);
}

void destroyStack(StackNode** stack) {
	if (!*stack) return;
	if (!(*stack)->next) {
		free(*stack);
		return;
	}
	destroyStack(&(*stack)->next);
	(*stack)->next = NULL;
	free(*stack);
	stack = NULL;
	return;
}
