#ifndef stack_H
#define stack_H

#include <stdbool.h>
#include <stddef.h>

/**
 * Name of the node struct used by stack.
 */
typedef struct node node;

/**
 * The node struct definition.
 */
struct node {
    void *elem;
    node *next;
};

/**
 * Name of the stack struct.
 */
typedef struct stack stack;

/**
 * The stack struct definition.
 */
struct stack {
    node *top;
    size_t size;
};

/**
 * Pointer to function that prints an element.
 */
typedef void (*print_elem_func)(const void *elem);

/* 
 * Pointer to function that frees an element.
 */
typedef void (*free_elem_func)(void *elem);

/**
 * Returns a pointer to an empty stack, or null if the stack could
 * not be allocated.
 * 
 * The returned stack must be freed using stack_free.
 */
stack *stack_init_empty();


/**
 * Returns true if the stack pointed at by s is empty, false
 * otherwise.
 * 
 * Behavior is undefined if s is NULL.
 */
bool stack_is_empty(const stack *s);


/**
 * Returns the number of elements in the stack pointed at by s.
 * 
 * Behavior is undefined if s is NULL.
 */
size_t stack_size(const stack *s);


/**
 * Pushes the pointer elem onto the top of the stack pointed at
 * by s. Returns false if memory allocation fails, otherwise
 * returns true.
 * 
 * Behavior is undefined if s is NULL.
 */
bool stack_push(stack *s, void *elem);


/**
 * Pops the top element of the stack pointed at
 * by s returning a pointer to the element.
 * 
 * Behavior is undefined if s is NULL.
 */
void *stack_pop(stack *s);


/**
 * Free the memory associated with a stack. If
 * free_elem is not NULL, then the memory for each element
 * is also freed by calling the provided function;
 * otherwise, the elements are not freed.
 */
void stack_free(stack *s, free_elem_func free_elem);


/**
 * Prints the elements of the stack where each element is
 * printed using the provided function. Undefined behavior
 * results if print_elem is NULL.
 */
void stack_print(const stack *s, print_elem_func print_elem);

#endif // stack_H