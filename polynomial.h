#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

// The polynomial is just a singly-linked list, and nodes represent individual terms
typedef struct Term {
    int32_t coef;
    uint8_t expo;
    struct Term* next;
} term_t;

// New nodes are added to the end of the list
void add_term(term_t** head, int32_t coef, uint8_t expo){
    term_t* newTerm = (term_t*)malloc(sizeof(term_t));
    newTerm->coef = coef;
    newTerm->expo = expo;
    newTerm->next = NULL;
    if(*head != NULL){
        newTerm->next = *head;      // if the list isn't empty, then newTerm becomes the head node
    }
    *head = newTerm;                
}

// Frees a node at a specified position from the linked list
void remove_term(term_t** head, uint32_t pos_to_delete){
    uint32_t curr_pos = 0;
    term_t* curr_term = *head, *prev_term = NULL;
    while(curr_term != NULL && curr_pos != pos_to_delete){  // searches for the term to remove, as well as the ones before and after it
        prev_term = curr_term;
        curr_term = curr_term->next;
        curr_pos++;
    }
    if(curr_term != NULL){            // first checks that the linked list is not empty
        if(prev_term == NULL){        // CASE #1: node to remove is the head of the linked list
            *head = curr_term->next;  
        }
        else if(curr_term->next == NULL){  // CASE #2: node to remove is at the end of the linked list
            prev_term->next = NULL;   
        }
        else{
            prev_term->next = curr_term->next;  // CASE #3: node to remove is in the middle of the linked list
        }
        free(curr_term);
        curr_term = NULL;
    }
}

// Only variable contents are swapped; in other words, the order of terms in memory is preserved
void swap_terms(term_t* t1, term_t* t2){ 
    if(t1 != NULL && t2 != NULL){        
        int32_t tmp_coef = t1->coef;
        uint8_t tmp_expo = t1->expo;
        t1->coef = t2->coef;
        t1->expo = t2->expo;
        t2->coef = tmp_coef;
        t2->expo = tmp_expo;
    }
}

// Prints a polynomial in a way the end-user recognizes from Algebra
void print_terms(term_t* head){
    uint32_t pos = 0;
    while(head != NULL){
        if(head->coef == 0){    // like in Algebra, print_terms ignores nodes whose coef = 0
            printf((head->next != NULL) ? "" : "\n");
            head = head->next;
            continue;          
        }
        printf(pos == 0 ? (head->coef >= 0 ? "" : "-") : (head->coef >= 0 ? " + " : " - "));  // makes signage look nice
        if(imaxabs(head->coef) > 1 && head->expo > 1){                  // -> cx^n only when c and n > 1
            printf("%llux^%u", imaxabs(head->coef), head->expo);
        }
        else{
            printf((imaxabs(head->coef) == 1 && head->expo != 0) ? "" : "%llu", imaxabs(head->coef)); // else handle all the edge cases
            if(head->expo == 1){ 
                printf("x");
            }
            else if(head->expo > 1){
                printf("x^%u", head->expo);
            }
        }
        printf((head->next != NULL) ? "" : "\n");
        head = head->next;
        pos++;
    }
}

/*Frees all nodes in the linked list.
No need to set head to NULL manually.*/
void remove_all_terms(term_t** head){
    term_t* curr_term = *head, *next_term = NULL;
    while(curr_term != NULL){
        next_term = curr_term->next;
        free(curr_term);
        curr_term = next_term;
    }
    *head = NULL;
}

/*Counts the number of terms in the polynomial.
Might not match the number of terms printed because print_terms ignores zeroes.*/
uint32_t count_terms(term_t* head){ 
    uint32_t terms = 0;
    while(head != NULL){
        head = head->next;
        terms++;
    }
    return terms;
}