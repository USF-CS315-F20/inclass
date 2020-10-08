#include<stdio.h>
#include<string.h>

int sum_array_rec_c(int *array, int index, int len);
int sum_array_rec_s(int *array, int index, int len);

char *strcat_c(char *dst, char *src);
char *strcat_s(char *dst, char *src);

int match_s(char *s1, char *s2, int len2);

int substr_c(char *s1, char *s2);
int substr_s(char *s1, char *s2);

int main(int argc, char **argv)
{
    int r;

    int a1[] = {1, 2, 5, 4, 3};
    r = sum_array_rec_c(a1, 0, 5);
    printf("sum_array_rec_c({1, 2, 5, 4, 3}, 0, 5) = %d\n", r);
    r = sum_array_rec_s(a1, 0, 5);
    printf("sum_array_rec_s({1, 2, 5, 4, 3}, 0, 5) = %d\n", r);    


    int a2[] = {-300, -200, -2, -1, 0, 100, 1, 2, 5, 4};    
    r = sum_array_rec_c(a2, 0, 10);
    printf("sum_array_rec_c({-300, -200, -2, -1, 0, 100, 1, 2, 5, 4}, 0, 10) = %d\n", r);
    r = sum_array_rec_s(a2, 0, 10);
    printf("sum_array_rec_s({-300, -200, -2, -1, 0, 100, 1, 2, 5, 4}, 0, 10) = %d\n", r);    

    char s[128];
    strcpy(s, "foo");
    strcat_c(s, "bar");
    printf("strcat_c(\"foo\", \"bar\") = %s\n", s);

    strcpy(s, "foo");
    strcat_s(s, "bar");
    printf("strcat_s(\"foo\", \"bar\") = %s\n", s);

    r = match_s("foo", "bar", 3);
    printf("match_s(\"foo\", \"bar\") = %d\n", r);

    r = match_s("foo", "foo", 3);
    printf("match_s(\"foo\", \"foo\") = %d\n", r);

    r = substr_c("foobar", "bar");
    printf("substr_c(\"foobar\", \"bar\") = %d\n", r);

    r = substr_s("foobar", "bar");
    printf("substr_s(\"foobar\", \"bar\") = %d\n", r);

    return 0;
}
