#include "../stack/stack.h"
#include "../queue/queue.h"
#include <string.h>

bool isUnaryOperator(char *expression, size_t index);
bool isOperator(char c);
bool isDigit(char c);
bool isNumber(char* str, size_t len);
int precedence(char c);
Stack* infixToPostfix(Queue* expression);
double calculate(Stack* postfix);

int main() {
	char expression[100];
	printf("Enter an expression: ");
	fgets(expression, sizeof(expression), stdin);
	expression[strcspn(expression, "\n")] = 0; // Remove trailing newline
	size_t exp_len = strlen(expression);

	Queue* tokensQueue = createQueue();
	char token[64];
	size_t written = 0;	// bytes written to token

	bool expectingNumber = true;
	// Tokenize the expression with floating-point numbers and unary operators supported
	for (size_t i = 0; i < exp_len; i++) {
        if (expression[i] == ' ') continue;

        if (isOperator(expression[i]) || expression[i] == '(' || expression[i] == ')') {
            // Handle unary + or -
            if ((expression[i] == '+' || expression[i] == '-') && isUnaryOperator(expression, i)) {
                token[written++] = expression[i];
                expectingNumber = false;
                continue;
            }

            // If there is a number in the buffer, enqueue it
            if (written > 0) {
                token[written] = '\0';
                enqueue(&tokensQueue, strdup(token));
                written = 0;
            }

            // Enqueue the operator or parenthesis
            token[0] = expression[i];
            token[1] = '\0';
            enqueue(&tokensQueue, strdup(token));
            expectingNumber = true;
        } else {
            // Append numbers and decimal points
            if (expression[i] == '.' && written > 0 && strchr(token, '.') == NULL) {
                token[written++] = '.';
            } else if (isDigit(expression[i]) || (expression[i] == '.' && written == 0)) {
                token[written++] = expression[i];
                expectingNumber = false;
            }
        }
    }

    // Enqueue any remaining token
    if (written > 0) {
        token[written] = '\0';
        enqueue(&tokensQueue, strdup(token));
    }

	Stack* postfix = infixToPostfix(tokensQueue);
	destroyQueue(&tokensQueue);

	printf("Result: %g\n", calculate(postfix));
	destroyStack(&postfix);
}

bool isUnaryOperator(char *expression, size_t index) {
    if (index == 0) return true;  // First character in expression
    char prev = expression[index - 1];
    return (prev == '(' || isOperator(prev));  // After '(' or another operator
}

bool isOperator(char c) {
	return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

bool isDigit(char c) {
	return c >= '0' && c <= '9';
}

bool isNumber(char* str, size_t len) {
	if (len == 0) return false;  // Empty string is invalid

    size_t i = 0;
    bool hasDecimal = false;
    bool hasDigit = false;

    // Check for unary + or -
    if (str[0] == '+' || str[0] == '-') {
        if (len == 1) return false; // "+" or "-" alone is not a number
        i++;
    }

    for (; i < len; i++) {
        if (isDigit(str[i])) hasDigit = true;
        else if (str[i] == '.') {
            if (hasDecimal || i == 0 || i == len - 1) return false;  // Multiple dots or leading/trailing dot
            hasDecimal = true;
        } else return false;  // Any other character is invalid
    }
    return hasDigit;
}

int precedence(char c) {
	if (c == '+' || c == '-') return 1;
	else if (c == '*' || c == '/') return 2;
	else if (c == '^') return 3;
	else return 0;
}

Stack* infixToPostfix(Queue* expression) {
	if (!expression) return NULL;

	Stack* operators = createStack();
	Stack* postfix = createStack();

	while (!queueIsEmpty(expression)) {
		char* token = dequeue(expression);

		if (isNumber(token, strlen(token)))
			pushToStack(&postfix, token);
		else if (token[0] == '(')
			pushToStack(&operators, token);
		else if (token[0] == ')') {
			while (!stackIsEmpty(operators) && peekStack(operators)[0] != '(')
				pushToStack(&postfix, popFromStack(operators));
			// Check for mismatched parentheses
			if (stackIsEmpty(operators)) {
				destroyStack(&operators);
				destroyStack(&postfix);
				clearQueue(expression);
				free(expression);
				printf("Invalid expression. Unexpected token `)`\n");
				exit(-1);
			}
			popFromStack(operators); // Discard the open parenthesis
		} else if (isOperator(token[0])) {
			while (!stackIsEmpty(operators) && precedence(token[0]) <= precedence(peekStack(operators)[0]))
				pushToStack(&postfix, popFromStack(operators));
			pushToStack(&operators, token);
		}
	}

	// Pop the remaining operators
	while (!stackIsEmpty(operators)) {
		if (peekStack(operators)[0] == '(') {
			destroyStack(&operators);
			destroyStack(&postfix);
			clearQueue(expression);
			free(expression);
			printf("Invalid expression. Unexpected token `(`\n");
			exit(1);
	 	}
		pushToStack(&postfix, popFromStack(operators));
	}

	destroyStack(&operators);
	reverseStack(postfix);
	return postfix;
}

double calculate(Stack* postfix) {
	Stack* operands = createStack();

	while (!stackIsEmpty(postfix)) {
		char* token = popFromStack(postfix);
		if (isNumber(token, strlen(token)))
			pushToStack(&operands, token);
		else if (isOperator(token[0])) {
			double num2 = atof(popFromStack(operands));
			double num1 = atof(popFromStack(operands));
			double result;

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
					if (num2 == 0) {
						destroyStack(&operands);
						destroyStack(&postfix);
						printf("Division by zero is not allowed.\n");
						exit(1);
					}
					result = num1 / num2;
					break;
				case '^':
					result = 1;
					for (size_t i = 0; i < num2; i++) result *= num1;
					break;
			}
			char result_str[64];
			sprintf(result_str, "%lf", result);
			pushToStack(&operands, result_str);
		}
	}

	double result = atof(popFromStack(operands));
	destroyStack(&operands);
	return result;
}
