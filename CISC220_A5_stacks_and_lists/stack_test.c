#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "stack_utils.h"


void print_double(const void *elem) {
    int val = *((double *) elem);
    printf("%.1f", val);
}

int main(void) {
    stack *s = stack_init_empty();

    // double *arr = malloc(5 * sizeof(double));
    // arr[0] = 1.0f;
    // arr[1] = 2.0f;
    // arr[2] = 3.0f;
    // arr[3] = 5.0f;
    // arr[4] = 4.0f;
    // stack_push(s, arr);
    // stack_push(s, arr + 1);
    // stack_push(s, arr + 2);
    // stack_push(s, arr + 3);
    // stack_push(s, arr + 4);
    // stack_print(s, print_double);
    // printf("s is sorted: %s\n", stack_is_sorted(s, double_less_than)?"true":"false");
    // stack *new_stack = stack_split_at(s, 2);
    // stack_print(s, print_double);
    // stack_print(new_stack, print_double);
    // printf("s is sorted: %s\n", stack_is_sorted(s, double_less_than)?"true":"false");
    // printf("new stack is sorted: %s\n", stack_is_sorted(new_stack, double_less_than)?"true":"false");
    // free(arr);
    // stack_free(s, NULL);

    stack *s1 = stack_init_empty();

    double *arr1 = malloc(100 * sizeof(double));
    double *arr2 = malloc(10 * sizeof(double));
    double num = 10;
    for (int i = 0; i < 10; i++) {
        arr2[i] = num;
        stack_push(s1, arr2 + i);
        num -= 1;
    }
    num = 5.9;
    for (int i = 0; i < 100; i++) {
        arr1[i] = num;
        stack_push(s, arr1 + i);
        num -= 0.1;
    }

    stack_print(s, print_double);
    stack_split_at(s, 50);
    printf("s: %d\n", stack_is_sorted(s, double_less_than));
    stack_print(s, print_double);

    return 0;
}