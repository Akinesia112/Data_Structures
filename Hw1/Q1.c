#include <stdio.h>
#define MAX_degree 101 // Maximum degree of the polynomial

typedef struct {
    int degree; // The degree of the polynomial
    float coef[MAX_degree]; // The coefficients of the polynomial
} polynomial;

polynomial poly_add(polynomial A, polynomial B) {
    polynomial result = {0}; // Initialize all coefficients to 0
    result.degree = A.degree > B.degree ? A.degree : B.degree; // Set the degree of the result to the maximum degree of the two polynomials

    // Add the coefficients of the two polynomials and store the result in the result polynomial by iterating through the coefficients
    for (int i = 0; i <= result.degree; i++) {
        result.coef[i] = A.coef[i] + B.coef[i]; // Add the coefficients
    }

    return result;
}

void print_poly(polynomial P) { // Function to print the polynomial
    int first = 1; // Flag to check if the first term has been printed
    // Iterate through the coefficients and print the non-zero coefficients
    for (int i = P.degree; i >= 0; i--) {
        if (P.coef[i] != 0) { // If the coefficient is non-zero
            if (!first) { // If it's not the first term, print a '+' sign
                printf("\n");
            }
            printf("%g %d", P.coef[i], i); // Print the coefficient and the degree
            first = 0;
        }
    }
}

int main() {
    // Initialize the polynomials A and B
    polynomial A = {9, {0, 0, -3, 0, 0, 12, 0, 0, 4, 5}};
    polynomial B = {9, {15, 0, 3, 0, 12, 0, 0, 0, 2, 3}};
    
    // Add the polynomials A and B
    polynomial result = poly_add(A, B);
    
    // Print the result
    printf("多項式A和B相加的結果是：\n");
    print_poly(result);
    printf("\n-----------------------\n");

    // Test case 1: Polynomials with the same degree
    polynomial C = {3, {4, 0, 2, 1}};
    polynomial D = {3, {-1, 0, 2, 3}};
    polynomial result1 = poly_add(C, D);
    printf("測試1結果（相同次數的多項式相加）：\n");
    print_poly(result1);
    printf("\n-----------------------\n");

    // Test case 2: Polynomials with different degrees
    polynomial E = {4, {0, 3, 1, 0, 2}};
    polynomial F = {2, {5, 0, -1}};
    polynomial result2 = poly_add(E, F);
    printf("測試2結果（不同次數的多項式相加）：\n");
    print_poly(result2);
    printf("\n-----------------------\n");

    // Test case 3: Polynomials with zero coefficients
    polynomial G = {3, {0, 0, 0, 5}};
    polynomial H = {3, {0, 0, 0, -5}};
    polynomial result3 = poly_add(G, H);
    printf("測試3結果（係數為零的多項式相加）：\n");
    print_poly(result3);
    printf("\n-----------------------\n");

    // Test case 4: Polynomials with boundary coefficients
    polynomial I = {0, {7}};
    polynomial J = {100, {3}};
    polynomial result4 = poly_add(I, J);
    printf("測試4結果（邊界次數的多項式相加）：\n");
    print_poly(result4);
    printf("\n-----------------------\n");

    return 0;
}