#include<stdint.h>
#include<stdio.h>
#include<string.h>

int add_s(int a0, int a1);

void decode(char *name, uint32_t *code, int len);

void copy_code(uint32_t *dst, uint32_t *src, int len) {
    int i;

    for (i = 0; i < len; i++) {
        dst[i] = src[i];
    }
}

void mod_dp_imm(uint32_t *ip, int imm) {
    uint32_t iw;

    iw = *ip;

    iw = iw & 0xFFFFFF00;
    iw = iw | (imm & 0x000000FF);

    *ip = iw;    
}


uint32_t code[16];

int main(int argc, char **argv)
{
    decode("add_s", (uint32_t *) add_s, 3);
    printf("\n");

    copy_code(code, (uint32_t *) add_s, 3);
    decode("add_s (copy)", code, 3);
    printf("\n");

    mod_dp_imm(&code[1], 99);
    decode("add_s (copy)", code, 3);
    printf("\n");
    
    return 0;
}
