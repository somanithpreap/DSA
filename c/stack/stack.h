#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct LLNode {
    char* data;
    struct LLNode* next;
} LLNode;

typedef struct Stack {
    LLNode* top;
} Stack;



Stack* createStack();
bool stackIsEmpty(Stack* stack);
void pushToStack(Stack* stack, char* data);
char* popFromStack(Stack* stack);
char* peekStack(Stack* stack);

void reverseStack(Stack* stack);
void freeStack(Stack** stack);

#endif
