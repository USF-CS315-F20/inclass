#include <stdint.h>
#include <stdio.h>

void decode(char *name, uint32_t *code, int len) {
    int i;
    uint32_t iw;

    for(i = 0; i < len; i++) {
        iw = code[i];
        printf("%s + %d : %8X\n", name, (i * 4), iw);
    }
}
