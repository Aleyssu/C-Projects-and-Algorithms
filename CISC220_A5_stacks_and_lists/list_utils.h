#ifndef list_utils_h
#define list_utils_h

#include "list.h"

/**
 * Inserts all elements from src into dest at the specified index.
 * Elements at and beyond the index in the original list are shifted
 * up beginning at the end of the inserted elements.
 * 
 * Does nothing and returns false if: 
 * -dest or src is NULL
 * -src and dest point to the same list
 * -index is greater than the size of the dest list
 * 
 * Will also return false upon memory allocation failure for the
 * array expansion of list dest.
*/
bool list_insert_all(list *dest, size_t index, const list *src);

/**
 * Splits the list in two at the specified index. Elements at and beyond
 * the index are placed in the returned list, while the elements below
 * the index remain in the original list.
 * 
 * Returns false if t is null
 * 
 * Does nothing and returns NULL if index is greater than the size of list t
 * 
 * Returns NULL if memory for the new list can't be successfully allocated.
*/
list *list_split_at(list *t, size_t index);

#endif // list_utils_h
