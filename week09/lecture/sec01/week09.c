#include<stdint.h>
#include<stdio.h>
#include<string.h>

int add_s(int a0, int a1);

void decode(char *name, uint32_t *code, int len) {
    int i;
    uint32_t iw;

    for (i = 0; i < len; i++) {
        iw = code[i];
        printf("%s + %d : %8X\n", name, (i * 4), iw);
    }
}

void copy_code(uint32_t *dst, uint32_t *src, int len) {
    int i;

    for (i = 0; i < len; i++) {
        dst[i] = src[i];
    }
}

void mod_dp_imm(uint32_t *ip, int imm) {
    uint32_t iw = *ip;

    iw = iw & 0xFFFFFF00;
    iw = iw | (imm & 0xFF);

    *ip = iw;
}

uint32_t code[32];

int main(int argc, char **argv)
{
    int r;
    int (*fp) (int, int);

    decode("add_s", (uint32_t *) add_s, 3);
    printf("\n");

    r = add_s(1, 2);
    printf("add_s(1, 2) = %d\n", r);
    printf("\n");

    copy_code(code, (uint32_t *) add_s, 3);
    mod_dp_imm(&code[1], 99);
    decode("add_s (copy)", code, 3);
    printf("\n");

    fp = (int (*)(int, int)) code;
     __clear_cache((char *) code, ((char *) code) + 16);
    r = fp(1, 2);

    printf("code(1, 2) = %d\n", r);
    printf("\n");

    return 0;
}
