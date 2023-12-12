#include <stdio.h>
#include <stdbool.h>

/**
 * Solutions for the 2023 Advent of Code day 1
 * 
 * https://adventofcode.com/2023/day/1
*/

// Used in part_2 to aid in word matching
static int match_limits[] = {2, 2, 4, 3, 3, 2, 4, 4, 3};
static char *nums[] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

/** 
 * Finds the first and last integer of each line in the given file, 
 * combining them into a two digit number. Returns the sum of all
 * the two digit numbers from every line.
*/
int part_1(FILE *f) {
    rewind(f);
    int curr;
    int firstchr = 0; 
    int lastchr = 0;
    int sum = 0;

    curr = fgetc(f);
    while (curr != EOF) {
        firstchr = 0;
        lastchr = 0;
        // Iterating through the characters in the line
        for (; curr != EOF && curr != '\n'; curr = fgetc(f)) {
            if (curr > '0' && curr <= '9') {
                if (!firstchr) {
                    firstchr = curr - '0';
                }
                lastchr = curr - '0';
            }
        }
        sum += firstchr * 10 + lastchr;
        curr = fgetc(f);
    }

    return sum;
}

/** 
 * Works similarly to part_1, but integers spelt out as words from 1-9 
 * ex. "one", "two" are also counted.
*/
int part_2(FILE *f) {
    rewind(f);
    // Stores the number of consecutive char matches 
    // corresponding to the number represented by the index + 1.
    int matches[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

    int curr;
    int firstchr = 0; 
    int lastchr = 0;
    int sum = 0;

    curr = fgetc(f);
    while (curr != EOF) {
        firstchr = 0;
        lastchr = 0;
        // Iterating through the characters in the line
        for (; curr != EOF && curr != '\n'; curr = fgetc(f)) {
            // Match for literal numbers
            if (curr > '0' && curr <= '9') {
                if (!firstchr) {
                    firstchr = curr - '0';
                }
                lastchr = curr - '0';
                // Reset the match array
                for(int i = 0; i < 9; matches[i++] = 0);
            }
            // Match for word numbers
            else {
                for(int i = 0; i < 9; i++) {
                    if(curr == nums[i][matches[i]]) {
                        // Full match has been found
                        if(match_limits[i] == matches[i]++) {
                            if (!firstchr) {
                                firstchr = i + 1;
                            }
                            lastchr = i + 1;
                            matches[i] = 0;
                        }
                    }
                    else if(curr == nums[i][0]) {
                        matches[i] = 1;
                    }
                    else {
                        matches[i] = 0;
                    }
                }
            }
        }
        // Reset the match array
        for(int i = 0; i < 9; matches[i++] = 0);

        sum += firstchr * 10 + lastchr;
        curr = fgetc(f);
    }

    return sum;
}

void main() {
    FILE *f = fopen("advent_1.txt", "r");

    printf("Part 1 Solution: %d\n", part_1(f));
    printf("Part 2 Solution: %d\n", part_2(f));

    fclose(f);
}