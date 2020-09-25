#include <stdio.h>

int min_c(int a, int b);
int min_s(int a, int b);

int main(int argc, char **argv)
{
    int r;

    r = min_c(1, 2);
    printf("min_c(1, 2) = %d\n", r);
    r = min_s(1, 2);
    printf("min_s(1, 2) = %d\n", r);

    r = min_c(100, 99);
    printf("min_c(100, 99) = %d\n", r);
    r = min_s(100, 99);
    printf("min_s(100, 99) = %d\n", r);    

    return 0;
}
