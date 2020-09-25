#include <stdio.h>

int max_c(int a0, int a1);
int max_s(int a0, int a2);

int main(int argc, char **argv) {
    int r;

    r = max_c(1, 2);
    printf("max_c(1, 2) = %d\n", r);
    r = max_s(1, 2);
    printf("max_s(1, 2) = %d\n", r);

    r = max_c(150, 100);
    printf("max_c(150, 100) = %d\n", r);
    r = max_s(150, 100);
    printf("max_s(150, 100) = %d\n", r);


    return 0;
}
