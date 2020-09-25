#include <stdio.h>

int mul_c(int a0, int a2, int a3);
int mul_s(int a0, int a2, int a3);

int main(int argc, char **argv) {
    int r;

    r = mul_c(2, 4, 8);
    printf("mul_c(2, 4, 8) = %d\n", r);
    r = mul_s(2, 4, 8);
    printf("mul_s(2, 4, 8) = %d\n", r);

    return 0;
}
