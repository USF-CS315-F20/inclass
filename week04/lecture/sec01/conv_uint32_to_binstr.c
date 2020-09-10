#include <stdio.h>
#include <stdint.h>

void conv_uint32_to_binstr(uint32_t v, char *s) {
    int i, j, bit;

    s[0] = '0';
    s[1] = 'b';
    j = 2;

    for (i = 31; i >= 0; i--) {
        bit = (v >> i) & 0b1;
        s[j] = '0' + bit;
        j += 1;        
    }

    s[j] = '\0';
}

int main(int argc, char **argv) {
    uint32_t x = 0b110110101;
    char result[64];

    conv_uint32_to_binstr(x, result);
    printf("%u = %s\n", x, result);

    return 0;
}
