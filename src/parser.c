#include "../inc/computor.h"

char *           cleaner(char * input) {

    char * clean = cleanstr(input, " ");

    for (size_t i = 0; clean[i]; i++)
        clean[i] = tolower(clean[i]);

    return (clean);
}

int              checker(char * input) {

    int error = 0;
    int equal = 0;

    if (!input || !*input)
        error = 1;
    if (!error && (!sublen(input, "=") || input[strlen(input) - 1] == '=' || !strchr(input, 'x')))
        error = 2;
    if (!error && (input[0] == '*' || input[strlen(input) - 1] == '*'))
        error = 8;
    for (size_t i = 0; !error && input[i]; i++) {

        if (input[i] == '=')
            equal++;
        else if (!strchr(" x=+-*^0123456789", input[i]))
            error = 3;
        else if (input[i] == 'x' && input[i + 1] && !strchr("=+-*^", input[i + 1]))
            error = 4;
        else if (input[i] == '^' && (!input[i + 1] || (input[i + 1] && !strchr("+0123456789", input[i + 1]))))
            error = 5;
        else if (input[i] == '^' && (!input[i - 1] || input[i - 1] != 'x'))
            error = 6;
        else if (strchr("+-*", input[i]) && (!input[i + 1] || (input[i + 1] && !strchr("x0123456789", input[i + 1]))))
            error = 7;
        else if (input[i] == '*' && (strchr("0123456789", input[i - 1]) && input[i + 1] && strchr("0123456789", input[i + 1])))
            error = 8;
    }
    if (!error && equal != 1)
        error = 9;

    if (error) {

        errno = EINVAL;
        switch (error) {
            case 1:
                perror("Empty equation"); break;
            case 2:
                perror("Nothing to solve"); break;
            case 3:
                perror("Equation must contain only \" Xx=+-*^0123456789\""); break;
            case 4:
                perror("\'x\' must be followed by \"=+-*^\""); break;
            case 5:
                perror("\'^\' must be followed by a positif number"); break;
            case 6:
                perror("Only \'x\' can be followed by a \'^\'"); break;
            case 7:
                perror("\"+-*^\" must be followed by \'x\' or a number"); break;
            case 8:
                perror("Can only multiply \'x\' with a number"); break;
            case 9:
                perror("Equation must contain (only) one \'=\'"); break;
        }   
    }
    return error;
}

char ***         lexer(char * input) {

    size_t  count = 0;
    char *  del = NULL;
    
    for (size_t i = 0; input[i]; i++)
        if (strchr("+-", input[i]) && (!i || input[i - 1] != '^'))
            count++;

    if (!(del = (char *) calloc(strlen(input) + count + 1, sizeof(char)))) {
        errno = ENOMEM; perror("lexer(put_delimiter())"); return (NULL);
    }

    for (size_t i = 0, j = 0; input[i]; i++, j++) {

        if (strchr("+-", input[i]) && (!i || input[i - 1] != '^'))
            del[j++] = '|';
        del[j] = input[i];
    }

    char ***    tokens = NULL;

    if (!(tokens = (char ***) calloc(3, sizeof(char **)))) {
        errno = ENOMEM; perror("lexer()"); return (NULL);
    }

    char ** tmp = split(del, "=");
    free(del);

    tokens[0] = split(tmp[0], "|");
    tokens[1] = split(tmp[1], "|");
    freetab(tmp);

    return (tokens);
}

static int **    tokens_tab(char *** tokens) {

    int         tmp = 0;
    int         deg = 0;
    int **      tab = NULL;

    for (size_t i = 0; tokens[i]; i++) {

        for (size_t j = 0; tokens[i][j]; j++) {

            if (tokens[i][j][0] == 'x' || atoi(tokens[i][j])) {

                tmp = 0;
                if (tokens[i][j][sublen(tokens[i][j], "^")])
                    tmp = atoi(&tokens[i][j][sublen(tokens[i][j], "^") + 1]);
                else if (strchr(tokens[i][j], 'x'))
                    tmp = 1;

                deg = (tmp > deg) ? tmp : deg;
            }
        }
    }
    
    if (!(tab = (int **) calloc(3, sizeof(int *)))) {
        errno = ENOMEM; perror("parser()"); return NULL;
    }

    if (!(tab[0] = (int *) calloc(1, sizeof(int)))) {

        free(tab);
        errno = ENOMEM; perror("parser()"); return NULL;
    }

    if (!(tab[1] = (int *) calloc(deg + 1, sizeof(int)))) {

        free(tab[0]);
        free(tab);
        errno = ENOMEM; perror("parser()"); return NULL;
    }
    
    if (!(tab[2] = (int *) calloc(deg + 1, sizeof(int)))) {

        free(tab[0]);
        free(tab[1]);
        free(tab);
        errno = ENOMEM; perror("parser()"); return NULL;
    }

    tab[0][0] = deg;

    return tab;
}

t_eqtn *         parser(char *** tokens) {

    int      deg = 0;
    int **   tab = tokens_tab(tokens);

    if (!tab)
        return NULL;

    for (size_t i = 0; tokens[i]; i++) {

        for (size_t j = 0; tokens[i][j]; j++) {

            if (tokens[i][j][0] == 'x' || (strchr("-+", tokens[i][j][0]) && tokens[i][j][1] == 'x') || atoi(tokens[i][j])) {

                deg = 0;
                if (tokens[i][j][sublen(tokens[i][j], "^")])
                    deg = atoi(&tokens[i][j][sublen(tokens[i][j], "^") + 1]);
                else if (strchr(tokens[i][j], 'x'))
                    deg = 1;
                
                if (tokens[i][j][0] == 'x' || (tokens[i][j][0] == '+' && tokens[i][j][1] == 'x'))
                    tab[i + 1][deg] += 1;
                else if (tokens[i][j][0] == '-' && tokens[i][j][1] == 'x')
                    tab[i + 1][deg] -= 1;
                else
                    tab[i + 1][deg] += atoi(tokens[i][j]);
            }
        }
    }

    t_eqtn * eqtn = new_eqtn(**tab, tab[1], tab[2]);

    free(tab[0]);
    free(tab[1]);
    free(tab[2]);
    free(tab);

    return eqtn;
}
