#include <stdio.h>
#include <string.h>

struct node_st {
    int x;
    int y;
    char value[32];
};

void print_node(struct node_st *np) {
    printf("x = %d\n", np->x);
    printf("y = %d\n", np->y);
    printf("value = %s\n", np->value);
}

int main(int argc, char **argv) {
    struct node_st node;

    node.x = 99;
    node.y = 5555;
    strncpy(node.value, "CS315 is fun", 32);

    print_node(&node);

    return 0;
}
