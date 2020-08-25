#include <stdio.h>

#include "foo.h"

int main(int argc, char **argv) {
    int x = 1;
    int y = 2;
    int z;
    z = foo(x, y);
    printf("foo(%d, %d) = %d\n", x, y, z);
    return 0;
}
