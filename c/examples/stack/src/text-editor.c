#include "../../../stack/stack.h"
#include <stdio.h>
#include <string.h>

#define MAX_TEXT_SIZE 1024

// Main Text Editor Program
int main() {
    char text[MAX_TEXT_SIZE] = "";
    Stack* undoStack = createStack();
    Stack* redoStack = createStack();

    int choice;
    char inputText[MAX_TEXT_SIZE];

    while (1) {
        printf("\nCurrent Text: \n```\n%s\n```\n", text);
        printf("1. Add Text\n2. Undo\n3. Redo\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Clean newline

        switch (choice) {
            case 1: // Add Text
                printf("Enter text to add: ");
                fgets(inputText, MAX_TEXT_SIZE, stdin);
                inputText[strcspn(inputText, "\n")] = 0; // Remove trailing newline

                char* text_cp = (char*)malloc(strlen(text));
                if (!text_cp) {
					printf("Memory allocation failed.\n");
					return 1;
				}

                strcpy(text_cp, text);
                pushToStack(&undoStack, text_cp); // Save current state for undo
                strcat(text, inputText);

                clearStack(redoStack);
                break;
            case 2: // Undo
                if (!stackIsEmpty(undoStack)) {
                    pushToStack(&redoStack, text); // Save current state for redo
                    char *undoText = popFromStack(undoStack);
                    strcpy(text, undoText);
                    free(undoText);
                } else printf("Nothing to undo.\n");
                break;
            case 3: // Redo
                if (!stackIsEmpty(redoStack)) {
                    pushToStack(&undoStack, text); // Save current state for undo
                    char *redoText = popFromStack(redoStack);
                    strcpy(text, redoText);
                    free(redoText);
                } else printf("Nothing to redo.\n");
                break;
            case 4: // Exit
                destroyStack(&undoStack);
                destroyStack(&redoStack);
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
}
