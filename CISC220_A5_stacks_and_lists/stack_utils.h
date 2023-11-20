#ifndef stack_utils_h
#define stack_utils_h

#include "stack.h"

/**
 * Splits the given stack in two at the specified index. 
 * Elements at and beyond the index are returned in a new stack, while
 * elements below the index remain in the original stack.
 * 
 * Returns false if s is NULL
 * 
 * Does nothing and returns NULL if the index is greater than the size 
 * of the stack.
 * 
 * Returns NULL if memory for the new stack can't be allocated.
*/
stack *stack_split_at(stack *s, size_t index);

/**
 * Function which is used to compare elements to determine sorted order.
*/
typedef bool (*stack_leq_func)(const void *, const void *);

/**
 * Returns true if the double in val1 <= val2
*/
bool double_less_than(const void *val1, const void *val2);

/**
 * Traverses the stack s and returns true if they're all in sorted order
 * determined by the function eq, else returns false.
*/
bool stack_is_sorted(const stack *s, stack_leq_func eq);

#endif // stack_utils_h
