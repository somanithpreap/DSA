#include "stack.h"

Stack* createStack() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->top = NULL;
    return stack;
}

bool stackIsEmpty(Stack* stack) {
    return stack->top == NULL;
}

void pushToStack(Stack* stack, char* data) {
    LLNode* newNode = (LLNode*)malloc(sizeof(LLNode));
    newNode->data = data;
    newNode->next = stack->top;
    stack->top = newNode;
}

char* popFromStack(Stack* stack) {
    if (stackIsEmpty(stack)) {
        printf("The stack is empty; there is no element to pop.\n");
        exit(1);
    }

    LLNode* temp = stack->top;
    stack->top = stack->top->next;
    char* popped = temp->data;
    free(temp);
    return popped;
}

char* peekStack(Stack* stack) {
    if (stackIsEmpty(stack)) {
        printf("The stack is empty; there is no element to peek.\n");
        exit(1);
    }
    return stack->top->data;
}

void freeStack(Stack** stack) {
    while (!stackIsEmpty(*stack))
        free(popFromStack(*stack));
    free(*stack);
    *stack = NULL;
}

void reverseStack(Stack *stack) {
    LLNode* prev = NULL;
    LLNode* current = stack->top;
    LLNode* next = NULL;

    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    stack->top = prev;
}
