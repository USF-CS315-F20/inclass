#include<stdio.h>
#include<string.h>

void decode(void);

int main(int argc, char **argv)
{
    int a[2] = {0xFF22AA11, 0xBB33CC00};

    printf("a[0] = %8X\n", a[0]);
    printf("a[1] = %8X\n", a[1]);

    decode();

    return 0;
}
