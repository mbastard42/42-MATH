#pragma once

#include "utils.h"

//  EQUATION.C

/**
 * @brief   Structure representing an equation.
 * 
 * @param   init    1 if the equation is initialized, 0 otherwise
 * @param   lsh     Left-hand side of the equation
 * @param   rsh     Right-hand side of the equation
 */
typedef struct s_eqtn {

    int         sol;
    int         dis;
    int         deg;
    int *       lsh;
    int *       rsh;
    double      x[2];
    double      i[2];
    
}   t_eqtn;

/**
 * @brief   Creates a new equation.
 * 
 * @param   deg Degree of the equation
 * @param   lsh Left-hand side of the equation
 * @param   rsh Right-hand side of the equation
*/
t_eqtn *    new_eqtn(int deg, int * lsh, int * rsh);
/**
 * @brief   Deletes an equation.
 * 
 * @param   eqtn Equation to delete
 */
void        del_eqtn(t_eqtn * eqtn);
/**
 * @brief   Prints an equation.
 * 
 * @param   eqtn Equation to print
 */
void        print_eqtn(t_eqtn * eqtn);

//  PARSING.C

/**
 * @brief   Removes all spaces from the input string.
 * 
 * @param   input Input string
 * @return  Newly allocated string containing the cleaned string
 */
char *      cleaner(char * input);
/**
 * @brief   Checks if the input string is valid.
 * 
 * @param   input Input string
 * @return  1 if the input string is valid, 0 otherwise
 */
int         checker(char * input);
/**
 * @brief   Lexes the input string and returns an array of tokens.
 * 
 * @param   input Input string
 * @return  Array of tokens
 */
char ***    lexer(char * input);
/**
 * @brief   Parses the tokens and returns an equation.
 * 
 * @param   tokens Array of tokens
 * @return  Equation
 */
t_eqtn *    parser(char *** tokens);

//  SOLVER.C

t_eqtn *    solve_polynomial(char * equation);
