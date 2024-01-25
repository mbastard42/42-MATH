#pragma once

#include <ctype.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

//  UTILS.C

/**
 * @brief   Calculates the length of the substring in [str] until a character
 * from [set] is encountered.
 *
 * @param   str Original string
 * @param   set Set of characters to search for
 * @return  Length of the substring until a character from [set] is found
 */
size_t  sublen(const char * str, const char * set);
/**
 * @brief   Extracts a substring from [str] starting at index [start] with a
 * specified length [len].
 *
 * @param   str Original string
 * @param   start Starting index of the substring
 * @param   len Length of the substring to extract
 * @return  Newly allocated string containing the extracted substring
 */
char *  substr(const char * str, const size_t start, const size_t len);
/**
 * @brief   Removes all [set] characters from [str].
 *
 * @param   str Original string
 * @param   set Set of characters to remove
 * @return  Newly allocated string containing the cleaned string
 */
char *  cleanstr(const char * str, const char * set);
/**
 * @brief   Frees a NULL-terminated array of strings.
 *
 * @param   tab Array of strings
 */
void    freetab(char ** tab);
/**
 * @brief   Splits the string [str] at characters specified by [set].
 *
 * @param   str     String to be split
 * @param   set     Delimiting characters
 *
 * @return  Array of strings
 */
char ** split(const char * str, const char * set);
