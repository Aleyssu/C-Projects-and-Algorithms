#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h>
using namespace std;

/**
 * Solutions for the 2023 Advent of Code day 4
 * 
 * https://adventofcode.com/2023/day/4
*/

// Node class for the Queue
template <typename T>
class Node {
    public:
        T val;
        Node* next;
        Node(const T elem) : val(elem), next(nullptr) {};
};

// For part 2; queue which allows direct access to the internal nodes
template <typename T>
class Queue {
    public:
        Node<T>* head;
        Node<T>* tail;
        size_t size;

        Queue() : head(nullptr), tail(nullptr), size(0) {};

        ~Queue() {
            Node<T>* curr = head;
            Node<T>* temp;
            while (curr) {
                temp = curr;
                delete temp;
                curr = curr->next;
            }
        }

        void enqueue(T val) {
            if (!head) {
                head = new Node<T>(val);
                tail = head;
            }
            else {
                tail->next = new Node<T>(val);
                tail = tail->next;
            }
            size++;
        }

        T dequeue() {
            if (head) {
                T result = head->val;
                Node<T>* temp = head;
                if (head == tail) tail = nullptr;
                head = head->next;
                delete temp;
                size--;
                return result;
            }
            else {
                throw runtime_error("Dequeue from empty queue.");
            }
        }
};


// Returns true if char is a number; false otherwise.
bool is_num(char c) {
    return c >= '0' && c <= '9';
}

/*
 * Returns the value of the next integer in the current line of the stream, and 0 if 
 * not found within the line or before a '|' character. 
 * Stream position is set to the end said integer, and last read character is stored in c.
*/
int get_num(ifstream &f, char &c) {
    int curr = f.get(), num = 0;
    while (!is_num(curr)) {
        if (curr == '\n' || curr == EOF || curr == '|') {
            c = curr;
            return 0;
        }
        curr = f.get();
    }
    do {
        num = num * 10 + curr - '0';
        curr = f.get();
    } while (is_num(curr));

    c = curr;
    return num;
}

// Part one of the day's solutions - assumes that every line is the same length.
int part_1(ifstream &f) {
    f.clear();
    f.seekg(0);
    int sum = 0, num, points;
    char c = 1;
    string s;
    unordered_set<int> winning_nums;
    
    while (c && c != EOF) {
        // Skip to the first colon of the line
        for (c = f.get(); c != ':'; c = f.get());
        num =  get_num(f, c);

        // Save all the numbers up to the '|' for future reference
        while (num && c != '|') {
            winning_nums.insert(num);
            num = get_num(f, c);
        } 

        // Find the amount of numbers past the '|' which match with the first numbers
        num = get_num(f, c);
        points = 1;
        while (num) {
            if (winning_nums.find(num) != winning_nums.end()) {
                points *= 2;
                // cout << num << ' ';
            }
            if (c == '\n' || c == EOF) break;
            num = get_num(f, c);
        } 
        // cout << '\n';
        
        winning_nums.clear();
        sum += points / 2;
    }
    return sum;
}

// Part two of the day's solutions - assumes that every line is the same length.
int part_2(ifstream &f) {
    f.clear();
    f.seekg(0);
    int sum = 0, num, points;
    char c = 1;
    string s;
    unordered_set<int> winning_nums;
    Queue<int> copies;
    
    // Find the number of matching numbers in the card
    while (c && c != EOF) {
        // Skip to the first colon of the line
        for (c = f.get(); c != ':'; c = f.get());

        // Save all the numbers up to the '|' for future reference
        num =  get_num(f, c);
        while (num && c != '|') {
            winning_nums.insert(num);
            num = get_num(f, c);
        } 

        // Find the amount of numbers past the '|' which match with the first numbers
        num = get_num(f, c);
        points = 0;
        while (num) {
            if (winning_nums.find(num) != winning_nums.end()) {
                points++;
            }
            if (c == '\n' || c == EOF) break;
            num = get_num(f, c);
        } 
        winning_nums.clear();

        // Number of copies of the current card won plus the initial card.
        int copy;
        if (copies.head) {
            copy = copies.dequeue() + 1;
        }
        else {
            copy = 1;
        }

        sum += copy;

        // Add won cards to the queue for future reference
        if (copies.size < points) {
            int size = copies.size;
            while (points > size) {
                copies.enqueue(copy);
                points--;
            }
        }
        Node<int>* curr = copies.head;
        while (points > 0) {
            curr->val += copy;
            curr = curr->next;
            points--;
        }
    }
    return sum;
}


int main() {
    ifstream f("advent_4.txt");    

    cout << "Part 1: " << part_1(f) << '\n';
    cout << "Part 2: " << part_2(f) << '\n';
    f.close();
}