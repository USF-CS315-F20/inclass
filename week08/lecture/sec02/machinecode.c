#include <stdint.h>
#include <stdio.h>

int add_s(int a0, int a1);

void decode(void) {
    uint32_t *ip;
    uint32_t iw;
    int r;

    r = add_s(1, 2);
    printf("add_s(1, 2) = %d\n", r);

    ip = (uint32_t *) add_s;
    iw = *ip;
    printf("add_s + 0 = %8X\n", iw);

    ip = ip + 1;
    iw = *ip;
    printf("add_s + 4 = %8X\n", iw);

    ip = ip + 1;
    iw = *ip;
    printf("add_s + 8 = %8X\n", iw);

}
