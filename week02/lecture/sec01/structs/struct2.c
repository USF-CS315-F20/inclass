#include <stdio.h>
#include <string.h>

struct node_st {
    union {
        struct {
            char value[64];
        } url;
        struct {
            int byte0;
            int byte1;
            int byte2;
            int byte3;
        } ipaddr;
    };
};

/*
void print_node(struct node_st *np) {
    printf("x = %d\n", np->x);
    printf("y = %d\n", np->y);
    printf("value = %s\n", np->value);
}
*/

int main(int argc, char **argv) {
    struct node_st node;

    strncpy(node.url.value, "CS315 is fun", 32);

    node.ipaddr.byte0 = 1;
    node.ipaddr.byte1 = 2;
    node.ipaddr.byte2 = 168;
    node.ipaddr.byte3 = 192;

    //    print_node(&node);

    return 0;
}
