#include <stdio.h>
#include <stdbool.h>
#include "helper.h"

int seeki(FILE *f) {
    char c = fgetc(f);
    while (c > '9' || c < '0') {
        c = fgetc(f);
    }
    return c - '0';
}

bool seekc(FILE *f, char target) {
    for (int c = fgetc(f); c != '\n' && c != EOF; c = fgetc(f)) {
        if (c == target) {
            return true;
        }
    }
    return false;
}