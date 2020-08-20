#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define ELEMENT_LEN 32
#define TABLE_LEN 64

struct element_st {
    char value[ELEMENT_LEN];
};

struct list_st {
    struct element_st table[TABLE_LEN];
    int count;
};

void list_init(struct list_st *list) {
    list->count = 0;
}

void list_add(struct list_st *list, char *element) {
    strncpy(list->table[list->count].value, element, ELEMENT_LEN);
    list->count += 1;
}

void list_print(struct list_st *list) {
    for (int i = 0; i < list->count; i++) {
        printf("list[%d] = %s\n", i, list->table[i].value);
    }
}

bool list_is_member(struct list_st *list, char *element) {
    int i = 0;
    bool rv = false;

    for (i = 0; i < list->count; i++) {
        if (strncmp(list->table[i].value, element, ELEMENT_LEN) == 0) {
            rv = true;
            break;
        }
    }

    return rv;
}

int main(int argc, char **argv) {
    int rv;
    struct list_st list;

    list_init(&list);
    list_add(&list, "foo");
    list_add(&list, "bar");
    list_add(&list, "baz");

    list_print(&list);
    
    rv = list_is_member(&list, "baz");
    printf("is_member(&list, \"baz\") = %d\n", rv);

    rv = list_is_member(&list, "goo");
    printf("is_member(&list, \"goo\") = %d\n", rv);

    rv = list_is_member(&list, "moo");
    printf("is_member(&list, \"moo\") = %d\n", rv);
    
    return 0;
}
