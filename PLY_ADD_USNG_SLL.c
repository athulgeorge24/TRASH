#include <stdio.h>
#include <stdlib.h>

// Structure to represent a polynomial term
struct Node {
    int coeff;  // Coefficient of the term
    int exp;    // Exponent of the term
    struct Node* next;  // Pointer to next term
};

// Function to create a new node
struct Node* createNode(int coeff, int exp) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->coeff = coeff;
    newNode->exp = exp;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a term into the polynomial (sorted by exponent)
struct Node* insertTerm(struct Node* head, int coeff, int exp) {
    struct Node* newNode = createNode(coeff, exp);
    if (head == NULL || head->exp < exp) {
        newNode->next = head;
        return newNode;
    }
    
    struct Node* current = head;
    while (current->next != NULL && current->next->exp > exp) {
        current = current->next;
    }
    
    newNode->next = current->next;
    current->next = newNode;
    return head;
}

// Function to add two polynomials
struct Node* addPolynomials(struct Node* poly1, struct Node* poly2) {
    struct Node* result = NULL;
    struct Node *p1 = poly1, *p2 = poly2;
    
    while (p1 != NULL && p2 != NULL) {
        if (p1->exp == p2->exp) {
            int sum = p1->coeff + p2->coeff;
            if (sum != 0) {
                result = insertTerm(result, sum, p1->exp);
            }
            p1 = p1->next;
            p2 = p2->next;
        } else if (p1->exp > p2->exp) {
            result = insertTerm(result, p1->coeff, p1->exp);
            p1 = p1->next;
        } else {
            result = insertTerm(result, p2->coeff, p2->exp);
            p2 = p2->next;
        }
    }
    
    // Add remaining terms of poly1
    while (p1 != NULL) {
        result = insertTerm(result, p1->coeff, p1->exp);
        p1 = p1->next;
    }
    
    // Add remaining terms of poly2
    while (p2 != NULL) {
        result = insertTerm(result, p2->coeff, p2->exp);
        p2 = p2->next;
    }
    
    return result;
}

// Function to display polynomial
void displayPolynomial(struct Node* poly) {
    if (poly == NULL) {
        printf("0\n");
        return;
    }
    
    struct Node* current = poly;
    while (current != NULL) {
        printf("%dx^%d", current->coeff, current->exp);
        current = current->next;
        if (current != NULL) {
            printf(" + ");
        }
    }
    printf("\n");
}

// Function to free the linked list
void freePolynomial(struct Node* poly) {
    struct Node* current = poly;
    while (current != NULL) {
        struct Node* temp = current;
        current = current->next;
        free(temp);
    }
}

int main() {
    struct Node* poly1 = NULL;
    struct Node* poly2 = NULL;
    struct Node* result = NULL;
    
    // Example: poly1 = 5x^3 + 4x^2 + 2x^0
    poly1 = insertTerm(poly1, 5, 3);
    poly1 = insertTerm(poly1, 4, 2);
    poly1 = insertTerm(poly1, 2, 0);
    
    // Example: poly2 = 3x^2 + 1x^1
    poly2 = insertTerm(poly2, 3, 2);
    poly2 = insertTerm(poly2, 1, 1);
    
    printf("Polynomial 1: ");
    displayPolynomial(poly1);
    printf("Polynomial 2: ");
    displayPolynomial(poly2);
    
    // Add polynomials
    result = addPolynomials(poly1, poly2);
    
    printf("Sum: ");
    displayPolynomial(result);
    
    // Free memory
    freePolynomial(poly1);
    freePolynomial(poly2);
    freePolynomial(result);
    
    return 0;
}
