/* conv.c base conversion functions */

#include "ntcalc.h"

uint32_t conv_binstr_to_uint32(char *binstr) {
    uint32_t result = 0;
    int i = 0;

    while (binstr[i] != '\0') {
        result *= 2;
        result += binstr[i] - '0';
        i += 1;
        if (i >= 32) {
            printf("BINLIT too big\n");
            exit(-1);
        }
    }

    return result;
}


void conv_uint32_to_binstr(uint32_t v, char *binstr) {
    int i, j, bit;

    binstr[0] = '0';
    binstr[1] = 'b';
    j = 2;

    for (i = 31; i >= 0; i--, j++) {
        bit = (v >> i) & 0b1;
        binstr[j] = '0' + bit;
    }

    binstr[j] = '\0';
}
