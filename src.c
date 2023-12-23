#include "operations.h"

// Some basic tests that hopefully demonstrate what this library currently can and cannot do.

int main(){

    //TEST #1:
    /*
    term_t* p = NULL;
    derivative_polynomial(p);   // <- bad operation, error thrown

    add_term(&p, -4, 3);
    add_term(&p, -3, 2);
    add_term(&p, -1, 0);
    add_term(&p, 5, 1);
    add_term(&p, -3, 0);
    add_term(&p, 0, 5);
    add_term(&p, 3, 3);
    add_term(&p, -6, 0);
    add_term(&p, 3, 1);
    add_term(&p, 11, 0);
    add_term(&p, 2, 3);     // 4x^2 - 7x + 2x^3 + 11 + 3x - 6 + 3x^3 + 0 - 3 + 5x - 1 - 3x^2 - 4x^3
    add_term(&p, -7, 1);    
    add_term(&p, 4, 2);

    term_t* dp = derivative_polynomial(p);   // 8x - 7 + 6x^2 + 3 + 9x^2 + 5 - 6x - 12x^2

    log_polynomial(p);
    log_polynomial(dp);

    printf("p(2.5) = %f\n", evaluate_polynomial(p, 2.5f));    // unsimplified 
    printf("p'(2.5) = %f\n", evaluate_polynomial(dp, 2.5f));

    sort_polynomial(&p);
    simplify_polynomial(&p);   // x^3 + x^2 + x + 1

    sort_polynomial(&dp);
    simplify_polynomial(&dp);  // 3x^2 + 2x + 1

    log_polynomial(p);
    log_polynomial(dp);

    printf("p(2.5) = %f\n", evaluate_polynomial(p, 2.5f));      // simplified
    printf("p'(2.5) = %f\n", evaluate_polynomial(dp, 2.5f));    // simplified and unsimplified polynomials should have equal outputs

    printf("A solution to p is x = %f\n", solve_polynomial(p, -2, 5, 0.01f));

    remove_all_terms(&p);
    remove_all_terms(&dp);
    */

    // TEST #2:
    /*
    term_t* p = NULL;
    printf("One possible solution to p is x = %f\n", solve_polynomial(p, -2, 5, 0.01f));  // <- correctly returns an error

    add_term(&p, -1, 2);    // 1 - x^2
    add_term(&p, 1, 0);
    log_polynomial(p);

    printf("One possible solution to p is x = %f\n", solve_polynomial(p, -2, 5, 0.01f));    // x ~ -1
    printf("One possible solution to p is x = %f\n", solve_polynomial(p, 2, 5, 0.01f));     // x ~ 1
    */
    
    // TEST #3:
    /*
    term_t* p1 = NULL, *p2 = NULL;
    add_polynomials(&p1, &p2);  // <- function identifies that adding NULL ptrs makes no sense
    subtract_polynomials(&p1, &p2); // <- this as well

    add_term(&p1, 1, 2);
    add_term(&p1, 4, 1);
    add_term(&p1, 4, 0);      // p1: 4 + 4x + x^2
    log_polynomial(p1);
    reverse_polynomial(&p1);  // p1: x^2 + 4x + 4
    log_polynomial(p1);
    add_term(&p2, -12, 0);
    add_term(&p2, 4, 1);      // p2: 4x - 12
    subtract_polynomials(&p1, &p2);
    simplify_polynomial(&p1);
    log_polynomial(p1);       // p1 - p2: x^2 + 16

    printf("One possible solution to p is x = %f\n", solve_polynomial(p1, 1, 5, 0.01f));  // returns an incorrect answer when p has no real solutions
    add_term(&p1, -8, 1);
    sort_polynomial(&p1);     // p1: x^2 - 8x + 16
    log_polynomial(p1);   
    printf("One possible solution to p is x = %f\n", solve_polynomial(p1, 2, 10, 0.001f));  // x ~ 4
    remove_all_terms(&p1);
    */
    
    // TEST #4:
    /*
    term_t* p = NULL;
    add_term(&p, 2, 0);
    add_term(&p, -2, 1);
    add_term(&p, 1, 3);      // p: x^3 - 2x + 2
    log_polynomial(p);

    printf("One possible solution to p is x = %f\n", solve_polynomial(p, 1, 4, 0.01f));  // some initial points cause the algorithm to enter into a cycle
    printf("One possible solution to p is x = %f\n", solve_polynomial(p, -1, 10, 0.01f)); // x ~ -1.769
    remove_all_terms(&p);
    */
    

    getchar();
    return 0;
}