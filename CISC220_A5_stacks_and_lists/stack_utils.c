#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "stack_utils.h"

stack *stack_split_at(stack *s, size_t index) {
    if (!s) {
        return false;
    }
    else if (index > s->size) {
        return NULL;
    }
    
    stack *new_stack = stack_init_empty();
    // Return empty stack if index is at the end of s, or return NULL if
    // memory for the new stack could not be allocated. 
    if (index == s->size || !new_stack) {
        return new_stack;
    }
    // Move the entire contents of s to the new stack if the index is 0.
    else if (index == 0) {
        new_stack->size = s->size;
        new_stack->top = s->top;
        s->size = 0;
        s->top = NULL;
        return new_stack;
    }

    // Traverse to the node right before the specified index
    node *curr = s->top;
    for (int i = 0; i < index - 1; i++) {
        curr = curr->next;
    }
    new_stack->top = curr->next;
    new_stack->size = s->size - index;
    s->size = index;
    curr->next = NULL;

    return new_stack;
}

bool double_less_than(const void *val1, const void *val2) {
    return *(double *)val1 <= *(double *)val2;
}

bool stack_is_sorted(const stack *s, stack_leq_func eq) {
    // Stack or the comparison function is NULL
    if (!s || !eq) {
        return false;
    }
    else if (stack_is_empty(s)) {
        return true;
    }
    else {
        // Traverse the stack and compare elements with eq.
        node *curr = s->top;
        while (curr->next) {
            if (!(*eq)(curr->elem, curr->next->elem)) {
                return false;
            }
            curr = curr->next;
        }
        return true;
    }
}
