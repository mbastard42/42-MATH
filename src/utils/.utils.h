#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//  STRING.C

/**
 * @brief   Calculates the length of the substring in [str] until a character from [set] is encountered.
 *
 * @param   str Original string
 * @param   set Set of characters to search for
 * @return  Length of the substring until a character from [set] is found
 */
size_t  sublen(const char * str, const char * set);
/**
 * @brief   Extracts a substring from [str] starting at index [start] with a specified length [len].
 * 
 * @param   str Original string
 * @param   start Starting index of the substring
 * @param   len Length of the substring to extract
 * @return  Newly allocated string containing the extracted substring
 */
char *  substr(const char *str, const size_t start, const size_t len);

//  SPLIT.C

/**
 * @brief   Splits the string [str] at characters specified by [set], 
 *          except when enclosed between two identical characters specified by [xpt].
 * 
 * @param   str String to be split
 * @param   set Delimiting characters
 * @param   xpt Exceptions characters
 * 
 * @return  Array of strings
 */
char ** split(const char *str, const char *set, const char *xpt);
