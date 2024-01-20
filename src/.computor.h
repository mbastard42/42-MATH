#pragma once

#include <stdio.h>
#include "utils/.utils.h"

char ** lexer(char * input);
char ** parser(char ** tokens);
char ** solve_polinomial(char * equation);