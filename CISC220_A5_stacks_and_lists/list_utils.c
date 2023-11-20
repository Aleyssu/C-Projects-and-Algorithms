#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "list_utils.h"

bool list_insert_all(list *dest, size_t index, const list *src) {
    if (dest == src || index > dest->size || src == NULL || dest == NULL) {
        return false;
    }
    size_t int_size = sizeof(int);
    // Destination array is not large enough to also contain src
    if (dest->size + src->size > dest->capacity) {
        int *new_arr = malloc(int_size * (dest->size + src->size)  * 2);
        if (new_arr) {
            memcpy(new_arr, dest->arr, index * int_size);
            memcpy(new_arr + index, src->arr, src->size * int_size);
            memcpy(new_arr + (index + src->size), dest->arr + index, (dest->size - index) * int_size); 
            free(dest->arr);
            dest->arr = new_arr;
            dest->capacity = (dest->size + src->size) * 2;
        }
        else {
            return false;
        }
    }
    // Destination array is large enough to also contain src
    else {
        memmove(dest->arr + src->size + index, dest->arr + index, (dest->size - index) * int_size);
        memcpy(dest->arr + index, src->arr, src->size * int_size);
    }
    dest->size += src->size;
    return true;
}

list *list_split_at(list *t, size_t index) {
    if (t == NULL) {
        return false;
    }
    else if (index > t->size) {
        return NULL;
    }
    else {
        size_t int_size = sizeof(int);
        list *new_list = list_init((t->size - index) * 2);
        if (new_list) {
            new_list->size = t->size - index;
            memcpy(new_list->arr, t->arr + index, new_list->size * int_size);
            t->size = index;
            return new_list;
        }
        else {
            return NULL;
        }
    }
}