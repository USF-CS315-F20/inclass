#include <stdio.h>

int in_range_c(int start, int end, int x);
int in_range_s(int start, int end, int x);

int count_zeros_c(int array[], int len);
int count_zeros_s(int array[], int len);

int sum_array_c(int array[], int len);
int sum_array_s(int array[], int len);

int add4_s(int v0, int v1, int v2, int v3);

int main(int argc, char **argv) {
    int r;

    r = in_range_c(0, 9, 3);
    printf("in_range_c(0, 9, 3) = %d\n", r);
    r = in_range_s(0, 9, 3);
    printf("in_range_s(0, 9, 3) = %d\n", r);

    r = in_range_c(0, 9, 29);
    printf("in_range_c(0, 9, 29) = %d\n", r);
    r = in_range_s(0, 9, 29);
    printf("in_range_s(0, 9, 29) = %d\n", r);

    int a1[] = {1, 0, 1, 0, 1};
    r = count_zeros_c(a1, 5);
    printf("count_zeros_c({1, 0, 1, 0, 1}, 5) = %d\n", r);

    r = count_zeros_s(a1, 5);
    printf("count_zeros_s({1, 0, 1, 0, 1}, 5) = %d\n", r);

    r = sum_array_c(a1, 5);
    printf("sum_array_c({1, 0, 1, 0, 1}, 5) = %d\n", r);

    r = sum_array_s(a1, 5);
    printf("sum_array_s({1, 0, 1, 0, 1}, 5) = %d\n", r);

    r = add4_s(1, 2, 3, 4);
    printf("add4_s(1, 2, 3, 4) = %d\n", r);

    return 0;
}
