#include <stdio.h>
#include <stdlib.h>

int* createStack(size_t capacity);
void push(int* stack, size_t* top, size_t capacity, int data);
int pop(int* stack, size_t* top);
void printStack(int* stack, int top);
void destroyStack(int* stack);

int main() {
	int* stack = createStack(3);
	size_t top = 0;
	size_t capacity = 3;

	push(stack, &top, capacity, 1);
	push(stack, &top, capacity, 2);
	push(stack, &top, capacity, 3);

	printf("Stack: ");
	printStack(stack, top);

	printf("Popped: %d\n", pop(stack, &top));
	printf("Stack: ");
	printStack(stack, top);

	destroyStack(stack);
}

int* createStack(size_t capacity) {
	int* stack = (int*)calloc(capacity, sizeof(int));
	if (stack) return stack;
	else {
		printf("Memory allocation failed.\n");
		exit(1);
	}
}

void push(int* stack, size_t* top, size_t capacity, int data) {
	if (*top == capacity) {
		printf("Stack is full. Cannot push %d.\n", data);
		exit(1);
	}
	stack[(*top)++] = data;
}

int pop(int* stack, size_t* top) {
	if (*top == 0) {
		printf("No element to pop. Stack is empty.\n");
		exit(1);
	}
	return stack[--(*top)];
}

void printStack(int* stack, int top) {
	if (top > 0) {
		printf("%d ", stack[top - 1]);
		printStack(stack, top - 1);
	} else printf("\n");
}

void destroyStack(int* stack) {
	free(stack);
}
