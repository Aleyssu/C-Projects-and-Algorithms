#include <stdlib.h>
#include <stdio.h>
#include "arr.h"

/**
 * Takes the name of a file containing:
 * 
 * -An integer at the beginning stating n number of lines to be processed
 * 
 * -n lines of run-length encoded bit arrays, with each number separated
 * by a ','
 * 
 * For each '1', prints a #. 
 * For each '0', prints an empty space.
 * A new line is printed for every line.
 * 
 * Ex. given the file:
 * 
 * 2
 * 2,1,1,0,2,1
 * 4,0,1,1
 * 
 * Prints:
 * 
 * ## ##
 *     #
*/
int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: arr_demo filename\n");
        exit(1);
    }
    FILE *f = fopen(argv[1], "r");
    
    if (!f) {
        fprintf(stderr, "Cannot open %s for reading\n", argv[1]);
        exit(2);
    }
    
    // Get number of lines to read from the file
    int lines;
    arr_readn(f, 1, &lines);
    
    // Clear out the first line
    char charray[10];
    fgets((char*) &charray, 10, f);

    // Decoding and printing
    char *arr = malloc(100);
    size_t n, dec_n;
    for (int i = 0; i < lines; i++) {
        arr_readline(f, 100, arr);
        int *enc = arr_fromstr(arr, &n);
        int *dec = arr_decode(n, enc, &dec_n);
        
        for (int j = 0; j < dec_n; dec[j++] ? printf("#") : printf(" "));
        puts("");

        free(enc);
        free(dec);
    }

    free(arr);
    fclose(f);
}