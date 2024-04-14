#include <stdbool.h> // Include for `bool` type
#include <string.h>  // Include for `strlen`

bool isValid(char * inStr){
    char charStack[5000];           // Define a stack of 5000 chars
    char *stackPtr = charStack;     // stackPtr as a pointer to the stack, traversing inStr character by character
    char *inStrPtr = inStr;         // inStrPtr as a pointer to inStr, traversing inStr character by character
    int length = strlen(inStr);     // Get the length of the input string

    for(int i = 0; i < length; i++, inStrPtr++){ // Get the length of the input string
        switch(*inStrPtr){ // Switch statement to check the current character
            case '(': 
            case '[': 
            case '{':
                *stackPtr = *inStrPtr; // Push the current character onto the stack
                stackPtr++;            // Move the stack pointer to the next position
                break;

            case ')':
                if(stackPtr == charStack || *(stackPtr-1) != '(') return false;
                stackPtr--; // Pop the top character from the stack
                break;

            case ']':
                if(stackPtr == charStack || *(stackPtr-1) != '[') return false;
                stackPtr--; // Pop the top character from the stack
                break;

            case '}':
                if(stackPtr == charStack || *(stackPtr-1) != '{') return false;
                stackPtr--; // Pop the top character from the stack
                break;

            default:
                // Do nothing for other characters
                return false;
        }
    }

    // Return true if the stack is empty, false otherwise
    return stackPtr == charStack; 
}
