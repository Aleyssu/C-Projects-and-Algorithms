#include <stdio.h>
#include <stdbool.h>

#ifndef HELPER_H
#define HELPER_H

/** 
 * Seeks the first integer in the file, returning the found 
 * int (or -1 if not found)
*/
int seeki(FILE *f);

/**
 * Seeks to the position of the first occurence of the target char in 
 * the current line of the given file, returning true if found, else false.
 */
bool seekc(FILE *f, char target);

#endif