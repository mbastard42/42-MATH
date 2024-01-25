#include "../inc/computor.h"

t_eqtn *    new_eqtn(int deg, int * lsh, int * rsh) {

    t_eqtn * eqtn;

    if (!(eqtn = malloc(sizeof(t_eqtn)))) {
        errno = ENOMEM; perror("new_eqtn()"); return NULL;
    }

    eqtn->sol = 0;
    eqtn->dis = 0;
    eqtn->deg = deg;

    if (!(eqtn->lsh = calloc(deg + 1, sizeof(int)))) {
        free(eqtn);
        errno = ENOMEM; perror("new_eqtn()"); return NULL;
    }

    if (!(eqtn->rsh = calloc(deg + 1, sizeof(int)))) {
        free(eqtn->lsh);
        free(eqtn);
        errno = ENOMEM; perror("new_eqtn()"); return NULL;
    }

    for (int i = 0; i < deg + 1; i++)
        eqtn->lsh[i] = lsh[i] - rsh[i];

    while (!eqtn->lsh[eqtn->deg] && eqtn->deg > 0)
        eqtn->deg--;

    return eqtn;
}

void        del_eqtn(t_eqtn * eqtn) {

    if (eqtn) {

        if (eqtn->lsh)
            free(eqtn->lsh);
        if (eqtn->rsh)
            free(eqtn->rsh);
        free(eqtn);
    }
}

void        print_eqtn(t_eqtn * eqtn) {

    if (eqtn) {

        for (int i = 0; i < eqtn->deg + 1; i++) {

            if (!i && eqtn->lsh[i] < 0)
                printf("-");
            if (eqtn->lsh[i] != 1 && eqtn->lsh[i] != -1)
                printf("%d", abs(eqtn->lsh[i]));
            if (i)
                printf("x^%u", i);
            if (i < eqtn->deg && eqtn->lsh[i + 1] >= 0)
                printf(" + ");
            if (i < eqtn->deg && eqtn->lsh[i + 1] < 0)
                printf(" - ");
        }
        printf(" = 0");
    }
}