#include "../inc/computor.h"

static void print_result(t_eqtn * eqtn) {

    printf("Reduced form: ");
    print_eqtn(eqtn);
    printf("\nPolynomial degree: %d\n", eqtn->deg);
    if (eqtn->deg == 0)
        printf("All real numbers are solution.\n");
    else if (eqtn->deg == 1)
        printf("Solution: %g\n", (double) eqtn->x[0]);
    else if (eqtn->deg == 2) {
            
        if (eqtn->dis > 0)
            printf("Discriminant is strictly positive, the two solutions are:\n%g\n%g\n", (double) eqtn->x[0], (double) eqtn->x[1]);
        else if (eqtn->dis == 0)
            printf("Discriminant is null, the solution is:\n%g\n", (double) eqtn->x[0]);
        else if (eqtn->dis < 0) {
            
            printf("Discriminant is strictly negative, the two solutions are:\n");
            printf("%g + %gi\n", (double) eqtn->x[0], (double) eqtn->i[0]);
            printf("%g - %gi\n", (double) eqtn->x[1], (double) eqtn->i[1] * -1);
        }
    }
    else
        printf("The polynomial degree is stricly greater than 2, I can't solve.\n");

}

int main(int argc, char ** argv) {
    
    if (argc != 2) {

        printf("Usage: ./computor \"equation\"\n");
        return 1;
    }

    t_eqtn * eqtn = solve_polynomial(argv[1]);

    if (eqtn) {

        print_result(eqtn);
        del_eqtn(eqtn);
    }

    return 0;
}
