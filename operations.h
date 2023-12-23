#include "polynomial.h"
#include <stdbool.h>
#include <math.h>

void log_polynomial(term_t* p1){
    print_terms(p1);
    printf("^ contains %u term(s).\n", count_terms(p1));
}

// Reverses a linked list
void reverse_polynomial(term_t** head){
    term_t* curr_term = *head, *prev_term = NULL, *next_term = NULL;
    while(curr_term != NULL){
        next_term = curr_term->next;
        curr_term->next = prev_term;
        prev_term = curr_term;
        curr_term = next_term;
    }
    *head = prev_term;                      // the last term becomes the new head node
}

// Adds and subtracts like terms
void simplify_polynomial(term_t** head){
    int32_t arrCoefTotals[UINT8_MAX+1] = {0}; // uint8_t expo is guaranteed to be between [0, 255]
    bool arrExpoExists[UINT8_MAX+1] = {0};
    term_t* curr_term = *head, *next = NULL; uint32_t pos = 0;  
    while(curr_term != NULL){
        bool first_instance = 1;      // first_instance is a sentinel; if it is zero then we can safely assume that curr_term is a like term
        next = curr_term->next;   
        arrCoefTotals[curr_term->expo] += curr_term->coef; 
        if(curr_term->coef == 0 || arrExpoExists[curr_term->expo]){
            remove_term(head, pos);   // remove all subsequent terms with a known exponent or zero coefficient                    
            first_instance = 0;
        }
        if(first_instance){                 
            arrExpoExists[curr_term->expo] = 1;
            pos++;
        }
        curr_term = next;
    }

    curr_term = *head, next = NULL; pos = 0;   // pass through polynomial again to set coefficients in arrCoefTotals
    while(curr_term != NULL){
        next = curr_term->next;
        curr_term->coef = arrCoefTotals[curr_term->expo];
        if(curr_term->coef == 0){              // removes curr_term if coef simplifies to zero
            remove_term(head, pos); 
        }
        else{
            pos++;
        }
        curr_term = next;
    }
}

/* Sort terms from highest to lowest order utilizing Bubble Sort.
Note: this function doesn't sort coefficients.*/
void sort_polynomial(term_t** head){
    term_t* curr_term = *head;
    uint32_t count = count_terms(*head);
    if(count < 2){  // the polynomial is already sorted
        return;
    }
    for(uint32_t comps = count - 1; comps > 0; comps--){
        uint32_t pos = 0;
        while(curr_term != NULL && curr_term->next != NULL && pos < comps){
            if(curr_term->expo < curr_term->next->expo){
                swap_terms(curr_term, curr_term->next);
            }
            curr_term = curr_term->next;
            pos++;
        }
        curr_term = *head;
    }
}

// => (p1) + (p2)
void add_polynomials(term_t** p1, term_t** p2){
    if(*p1 && *p2){
        term_t* h1 = *p1;
        while(h1->next != NULL){
            h1 = h1->next;
        }
        h1->next = *p2;    // connects the next pointer of the last non-null node to the start of p2's data
        *p2 = NULL;         
    }
    else{
        printf("ERROR: Make sure that p1 and p2 are initialized with non-NULL values.\n");
    }
}

// => (p1) - (p2)
void subtract_polynomials(term_t** p1, term_t** p2){
    if(*p1 && *p2){
        term_t* h1 = *p1, *h2 = *p2;
        while(h2 != NULL){
            h2->coef *= -1;
            h2 = h2->next;
        }
        while(h1->next != NULL){
            h1 = h1->next;
        }
        h1->next = *p2;  
        *p2 = NULL;  
    }
    else{
        printf("ERROR: Make sure that p1 and p2 are initialized with non-NULL values.\n");
    }          
}

term_t* derivative_polynomial(term_t* p){
    term_t* dp = NULL;
    if(!p){
        printf("ERROR: p currently points to NULL, NULL returned.\n");
        return NULL;
    }
    else{
        while(p != NULL){
            if(p->expo > 0 && p->coef != 0){
                add_term(&dp, p->expo * p->coef, p->expo - 1);     // d/dx[x^n] = nx^(n-1) for n > 0
            }                                                      // otherwise, d/dx[constant] = 0
            p = p->next;
        }
        reverse_polynomial(&dp);   // reversing dp preserves p's term order 
    }
    return dp;
}

// Substitutes a real number x into function p and returns p(x)
double evaluate_polynomial(term_t* p, double x){
    double px = 0;
    if(!p){
        printf("ERROR: p currently points to NULL, -1.0f returned.\n");
        return -1.0f;
    }
    else{
        while(p != NULL){
            px += p->coef*pow(x, (double)p->expo);   // adds even if coef = 0
            p = p->next;
        }
    }
    return px;
}

/* Implements Newton-Raphson. Assumes that the polynomial has one or more real solutions, 
else the function will return an incorrect answer.*/
double solve_polynomial(term_t* p, double x0, uint8_t max_iterations, double delta){
    double x = x0;
    if(!p){
        printf("ERROR: p currently points to NULL, -1.0f returned.\n");
        return -1.0f;
    }
    else{
        term_t* dp = derivative_polynomial(p);
        for(uint8_t it = 0; it < max_iterations; it++){
            double px = evaluate_polynomial(p, x);
            double dpx = evaluate_polynomial(dp, x);
            if(fabs(dpx) <= delta){
                printf("NOTE: dpx < specified tolerance %f, x0 returned.\n", delta);
                break;
            }                    
            x -= px/dpx;             // NOTE: doesn't address the problem of certain polynomials & initial x's resulting in an infinite cycle
        }                            // see TEST #4
        remove_all_terms(&dp);
        dp = NULL;
    }
    return x;
}