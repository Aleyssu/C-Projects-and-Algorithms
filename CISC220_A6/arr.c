#include <stdlib.h>
#include <stdio.h>
#include "arr.h"

/*
 * Reads count int values from f storing the values in 
 * the specified array.
 *
 * Does not close the file f.
 */
void arr_readn(FILE *f, size_t count, int *arr) {
    int c;
    for (int i = 0; i < count; i++) {
        if (fscanf(f, "%d", &c)) {
            arr[i] = c;
        }
        else {
            break;
        }
    }
}


/*
 * Reads characters from f storing the characters in the array 
 * pointed at by s. Stops reading when a newline character '\n' 
 * is reached, or when max_length characters are read. A newline
 * character is never stored in the array pointed at by s.
 * A null terminator is always stored to indicate the end of the
 * string.
 *
 * Returns true if a newline character is reached (indicating
 * that an entire line of the file was read), or if the max length 
 * is exceeded. Returns false if reading from the file failed for 
 * some reason.
 *
 * Does not close the file f.
 */
bool arr_readline(FILE *f, size_t max_length, char *s) {
    int c;
    for (int i = 0; i < max_length; i++) {
        c = fgetc(f);
        if (c != EOF) {
            if (c != '\n') {
                s[i] = c;
            }
            else {
                s[i] = '\0';
                return true;
            }
        }
        else {
            return false;
        }
    }
	s[max_length] = '\0';
    return true;
}


/*
 * Extracts integer values from a string where the integer values
 * are separated from one another by a single comma (no spaces).
 * The integer values are returned in a newly allocated array
 * having capacity exactly equal to the number of integers extracted.
 * The number of extracted integers is written into the object
 * pointed at by n.
 */
int *arr_fromstr(const char *s, size_t *n) {
    *n = 1;
    // Count the number of commas in s and store the result in n
    for (int i = 0; s[i]; s[i++] == ',' ? (*n)++ : false); 

    int *arr = malloc(*n * sizeof(int));
    int i = 0;
    int c;

    char *ptr = (char*) s;
    // Read the first int and put it into arr
    sscanf(s, "%d%n", &arr[i++], &c);
    ptr += c;

    // Read for a comma followed by an int which we write into arr
    while (sscanf(ptr, ",%d%n", &arr[i++], &c) != EOF) {
        ptr += c;
    }

    return arr;
}


/*
 * Uncompresses the n element compressed array enc returning
 * a pointer to the first element of a new array
 * containing the uncompressed array. Writes the length of the
 * uncompressed array into the object pointed at by dec_len.
 *
 * The returned array has no excess capacity (i.e.,
 * all values in the returned array are meaningful).
 */
int *arr_decode(size_t n, const int *enc, size_t *dec_len) {
    *dec_len = 0;
    // Find the length of the unencoded array
    for (int i = 0; i < n; i += 2) {
        *dec_len += enc[i];
    }

    int *dec = malloc(*dec_len * sizeof(int));
    int j = 0;
    int curr;
    // Decode and store results in dec
    for (int i = 0; i < n; i += 2) {
        curr = enc[i + 1];
        for (int k = 0; k < enc[i]; k++) {
            dec[j++] = curr;
        }
    }

    return dec;
}


