#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h> // Include for INT_MIN

#define MAX_STACK_SIZE 100

typedef struct {
    int items[MAX_STACK_SIZE];
    int top;
} Stack;

// Function to create a stack
Stack* CreateS() {
    Stack* S = (Stack*)malloc(sizeof(Stack)); // Allocate memory for the stack
    S->top = -1; // Initialize top to -1
    return S; // Return the stack
}

// Function to check if stack is full
bool IsFull(Stack* stack) {
    return stack->top == MAX_STACK_SIZE - 1; // Return true if stack is full
}

// Function to add item to stack
bool Add(Stack* stack, int item) {
    if (IsFull(stack)) {
        return false; // Return false if stack is full
    } else {
        stack->items[++stack->top] = item; // Add item to stack
        return true;
    }
}

// Function to check if stack is empty
bool IsEmpty(Stack* stack) {
    return stack->top == -1; // Return true if stack is empty
}

// Function to delete item from stack
int Delete(Stack* stack) {
    if (IsEmpty(stack)) {
        return INT_MIN; // or another value to indicate error
    } else {
        return stack->items[stack->top--]; // Delete item from stack
    }
}

// Function to evaluate postfix expressions
int EvaluatePostfix(char* expr) {
    Stack* stack = CreateS(); // Create stack
    char* token = strtok(expr, " "); // Initialize token with the first token

    while (token != NULL) {
        if (token[0] >= '0' && token[0] <= '9') { // If the token is an operand
            Add(stack, atoi(token));
        } else { // If the token is an operator
            int val2 = Delete(stack); // Get the second operand
            int val1 = Delete(stack); // Get the first operand
            switch (token[0]) {
                case '+': Add(stack, val1 + val2); break; // Add two operands and push the result to the stack
                case '-': Add(stack, val1 - val2); break; // Subtract two operands and push the result to the stack
                case '*': Add(stack, val1 * val2); break; // Multiply two operands and push the result to the stack
                case '/': Add(stack, val1 / val2); break; // Divide two operands and push the result to the stack
            }
        }
        token = strtok(NULL, " "); // Get the next token
    }

    int result = Delete(stack); // Get the result
    free(stack); // Don't forget to free the allocated memory
    return result; // Return the result
}

int main() {    
    char expr[MAX_STACK_SIZE]; // Initialize the expression
    FILE *file = fopen("Q1.Testcase.txt", "r"); // Open the test file
    if (!file) {
        perror("Failed to open example.txt"); // Print error message
        return EXIT_FAILURE;
    }
    
    // Example
    char Example[] = "1 1 2 * +"; // Initialize the expression
    printf("Example:\n"); 
    printf("Input: %s, Output: %d\n", Example, EvaluatePostfix(Example)); // Print the result
    printf("------------------------------------------------------------------\n");
    
    // Test
    file = fopen("Q1.Testcase.txt", "r"); // Open the test file
    if (!file) {
        perror("Failed to open test.txt"); // Print error message
        return EXIT_FAILURE;
    }
    
    printf("Test:\n");
    while (fgets(expr, MAX_STACK_SIZE, file) != NULL) { // Read each line
        expr[strcspn(expr, "\n")] = 0; // Remove newline character
        printf("Input: %s, Output: %d\n", expr, EvaluatePostfix(expr)); // Print the result
    }
    fclose(file); // Close the file

    return 0; // Return 0 to indicate successful completion
}