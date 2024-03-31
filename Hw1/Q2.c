#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_TERMS 100 /* Size of terms array */
 // A term is a non-zero element in the matrix
typedef struct {
    int row;
    int col;
    int value;
} term;
// The first element of the array is a special element that contains the number of rows, columns, and non-zero elements in the matrix
term a[MAX_TERMS];
term b[MAX_TERMS];
// Transpose the matrix 'a' and store the result in 'b'
void transpose(term a[], term b[]) {
    int n, i, j, currentb;
    n = a[0].value;
    b[0].row = a[0].col;
    b[0].col = a[0].row;
    b[0].value = n;
    // If the matrix is not empty, transpose the matrix
    if (n > 0) {
        currentb = 1;
        for (i = 0; i < a[0].col; i++) {
            for (j = 1; j <= n; j++) {
                if (a[j].col == i) {
                    b[currentb].row = a[j].col; 
                    b[currentb].col = a[j].row;
                    b[currentb].value = a[j].value;
                    currentb++;
                }
            }
        }
    }
}
// Print the matrix
void print_matrix(term m[]) {
    int num_elements = m[0].value;
    printf("row col value\n");
    for (int i = 1; i <= num_elements; i++) {
        printf("%d   %d   %d\n", m[i].row, m[i].col, m[i].value);
    }
}
// Test the transpose function by initializing the matrix in the provided example
void basic_test() {
    printf("Basic Test\n");
    // Initialize matrix 'a' as in the provided example
    a[0].row = 6; a[0].col = 6; a[0].value = 8;
    a[1].row = 0; a[1].col = 0; a[1].value = 15;
    a[2].row = 0; a[2].col = 3; a[2].value = 22;
    a[3].row = 0; a[3].col = 5; a[3].value = -15;
    a[4].row = 1; a[4].col = 1; a[4].value = 11;
    a[5].row = 1; a[5].col = 2; a[5].value = 3;
    a[6].row = 2; a[6].col = 3; a[6].value = -6;
    a[7].row = 4; a[7].col = 0; a[7].value = 91;
    a[8].row = 5; a[8].col = 2; a[8].value = 28;

    transpose(a, b);
    print_matrix(a[0].row == 6 ? a : b);
    print_matrix(b);
}
// Test the transpose function by initializing the matrix with random values
void random_test() {
    printf("\nRandom Test\n");
    srand(time(NULL));
    int n = rand() % 10 + 1;
    a[0].row = 6; a[0].col = 6; a[0].value = n;
    for (int i = 1; i <= n; i++) {
        a[i].row = rand() % 6;
        a[i].col = rand() % 6;
        a[i].value = rand() % 20 + 1;
    }

    transpose(a, b);
    print_matrix(b);
}
// Test the transpose function with special cases
void special_cases_test() {
    printf("\nSpecial Cases Test - Empty Matrix\n");
    a[0].row = 6; a[0].col = 6; a[0].value = 0;
    transpose(a, b);
    print_matrix(b);

    printf("\nSpecial Cases Test - Single Row\n");
    a[0].row = 1; a[0].col = 6; a[0].value = 2;
    a[1].row = 0; a[1].col = 2; a[1].value = 5;
    a[2].row = 0; a[2].col = 5; a[2].value = -3;
    transpose(a, b);
    print_matrix(b);
}
// Main function to test the transpose function
int main() {
    basic_test();
    random_test();
    special_cases_test();

    return 0;
}
