#include <stdio.h>

int in_range_c(int start, int end, int x);
int in_range_s(int start, int end, int x);

int count_zeros_c(int array[], int len);
int count_zeros_s(int array[], int len);
int count_zeros_index_c(int array[], int len);
int count_zeros_index_s(int array[], int len);

int sum_array_c(int array[], int len);
int sum_array_s(int array[], int len);

int add4_s(int v0, int v1, int v2, int v3);

int strlen_c(char *s);
int strlen_s(char *s);

int fact_c(int n);
int fact_s(int n);

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

    r = count_zeros_index_c(a1, 5);
    printf("count_zeros_index_c({1, 0, 1, 0, 1}, 5) = %d\n", r);
    r = count_zeros_index_s(a1, 5);
    printf("count_zeros_index_s({1, 0, 1, 0, 1}, 5) = %d\n", r);


    r = sum_array_c(a1, 5);
    printf("sum_array_c({1, 0, 1, 0, 1}, 5) = %d\n", r);
    r = sum_array_s(a1, 5);
    printf("sum_array_s({1, 0, 1, 0, 1}, 5) = %d\n", r);

    r = add4_s(1, 2, 3, 4);
    printf("add4_s(1, 2, 3, 4) = %d\n", r);

    char *s = "Hello, World";
    
    r = strlen_c(s);
    printf("strlen_c(\"Hello, World\") = %d\n", r);
    r = strlen_s(s);
    printf("strlen_s(\"Hello, World\") = %d\n", r);

    r = fact_c(4);
    printf("fact_c(4) = %d\n", r);
    r = fact_s(4);
    printf("fact_s(4) = %d\n", r);


    return 0;
}
