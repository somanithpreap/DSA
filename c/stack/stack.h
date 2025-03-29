#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct StackNode {
    char* data;
    struct StackNode* next;
} StackNode;

typedef struct Stack {
    StackNode* top;
} Stack;

Stack* createStack();
bool stackIsEmpty(Stack* stack);
void pushToStack(Stack** stack, char* data);
char* popFromStack(Stack* stack);
char* peekStack(Stack* stack);

void reverseStack(Stack* stack);
void clearStack(Stack* stack);
void destroyStack(Stack** stack);

#endif
