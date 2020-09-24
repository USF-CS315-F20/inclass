#include <stdio.h>

int add4_c(int a0, int a1, int a2, int a3);
int add4_s(int a0, int a1, int a2, int a3);

int main(int argc, char **argv) {
    int r;

    r = add4_c(1, 2, 3, 4);
    printf("add4_c(1, 2, 3, 4) = %d\n", r);
    r = add4_s(1, 2, 3, 4);
    printf("add4_s(1, 2, 3, 4) = %d\n", r);

    r = add4_c(-1, -2, 0, -3);
    printf("add4_c(-1, -2, 0, -3) = %d\n", r);    
    r = add4_s(-1, -2, 0, -3);
    printf("add4_s(-1, -2, 0, -3) = %d\n", r);    
    
    return 0;
}
