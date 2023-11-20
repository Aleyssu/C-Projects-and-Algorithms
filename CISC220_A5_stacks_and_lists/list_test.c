#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "list_utils.h"


int main(void) {
    list *t = list_init_empty();
    list_add(t, 1);
    list_add(t, 2);
    list_add(t, 3);
    list_add(t, 4);
    list_add(t, 5);

    // list_print(t);
    // list *new_list = list_split_at(t, 2);
    // list_print(t);
    // list_print(new_list);
    // list_insert_all(t, 1, new_list);
    // list_print(t);
    // list_print(new_list);

    // list *a = list_init_empty();
    // for (int i = 6; i < 1000; i++) {
    //     list_add(a, i);
    // }

    list *a = list_init_empty();
    for (int i = 6; i < 9; i++) {
        list_add(a, i);
    }

    list_print(t);
    list_print(a);
    printf("t %d a %d\n", t->size, a->size);
    list_insert_all(t, 5, a);
    list_print(t);
    printf("t %d a %d\n", t->size, a->size);
    list *b = list_split_at(t, 6);
    list_print(t);
    list_print(b);
    printf("t %d b %d\n", t->size, b->size);
    list_free(t);

    return 0;
}