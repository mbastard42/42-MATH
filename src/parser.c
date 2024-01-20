#include "./.computor.h"

char ** lexer(char * input) {

    char ** tmp = split(input, " ", ":");
    
    for (int i = 0; tmp && tmp[i]; i++)
        printf("tab[%d] = %s\n", i, tmp[i]);

    return (NULL);
}

char ** parser(char ** tokens) {

    if (!tokens)
        return (NULL);

    printf("parser\n");
    (void)tokens;

    return (NULL);
}