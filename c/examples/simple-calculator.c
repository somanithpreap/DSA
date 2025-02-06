#include "../stack/stack.h"
#include <string.h>

bool isOperator(char c);
bool isInteger(char* str, size_t len);
int precedence(char c);
Stack* infixToPostfix(Stack* expression);
int calculate(Stack* postfix);

int main() {
    Stack* expression = createStack();
    char raw_token[11];

    // Save the state of the previous input
    // 0 : empty stack or open parenthesis or operator
    // 1 : integer or close parenthesis
    char prev = 0;

    while (1) {
        if (prev == 0)
            printf("Enter an operand or open parenthesis  : ");
        else
            printf("Enter an operator or close parenthesis: ");

        // Read and sanitize the input
        if (fgets(raw_token, sizeof(raw_token), stdin)) {
            raw_token[strcspn(raw_token, "\n")] = 0;
            size_t token_len = strlen(raw_token);
            if (token_len == 1 && raw_token[0] == '=') break;

            char* token = (char*)malloc(token_len);
            strcpy(token, raw_token);

            if (isInteger(raw_token, token_len) && prev == 0) {
                pushToStack(expression, token);
                prev = 1;
            } else if (token_len == 1) {
                if (isOperator(raw_token[0]) && prev == 1) {
                    pushToStack(expression, token);
                    prev = 0;
                } else if (raw_token[0] == '(' && prev == 0) {
                    pushToStack(expression, token);
                    prev = 0;
                } else if (raw_token[0] == ')' && prev == 1) {
                    pushToStack(expression, token);
                    prev = 1;
                } else {
                    printf("Invalid input.\n");
                    free(token);
                }
            } else {
                printf("Invalid input.\n");
                free(token);
            }
        } else printf("Invalid input.\n");
    }

    reverseStack(expression);

    Stack* postfix = infixToPostfix(expression);
    freeStack(&expression);

    printf("\nResult: %d\n", calculate(postfix));
    freeStack(&postfix);
}

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

bool isInteger(char* str, size_t len) {
    if (len > 10 && str[0] != '-' || len == 1 && str[0] == '-') return false;
    for (int i = 0; i < len; i++) {
        if (str[i] < '0' || str[i] > '9') {
            if (i == 0 && str[i] == '-') continue;
            return false;
        }
    }
    return true;
}

int precedence(char c) {
    if (c == '+' || c == '-') return 1;
    else if (c == '*' || c == '/') return 2;
    else if (c == '^') return 3;
    else return 0;
}

Stack* infixToPostfix(Stack* expression) {
    Stack* operators = createStack();
    Stack* postfix = createStack();

    while (!stackIsEmpty(expression)) {
        char* token = popFromStack(expression);
        if (isInteger(token, strlen(token)))
            pushToStack(postfix, token);
        else if (token[0] == '(')
            pushToStack(operators, token);
        else if (token[0] == ')') {
            while (!stackIsEmpty(operators) && peekStack(operators)[0] != '(')
                pushToStack(postfix, popFromStack(operators));
            popFromStack(operators); // Discard the open parenthesis
        } else if (isOperator(token[0])) {
            while (!stackIsEmpty(operators) && precedence(token[0]) <= precedence(peekStack(operators)[0]))
                pushToStack(postfix, popFromStack(operators));
            pushToStack(operators, token);
        }
    }

    // Pop the remaining operators
    while (!stackIsEmpty(operators))
        pushToStack(postfix, popFromStack(operators));

    freeStack(&operators);
    reverseStack(postfix);
    return postfix;
}

int calculate(Stack* postfix) {
    Stack* operands = createStack();

    while (!stackIsEmpty(postfix)) {
        char* token = popFromStack(postfix);
        if (isInteger(token, strlen(token))) {
            pushToStack(operands, token);
        } else if (isOperator(token[0])) {
            int num2 = atoi(popFromStack(operands));
            int num1 = atoi(popFromStack(operands));
            int result;
            switch (token[0]) {
                case '+':
                    result = num1 + num2;
                    break;
                case '-':
                    result = num1 - num2;
                    break;
                case '*':
                    result = num1 * num2;
                    break;
                case '/':
                    result = num1 / num2;
                    break;
                case '^':
                    result = 1;
                    for (int i = 0; i < num2; i++) {
                        result *= num1;
                    }
                    break;
            }
            char result_str[11];
            sprintf(result_str, "%d", result);
            pushToStack(operands, result_str);
        }
    }

    int result = atoi(popFromStack(operands));
    freeStack(&operands);
    return result;
}
