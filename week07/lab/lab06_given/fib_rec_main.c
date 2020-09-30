#include<stdio.h>

int fib_rec_c(int n);
int fib_rec_s(int n);

int main(int argc, char **argv)
{
    int r;

    r = fib_rec_c(0);
    printf("fib_rec_c(0) = %d\n", r);
    r = fib_rec_s(0);
    printf("fib_rec_c(0) = %d\n", r);

    r = fib_rec_c(1);
    printf("fib_rec_c(1) = %d\n", r);
    r = fib_rec_s(1);
    printf("fib_rec_s(1) = %d\n", r);

    r = fib_rec_c(2);
    printf("fib_rec_c(2) = %d\n", r);
    r = fib_rec_s(2);
    printf("fib_rec_s(2) = %d\n", r);

    r = fib_rec_c(3);
    printf("fib_rec_c(3) = %d\n", r);
    r = fib_rec_s(3);
    printf("fib_rec_s(3) = %d\n", r);

    r = fib_rec_c(10);
    printf("fib_rec_c(10) = %d\n", r);
    r = fib_rec_s(10);
    printf("fib_rec_s(10) = %d\n", r);

    r = fib_rec_c(20);
    printf("fib_rec_c(20) = %d\n", r);
    r = fib_rec_s(20);
    printf("fib_rec_s(20) = %d\n", r);    
    
    return 0;
}
