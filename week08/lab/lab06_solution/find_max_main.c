#include<stdio.h>

int find_max_c(int *array, int len);
int find_max_s(int *array, int len);

int main(int argc, char **argv)
{
    int r;

    int a1[] = {1, 2, 5, 4, 3};

    r = find_max_c(a1, 5);
    printf("find_max_c({1, 2, 5, 4, 3}, 5) = %d\n", r);

    r = find_max_s(a1, 5);
    printf("find_max_s({1, 2, 5, 4, 3}, 5) = %d\n", r);    


    int a2[] = {-300, -200, -2, -1, 0, 100, 1, 2, 5, 4};    

    r = find_max_c(a2, 10);
    printf("find_max_c({-300, -200, -2, -1, 0, 100, 1, 2, 5, 4}, 10) = %d\n", r);

    r = find_max_s(a2, 10);
    printf("find_max_s({-300, -200, -2, -1, 0, 100, 1, 2, 5, 4}, 10) = %d\n", r);    

    return 0;
}
