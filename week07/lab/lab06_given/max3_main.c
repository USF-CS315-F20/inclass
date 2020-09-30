#include <stdio.h>

int max3_c(int v0, int v1, int v2);
int max3_s(int v0, int v1, int v2);

int main(int argc, char **argv) {
    int r;

    r = max3_c(1, 2, 3);
    printf("max3_c(1, 2, 3) = %d\n", r);
    r = max3_s(1, 2, 3);
    printf("max3_s(1, 2, 3) = %d\n", r);

    r = max3_c(1, 99, 3);
    printf("max3_c(1, 99, 3) = %d\n", r);
    r = max3_s(1, 99, 3);
    printf("max3_s(1, 99, 3) = %d\n", r);
    
    r = max3_c(1, -2, -3);
    printf("max3_c(1, -2, -3) = %d\n", r);
    r = max3_s(1, -2, -3);
    printf("max3_s(1, -2, -3) = %d\n", r);


    return 0;
}
