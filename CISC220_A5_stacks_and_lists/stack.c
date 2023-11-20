#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"



stack *stack_init_empty() {
    // allocate the stack struct
    stack *s = malloc(sizeof(stack));
    if (!s) {
        return NULL;
    }
    // initialize members for an empty list
    s->top = NULL;
    s->size = 0;
    return s;
}

bool stack_is_empty(const stack *s) {
    return s->size == 0;
}

size_t stack_size(const stack *s) {
    return s->size;
}

bool stack_push(stack *s, void *elem) {
    // allocate storage for a new node
    node *n = malloc(sizeof(node));
    if (!n) {
        return false;
    }
    // initialize node members so that the node is in
    // front of the current top node
    n->elem = elem;
    n->next = s->top;
    // the top node in the stack is now n
    s->top = n;
    s->size++;
    return true;
}

void *stack_pop(stack *s) {
    assert(!stack_is_empty(s));
    // get a pointer to the top node so that we can free the node later
    node *top = s->top;
    // get the element to return to the caller
    void *elem = top->elem;
    // pop the element by moving the top pointer to the next node
    s->top = top->next;
    s->size--;
    // free the old top node
    free(top);

    return elem;
}

void stack_free(stack *s, free_elem_func free_elem) {
    // free all nodes by iterating over all nodes and freeing
    // nodes as they are visited
    node *n = s->top;
    while (n) {
        node *next = n->next;
        if (free_elem) {
            (*free_elem)(n->elem);
        }
        free(n);
        n = next;
    }
    // free the stack
    free(s);
}



void stack_print(const stack *s, print_elem_func print_elem) {
    printf("TOP");
    if (s->size > 0) {
        printf(" ");
        print_elem(s->top->elem);
        node *n = s->top->next;
        while (n) {
            printf(", ");
            print_elem(n->elem);
            n = n->next;
        }
    }
    printf(" BOTTOM\n");
}

