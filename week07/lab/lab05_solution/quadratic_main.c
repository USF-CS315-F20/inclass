#include <stdio.h>

int quadratic_c(int x, int a, int b, int c);
int quadratic_s(int x, int a, int b, int c);

int main(int argc, char **argv) {
    int r;

    r = quadratic_c(1, 1, 1, 1);
    printf("quadtratic_c(1, 1, 1, 1) = %d\n", r);
    r = quadratic_s(1, 1, 1, 1);
    printf("quadtratic_s(1, 1, 1, 1) = %d\n", r);    

    r = quadratic_c(2, 2, 3, 4);
    printf("quadtratic_c(2, 2, 3, 4) = %d\n", r);
    r = quadratic_s(2, 2, 3, 4);
    printf("quadtratic_s(2, 2, 3, 4) = %d\n", r);    

    return 0;
}
