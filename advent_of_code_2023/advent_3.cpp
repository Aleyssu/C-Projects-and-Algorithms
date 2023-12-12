#include <iostream>
#include <fstream>
#include <string>
using namespace std;

bool is_symbol(char c) {
    return c != '.' && (c < '0' || c > '9');
}

/*
 * Checks for symbols adjacent or diagonal to an integer in the middle array, 
 * given the starting index of said integer.
 * 
 * Returns the number if a symbol is found, and 0 otherwise.
*/
int is_near_symbol(string (&line)[3], int i) {
    bool valid = false;
    int num = 0;
    char c = line[1][i];

    // Needs fixing
    
    // // Check left adjacent and diagonal characters
    // if (i != 0 && (is_symbol(line[1][i - 1]) || is_symbol(line[0][i - 1]))) {
    //     valid = true;
    // }
    // do {
    // num = num * 10 + (c - '0');

    // // Check vertical adjacent characters
    // if (!valid && (is_symbol(line[1][i]))) valid = true;

    // c = line[0][++i];
    // } while (c <= '9' && c >= '0');

    // // Check right adjacent and diagonal characters
    // if (!valid && line[1].size() > i && (is_symbol(line[1][i]) || is_symbol(line[0][i]))) {
    //     valid = true;
    // }
}

// Part one of the day's solutions - assumes that every line is the same length.
int part_1(istream &f) {
    string line[3];
    char c;
    int i, num;
    bool valid;

    getline(f, line[0]);
    while (getline(f, line[1])) {
        i = 0;
        c = line[0][0];
        if (c <= '9' && c >= '0' && is_near_symbol(line, i)) {
            cout << num << '\n';
        }
        
        swap(line[0], line[1]);
    }

    return 0;
}

int main() {
    ifstream f("advent_3.txt");    

    part_1(f);
}