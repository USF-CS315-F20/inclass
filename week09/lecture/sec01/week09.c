#include<stdint.h>
#include<stdio.h>
#include<string.h>

int add_s(int a0, int a1);
int max2_s(int a0, int a1);

void decode(char *name, uint32_t *code, int len);

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
uint32_t code2[32];

int main(int argc, char **argv)
{
    int r, r2;
    int (*fp) (int, int);

    decode("add_s", (uint32_t *) add_s, 3);
    printf("\n");

    r = add_s(1, 2);
    printf("add_s(1, 2) = %d\n", r);
    printf("\n");

    decode("max2_s", (uint32_t *) max2_s, 4);
    printf("\n");

    copy_code(code, (uint32_t *) add_s, 3);
    decode("add_s (copy)", code, 3);
    printf("\n");

    fp = (int (*)(int, int)) code;
    r = fp(1, 2);
    printf("code(1, 2) = %d\n", r);
    printf("\n");

    copy_code(code2, code, 3);
    mod_dp_imm(&code2[1], 99);

    decode("add_s (copy)", code2, 3);
    printf("\n");

    fp = (int (*)(int, int)) code2;
    r2 = fp(1, 2);
    printf("code2(1, 2) = %d\n", r2);
    printf("\n");

        
    return 0;
}
