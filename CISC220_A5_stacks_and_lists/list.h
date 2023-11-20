#ifndef LIST_H
#define LIST_H

#include <stdbool.h>
#include <stddef.h>

/**
 * Name of the provided list type.
 */
typedef struct list list;

/**
 * The list struct made visible so that other users can
 * extend the functionality of the list.
 */
struct list {
    /**
     * The array holding the elements of the list.
     */
    int *arr;

    /**
     * The capacity of arr.
     */
    size_t capacity;

    /**
     * The number of elements in the list.
     */
    size_t size;
};


/**
 * Attempts to double the capacity of the array backing
 * the list t. Returns true if the array capacity is increased,
 * false otherwise.
 */

bool add_capacity(list *t);


/**
 * Returns a pointer to an empty list having a default
 * capacity, or null if the list could not be allocated.
 * 
 * The returned list must be freed using list_free.
 */
list *list_init_empty(void);

/**
 * Returns a pointer to an empty list having the specified
 * capacity, or null if the list could not be allocated.
 * 
 * The returned list must be freed using list_free.
 */
list *list_init(size_t capacity);


/**
 * Returns the number of elements in the specified list.
 */
size_t list_size(const list *t);

/**
 * Returns the element at the specified index of the
 * specified list. Using an invalid index produces
 * undefined behavior.
 */
int list_get(const list *t, size_t index);

/**
 * Sets the specified index of the specified list to the
 * specified element, overwriting the existing element.
 * Using an invalid index produces undefined behavior.
 * The value that was overwritten is returned to the caller.
 */
int list_set(list *t, size_t index, int elem);

/**
 * Adds an element to the end of the specified list,
 * expanding the capacity of the list if needed. Returns
 * true if the element is added to the list, and false
 * if the element could not be added to the list.
 */ 
bool list_add(list *t, int elem);

/**
 * Inserts the specified element into the specified list at
 * the specified index. All existing elements, if any, starting
 * at the specified index and beyond are shifted one position
 * to the right. Using an invalid index produces undefined behavior
 * (but note that using an index equal to the size of the list
 * adds the element to the end of the list).
 * 
 * Returns true if the element is inserted into the list, and false
 * if the element could not be inserted into the list.
 */
bool list_insert(list *t, size_t index, int elem);

/**
 * Removes and returns the element at the specified
 * index of the specified list.
 */
int list_remove(list *t, size_t index);

/**
 * Returns a null-terminated string representation of the specified list.
 * The caller must free the returned string.
 */
char *list_to_string(const list *t);


/**
 * Prints a list followed by a newline to standard output.
 */
void list_print(const list *t);

/**
 * Deallocates memory used by the specified list. Attempts
 * to use the specified list after this function returns
 * produces undefined behavior.
 */
void list_free(list *t);

#endif /* LIST_H */