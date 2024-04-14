#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// the data structure of a polynomial node
typedef struct Node{
    int coef;
    int expo;
    struct Node *next;
}Node;

// helper function to print out the polynomial
// input polynomial linked list head
void print_poly(Node *head){
    printf("\n");
    if(head){
        while(head->next){
            printf("(%d)X^%d + ",head->coef,head->expo);
            head = head->next;
        }
        printf("(%d)X^%d",head->coef,head->expo);
    }
    else
        printf("0");
    printf("\n");
}

// create a new polynomial node and return the pointer point to the node
Node* new_node(int coef, int expo){
    Node* n = (Node*)malloc(sizeof(Node));
    n->coef = coef;
    n->expo = expo;
    n->next = NULL;
    return n;
}

// construct polynomial and return the pointer point to the head of polynomial
// You can Customize the input of this function 
Node* sorted_insert(Node *head, Node *node){
    if (!head || node->expo > head->expo){
        node->next = head;
        return node;
    }
    Node* current = head;
    while (current->next && current->next->expo > node->expo){
        current = current->next;
    }
    node->next = current->next;
    current->next = node;
    return head;
}

void construct_poly(const char *filepath, Node **A_head, Node **B_head) {
    FILE *file = fopen(filepath, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    int coef, expo;
    int is_first_poly = 1; // Flag to indicate whether it's the first polynomial
    while (fscanf(file, "%d %d", &coef, &expo) == 2) {
        if (is_first_poly) {
            *A_head = sorted_insert(*A_head, new_node(coef, expo));
        } else {
            *B_head = sorted_insert(*B_head, new_node(coef, expo));
        }
        // Check if we have read the first polynomial completely
        if (is_first_poly && fgetc(file) == '\n') {
            is_first_poly = 0; // Move to the second polynomial
        }
    }

    fclose(file);
}


// A + B and return the pointer point to the head of result
// input are two polynomial linked list heads
Node* plus(Node *A_head, Node* B_head){
    Node *result_head = NULL, *current, *temp;
    while (A_head && B_head){
        if (A_head->expo > B_head->expo){
            result_head = sorted_insert(result_head, new_node(A_head->coef, A_head->expo));
            A_head = A_head->next;
        } else if (A_head->expo < B_head->expo){
            result_head = sorted_insert(result_head, new_node(B_head->coef, B_head->expo));
            B_head = B_head->next;
        } else {
            int sum_coef = A_head->coef + B_head->coef;
            if (sum_coef != 0){
                result_head = sorted_insert(result_head, new_node(sum_coef, A_head->expo));
            }
            A_head = A_head->next;
            B_head = B_head->next;
        }
    }
    
    // If there are remaining terms in A or B, add them to the result
    while (A_head) {
        result_head = sorted_insert(result_head, new_node(A_head->coef, A_head->expo));
        A_head = A_head->next;
    }
    while (B_head) {
        result_head = sorted_insert(result_head, new_node(B_head->coef, B_head->expo));
        B_head = B_head->next;
    }
    return result_head;
}


// A - B and return the pointer point to the head of result
// input are two polynomial linked list heads
Node* minus(Node *A_head, Node* B_head){
    Node *result_head = NULL;
    while (A_head && B_head){
        if (A_head->expo > B_head->expo){
            result_head = sorted_insert(result_head, new_node(A_head->coef, A_head->expo));
            A_head = A_head->next;
        } else if (A_head->expo < B_head->expo){
            result_head = sorted_insert(result_head, new_node(-B_head->coef, B_head->expo));
            B_head = B_head->next;
        } else {
            int diff_coef = A_head->coef - B_head->coef;
            if (diff_coef != 0){
                result_head = sorted_insert(result_head, new_node(diff_coef, A_head->expo));
            }
            A_head = A_head->next;
            B_head = B_head->next;
        }
    }

    // If there are remaining terms in A or B, add them to the result
    while (A_head) {
        result_head = sorted_insert(result_head, new_node(A_head->coef, A_head->expo));
        A_head = A_head->next;
    }
    while (B_head) {
        result_head = sorted_insert(result_head, new_node(-B_head->coef, B_head->expo));
        B_head = B_head->next;
    }
    return result_head;
}

// Function to deallocate memory of the polynomial linked list
void free_poly(Node *head) {
    Node *temp;
    while (head) {
        temp = head;
        head = head->next;
        free(temp);
    }
}


int main(){
    char filepath[100];
    Node *A_head = NULL, *B_head = NULL;
    Node *sum = NULL, *diff = NULL;

    // Loop to process each of the five text files
    for (int i = 1; i <= 5; i++) {
        // Construct the file path for the current file
        sprintf(filepath, "D:\\Data Structure\\HW3_D84099084\\Test\\test%d.txt", i);

        // Read and construct the two given polynomials from the current file
        construct_poly(filepath, &A_head, &B_head);
        
        // Perform A+B and A-B
        sum = plus(A_head, B_head);
        diff = minus(A_head, B_head);

        // Print results for the current file
        printf("\nFile: test%d.txt\n", i);
        printf("A:");
        print_poly(A_head);
        printf("B:");
        print_poly(B_head);
        printf("A+B:");
        print_poly(sum);
        printf("A-B:");
        print_poly(diff);

        // Free memory for the current file's polynomials
        free_poly(A_head);
        free_poly(B_head);
        free_poly(sum);
        free_poly(diff);

        // Reset head pointers for the next iteration
        A_head = NULL;
        B_head = NULL;
        sum = NULL;
        diff = NULL;
    }
    
    return 0;
}
