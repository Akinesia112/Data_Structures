#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <limits.h> // Include for INT_MIN

#define MAX_STACK_SIZE 100

// Stack structure and function declarations
typedef struct {
    int items[MAX_STACK_SIZE];
    int top;
} Stack;

Stack* CreateS();
bool Add(Stack* stack, int item);
int Delete(Stack* stack);
bool IsEmpty(Stack* stack);
bool IsFull(Stack* stack);
int precedence(char operator);
void infixToPostfix(char* infix, char* postfix);

// Implementations of stack functions
// Function to create a stack
Stack* CreateS() {
    Stack* S = (Stack*)malloc(sizeof(Stack)); // Allocate memory for stack
    S->top = -1;  // Initialize top to -1
    return S;
}

// Function to check if stack is full
bool IsFull(Stack* stack) {
    return stack->top == MAX_STACK_SIZE - 1; // Return true if stack is full
}

// Add an item to the stack
bool Add(Stack* stack, int item) {
    if (IsFull(stack)) {
        return false; // Return false if stack is full
    }
    stack->items[++stack->top] = item; // Add item to stack
    return true; // Return true if stack is not full
}

// Function to check if stack is empty
bool IsEmpty(Stack* stack) {
    return stack->top == -1; // Return true if stack is empty
}

// Function to delete an item from the stack
int Delete(Stack* stack) {
    if (IsEmpty(stack)) {
        return INT_MIN; // Use INT_MIN to indicate an error or empty stack
    }
    return stack->items[stack->top--];
}

// Function to return precedence of operators
int precedence(char operator) {
    switch (operator) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0; // for non-operators
    }
}

// Function to convert infix expression to postfix
void infixToPostfix(char* infix, char* postfix) {
    Stack* stack = CreateS();
    int i, j = 0;
    char token;
    for (i = 0; infix[i] != '\0'; i++) {
        token = infix[i];
        // Skip spaces in the infix expression
        if (token == ' ') {
            continue;
        }
        // Handle operands (digits)
        if (isdigit(token)) {
            // Add operand to postfix expression
            postfix[j++] = token;
            // Handle multi-digit numbers
            while (isdigit(infix[i + 1])) {
                postfix[j++] = infix[++i];
            }
            // Add space after operand
            postfix[j++] = ' ';
        } else if (token == '(') {
            // Push '(' onto stack
            Add(stack, token);
        } else if (token == ')') {
            // Pop everything up to the matching '('
            while (!IsEmpty(stack) && stack->items[stack->top] != '(') {
                postfix[j++] = Delete(stack);
                postfix[j++] = ' ';
            }
            // Pop the '('
            Delete(stack);
        } else {
            // Operator
            // Pop operators with higher or equal precedence
            while (!IsEmpty(stack) && precedence(token) <= precedence(stack->items[stack->top]) && stack->items[stack->top] != '(') {
                postfix[j++] = Delete(stack);
                postfix[j++] = ' ';
            }
            // Push the current operator onto stack
            Add(stack, token);
        }
    }
    // Pop any remaining operators from the stack
    while (!IsEmpty(stack)) {
        postfix[j++] = Delete(stack);
        postfix[j++] = ' ';
    }
    // Replace the last space with a null terminator
    if (j > 0 && postfix[j - 1] == ' ') {
        j--;
    }
    postfix[j] = '\0';
    // Free the stack
    free(stack);
}


// Main function to read infix expressions from a file and convert them to postfix
int main() {
    printf("-----------------Example---------------\n");
    char exampleInfix[] = "1 + 1 * 2"; // Example infix expression
    char examplePostfix[strlen(exampleInfix) + 1]; // Postfix expression buffer
    infixToPostfix(exampleInfix, examplePostfix); // Convert infix expression to postfix
    printf("Infix: %s\nPostfix: %s\n", exampleInfix, examplePostfix); // Print the postfix expression

    printf("========================================\n");

    // Test
    printf("-----------------Test------------------\n");
    FILE *q2File = fopen("Q2.Testcase.txt", "r"); // Open Q2 test file for reading
    FILE *q1File = fopen("Q1.Testcase.txt", "r"); // Open Q1 test file for reading
    char infix[MAX_STACK_SIZE]; // Buffer for reading an infix expression
    char postfix[MAX_STACK_SIZE]; // Buffer for the corresponding postfix expression
    char expectedPostfix[MAX_STACK_SIZE]; // Buffer for the expected postfix expression from Q1

    if (q2File != NULL && q1File != NULL) {
        while (fgets(infix, sizeof(infix), q2File)) {
            if(fgets(expectedPostfix, sizeof(expectedPostfix), q1File) == NULL) {
                printf("Error reading from Q1 Testcase file.\n");
                break;
            }
            infix[strcspn(infix, "\n\r")] = 0; // Remove newline character
            expectedPostfix[strcspn(expectedPostfix, "\n\r")] = 0; // Remove newline character

            infixToPostfix(infix, postfix); // Convert infix to postfix
            printf("Infix: %s\nExpected Postfix: %s\nActual Postfix: %s\n", infix, expectedPostfix, postfix); // Print the results
            
            // Compare actual postfix with expected postfix
            if (strcmp(postfix, expectedPostfix) == 0) {
                printf("Result: Correct\n");
            } else {
                printf("Result: Incorrect\n");
            }
            printf("----------------------------------------\n");
        }
        fclose(q2File); // Close Q2 test file
        fclose(q1File); // Close Q1 test file
    } else {
        if (q2File == NULL) perror("Error opening Q2 Testcase file");
        if (q1File == NULL) perror("Error opening Q1 Testcase file");
    }

    return 0; // Return 0 to indicate successful execution
}