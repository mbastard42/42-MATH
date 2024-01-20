#include "./.computor.h"

int main(int argc, char ** argv) {
    
    char ** result = (argc == 2) ? solve_polinomial(argv[1]) : NULL;

    if (result) {

        printf("Reduced form: %s\n", result[0]);
        printf("Polynomial degree: %s\n", result[1]);
        printf("Discriminant: %s\n", result[2]);
        printf("Solution: %s\n", result[3]);
        return 0;
    }
    printf("Usage: ./computor \"equation\"\n");        
    return 1;
}