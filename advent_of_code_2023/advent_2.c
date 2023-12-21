#include <stdio.h>
#include "helper.h"

/**
 * Solutions for the 2023 Advent of Code day 2
 * 
 * https://adventofcode.com/2023/day/2
*/

/*
 * Returns the number of games in the file which can be played with at most r, g, b
 * cubes of colors red, green, and blue respectively. 
*/
int part_1(FILE *f, int r, int g, int b) {
    rewind(f);
    int game = 1;
    int num;
    bool viable_game = true;
    char color;
    int sum = 0;

    for (int c = fgetc(f); c != EOF; c = fgetc(f)) {
        // Read through each line, skipping past the first colon
        seekc(f, ':');
        while (c != '\n' && c != EOF) {
            fscanf(f, "%d %c", &num, &color);
            
            switch (color) {
                case 'r':
                    if (num > r) {
                        viable_game = false;
                    }
                    break;
                case 'g':
                    if (num > g) {
                        viable_game = false;
                    }
                    break;
                case 'b':
                    if (num > b) {
                        viable_game = false;
                    }
                    break;
                default:
                    printf("Color detection error on game %d\n", game);
            }
            
            if (!viable_game) {
                viable_game = true;
                // Skip to the next line
                for (c = fgetc(f); c != EOF && c != '\n'; c = fgetc(f));
            }
            else {
                // Move to the next (number color) pair
                for (c = fgetc(f); c != ' '; c = fgetc(f)) {
                    // If we've gotten to the end of the line, then the game
                    // must be viable - add it to the sum.
                    if (c == EOF || c == '\n') {
                        sum += game;
                        // printf("%d\n", game);
                        break;
                    }
                }
            }
        }
        game++;
    }

    return sum;
}


/*
 * Returns the sum of the powers of cubes from each game in the given file. 
*/
int part_2(FILE *f) {
    rewind(f);
    int num, game = 0, sum = 0;
    int r = -1, g = -1, b = -1;
    char color;

    for (int c = fgetc(f); c != EOF; c = fgetc(f)) {
        // Read through each line, skipping past the first colon
        seekc(f, ':');
        while (c != '\n' && c != EOF) {
            fscanf(f, "%d %c", &num, &color);
            
            switch (color) {
                case 'r':
                    if (num > r) {
                        r = num;
                    }
                    break;
                case 'g':
                    if (num > g) {
                        g = num;
                    }
                    break;
                case 'b':
                    if (num > b) {
                        b = num;
                    }
                    break;
                default:
                    printf("Color detection error on game %d\n", game);
            }
            // Move to the next (number color) pair
            for (c = fgetc(f); c != ' '; c = fgetc(f)) {
                // End of line reached; time to process the results
                if (c == EOF || c == '\n') {
                    sum += r * g * b;
                    r = 0, g = 0, b = 0;
                    // printf("%d\n", game);
                    break;
                }
            }
        }
        game++;
    }
    return sum;
}

void main() {
    FILE *f = fopen("advent_2.txt", "r");
    if (!f) {
        puts("Couldn't read the file");
        return;
    }

    printf("Part 1: %d\n", part_1(f, 12, 13, 14));
    printf("Part 2: %d\n", part_2(f));
	fclose(f);
}