#include <iostream>
#include <fstream>
#include <string>
using namespace std;

/**
 * Solutions for the 2023 Advent of Code day 3
 * 
 * https://adventofcode.com/2023/day/3
 * 
 * This is the first problem (first file, in fact) that I've coded in C++.
*/

// Returns true if char is a "symbol" (not a period or a number); false otherwise.
bool is_symbol(char c) {
    return c != '.' && (c < '0' || c > '9');
}

// Returns true if char is a number; false otherwise.
bool is_num(char c) {
    return c >= '0' && c <= '9';
}

/*
 * Checks for symbols adjacent or diagonal to an integer in the middle string, 
 * given the starting index of said integer.
 * 
 * Returns the number if a symbol is found, and 0 otherwise.
*/
int sym_near_num(string (&line)[3], int &i) {
    bool valid = false;
    int num = 0;
    char c = line[1][i];
    // Check left adjacent and diagonal characters
    if (i != 0 && (is_symbol(line[0][i - 1]) || is_symbol(line[1][i - 1]) || is_symbol(line[2][i - 1]))) {
        valid = true;
    }

    do {
        num = num * 10 + (c - '0');
        // Check vertical adjacent characters
        if (!valid && (is_symbol(line[0][i]) || is_symbol(line[2][i]))) valid = true;
        c = line[1][++i];
    } while (is_num(c));

    // Check right adjacent and diagonal characters
    if (!valid && line[1].size() > i && (is_symbol(line[0][i]) || is_symbol(line[1][i]) || is_symbol(line[2][i]))) {
        valid = true;
    }
    if (valid) {
        return num;
    }  
    else return 0;
}

// Part one of the day's solutions - assumes that every line is the same length.
int part_1(istream &f) {
    f.clear();
    f.seekg(0);
    string line[3];
    char c;
    int i, num, sum = 0;
    bool valid, not_end_of_line;

    getline(f, line[1]);
    // Create virtual line of '.' chars at the beginning of the file to pad for the algorithm
    line[0] = string(line[1].length(), '.');
    // Reading line by line
    do {
        not_end_of_line = (bool) getline(f, line[2]);
        // Create virtual line of '.' chars at the end of the file to pad for the algorithm
        if (!not_end_of_line) {
            line[2] = string(line[1].length(), '.');
        }
        i = 0;
        c = line[1][0];
        // Read till end of line (null terminator)
        while (c) {
            if (is_num(c)) {
                sum += sym_near_num(line, i);
            }
            c = line[1][++i];
        }
        // Shift lines up to make space in line[2] to read the next line 
        line[0] = line[1];
        line[1] = line[2];
    } while (not_end_of_line);

    return sum;
}

/*
 * Checks if there're exactly two numbers adjacent or diagonal to a symbol in the middle array, 
 * given the index of said symbol.
 * 
 * Returns the product of the two numbers if they're found, and 0 otherwise.
*/
int nums_near_sym(string (&line)[3], int &i) {
    int nums_found = 0;
    
    // Check left characters
    if (i != 0) {
        nums_found += (is_num(line[0][i - 1]) && !is_num(line[0][i]))
                    + is_num(line[1][i - 1])
                    + (is_num(line[2][i - 1]) && !is_num(line[2][i]));
    }

    // Check right characters
    if (i + 1 < line[0].length()) {
        nums_found += (is_num(line[0][i + 1]) && !is_num(line[0][i]))
                    + is_num(line[1][i + 1])
                    + (is_num(line[2][i + 1]) && !is_num(line[2][i]));
    }

    // Check vertical adjacent characters
    nums_found += is_num(line[0][i]) + is_num(line[2][i]);

    // If there are exactly two numbers, find them and compute their products 
    if (nums_found == 2) {
        int range, begin;
        if(i == 0) {
            range = i + 2;
            begin = i;
        }
        else if (i + 1 == line[0].length()) {
            range = i + 1;
            begin = i - 1;
        }
        else {
            range = i + 2;
            begin = i - 1;
        }

        int nums[2];
        for (int j = 0; j < 3; j++) {
            for (i = begin; i < range; i++) {
                if (is_num(line[j][i])) {
                    int num = 0, factor = 1, p = i;
                    // Traverse left
                    do {
                        num += factor * (line[j][p] - '0');
                        factor *= 10;
                        p--;
                    } while (is_num(line[j][p]));
                    // Traverse right
                    i++;
                    while (is_num(line[j][i])) {
                        num = num * 10 + (line[j][i] - '0');
                        i++;
                    }
                    // Compute final result
                    nums_found--;
                    nums[nums_found] = num;
                    if (nums_found == 0) {
                        // cout << nums[1] << " " << nums[0] << '\n';
                        return nums[0] * nums[1];
                    } 
                }
            }
        }

        cout << "Someone tell Vedal there's a problem with my AI.\n";
        return 0;
    }
    else return 0;
}

// Part two of the day's solutions - assumes that every line is the same length.
int part_2(istream &f) {
    f.clear();
    f.seekg(0);
    string line[3];
    char c;
    int i, num, sum = 0;
    bool valid, not_end_of_line;

    getline(f, line[1]);
    // Create line of '.' chars at the beginning to pad for the algorithm
    line[0] = string(line[1].length(), '.');
    // Reading line by line
    do {
        not_end_of_line = (bool) getline(f, line[2]);
        // Create line of '.' chars at the end to pad for the algorithm
        if (!not_end_of_line) {
            line[2] = string(line[1].length(), '.');
        }
        i = 0;
        c = line[1][0];
        // Read till end of line (null terminator)
        while (c) {
            if (is_symbol(c)) {
                sum += nums_near_sym(line, i);
            }
            c = line[1][++i];
        }
        // Shift lines up to make space in line[2] to read the next line 
        line[0] = line[1];
        line[1] = line[2];
    } while (not_end_of_line);

    return sum;
}


int main() {
    ifstream f("advent_3.txt");    

    cout << "Part 1: " << part_1(f) << '\n';
    cout << "Part 2: " << part_2(f) << '\n';
    f.close();
}