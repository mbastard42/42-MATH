#include "../inc/computor.h"

static double sqrt(double x) {

    double guess = x;
    double epsilon = 1e-6;
    double tmp = guess * guess - x * (guess * guess - x > 0 ? 1 : -1);

    while (tmp > epsilon) {

        guess = 0.5 * (guess + x / guess);
        tmp = guess * guess - x * (guess * guess - x > 0 ? 1 : -1);
    }

    return guess;
}

static void deg1_resolver(t_eqtn * eqtn) {

    eqtn->sol = 1;
    eqtn->x[0] = (double) -eqtn->lsh[0] / (double) eqtn->lsh[1];
}

static void deg2_resolver(t_eqtn * eqtn) {

    eqtn->dis = (double) eqtn->lsh[1] * (double) eqtn->lsh[1] - 4 * (double) eqtn->lsh[0] * (double) eqtn->lsh[2];

    if (eqtn->dis > 0) {

        eqtn->sol = 2;
        eqtn->x[0] = (double) (-eqtn->lsh[1] + sqrt(eqtn->dis)) / (2 * eqtn->lsh[2]);
        eqtn->x[1] = (double) (-eqtn->lsh[1] - sqrt(eqtn->dis)) / (2 * eqtn->lsh[2]);
    }
    else if (eqtn->dis == 0) {

        eqtn->sol = 1;
        eqtn->x[0] = (double) -eqtn->lsh[1] / (2 * eqtn->lsh[2]);
    }
    else {
            
        eqtn->sol = 2;
        eqtn->x[0] = (double) -eqtn->lsh[1] / (2 * eqtn->lsh[2]);
        eqtn->i[0] = (double) sqrt(-eqtn->dis) / (2 * eqtn->lsh[2]);
        eqtn->x[1] = (double) -eqtn->lsh[1] / (2 * eqtn->lsh[2]);
        eqtn->i[1] = (double) -sqrt(-eqtn->dis) / (2 * eqtn->lsh[2]);
    }
}

t_eqtn *    solve_polynomial(char * equation) {
    
    t_eqtn *    eqtn = NULL;
    char *      input = cleaner(equation);
    
    if (!checker(input)) {
        
        char *** tokens = lexer(input);
        
        eqtn = parser(tokens);
        if (eqtn->deg == 1)
            deg1_resolver(eqtn);
        else if (eqtn->deg == 2)
            deg2_resolver(eqtn);

        freetab(tokens[0]);
        freetab(tokens[1]);
        if (tokens)
            free(tokens);
    }

    free(input);
    return eqtn;
}