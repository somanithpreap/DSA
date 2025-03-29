#include "stack.h"

Stack* createStack() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    if (!stack) {
		printf("Memory allocation failed.\n");
		exit(1);
	}
    stack->top = NULL;
    return stack;
}

bool stackIsEmpty(Stack* stack) {
	if (!stack) return true;
    return stack->top == NULL;
}

void pushToStack(Stack** stack, char* data) {
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    if (!newNode) {
		printf("Memory allocation failed.\n");
		exit(1);
	}
    newNode->data = data;

    if (!*stack) {
    	newNode->next = NULL;
    	*stack = createStack();
    } else
    	newNode->next = (*stack)->top;
    (*stack)->top = newNode;
}

char* popFromStack(Stack* stack) {
	if (!stack) return NULL;
    if (stackIsEmpty(stack)) {
    	free(stack);
        printf("The stack is empty; there is no element to pop.\n");
        exit(1);
    }

    StackNode* temp = stack->top;
    stack->top = stack->top->next;
    char* popped = temp->data;
    free(temp);
    return popped;
}

char* peekStack(Stack* stack) {
	if (!stack) return NULL;
    if (stackIsEmpty(stack)) {
        printf("The stack is empty; there is no element to peek.\n");
        exit(1);
    }
    return stack->top->data;
}

void clearStack(Stack* stack) {
	if (!stack) return;
	while (!stackIsEmpty(stack))
        free(popFromStack(stack));
}

void destroyStack(Stack** stack) {
	clearStack(*stack);
    free(*stack);
    *stack = NULL;
}

void reverseStack(Stack* stack) {
    StackNode* prev = NULL;
    StackNode* current = stack->top;
    StackNode* next = NULL;

    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    stack->top = prev;
}
