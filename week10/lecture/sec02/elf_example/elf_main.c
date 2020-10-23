/* elf_main.c - elf generation example */

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "elf/elf.h"

/*
objdump -D count_s.o

Disassembly of section .text:

00000000 <count_s>:
   0:	e1a01000 	mov	r1, r0
   4:	e3a00000 	mov	r0, #0
   8:	e3a02000 	mov	r2, #0

0000000c <count_loop>:
   c:	e1520001 	cmp	r2, r1
  10:	ca000002 	bgt	20 <count_done>
  14:	e0800002 	add	r0, r0, r2
  18:	e2822001 	add	r2, r2, #1
  1c:	eafffffa 	b	c <count_loop>

00000020 <count_done>:
  20:	e12fff1e 	bx	lr
*/

#define SCAN_TOKEN_LEN 64
#define CODEGEN_TABLE_LEN 256

struct codegen_label_pair {
    char label[SCAN_TOKEN_LEN];
    int offset;
};

struct codegen_table_st {
    uint32_t table[CODEGEN_TABLE_LEN];
    int len;
    int next;
    struct parse_node_st *tree;
    struct codegen_label_pair labels[CODEGEN_TABLE_LEN];
    int label_count;
    struct codegen_label_pair publics[CODEGEN_TABLE_LEN];
    int public_count;
};

void codegen_table_add_pair(struct codegen_label_pair *lp, int index, 
                       char *label, int offset) {

    strncpy(lp[index].label, label, SCAN_TOKEN_LEN);
    lp[index].offset = offset;
}

bool codegen_is_public_label(struct codegen_table_st *ct, struct codegen_label_pair *pl) {
    for (int l = 0; l < ct->public_count; l++) {
        if (!strncmp(ct->publics[l].label, pl->label, SCAN_TOKEN_LEN))
            return true;
    }
    return false;
}

void codegen_elf_write(struct codegen_table_st *ct, char *path) {
    int i;
    elf_context elf;
    struct codegen_label_pair *pl;
    int binding;

    elf_init(&elf);
    for (i = 0; i < ct->label_count; i++) {
        pl = &ct->labels[i];
        if (codegen_is_public_label(ct, pl)) {
            binding = STB_GLOBAL;
        } else {
            binding = STB_LOCAL;
        }
        elf_add_symbol(&elf, pl->label, pl->offset, binding);
    }
    for (i = 0; i < ct->len; i++) {
        elf_add_instr(&elf, ct->table[i]);
    }

    FILE *f = fopen(path, "w");
    if (!f) {
        perror(path);
        return;
    }
    if (!elf_write_file(&elf, f)) {
        printf("elf_write_file failed\n");
    }
    fclose(f);
}

int main(int argc, char **argv) {
    struct codegen_table_st codegen_table;

    codegen_table.table[0] = 0xe1a01000;
    codegen_table.table[1] = 0xe3a00000;
    codegen_table.table[2] = 0xe3a02000;
    codegen_table.table[3] = 0xe1520001;
    codegen_table.table[4] = 0xca000002;
    codegen_table.table[5] = 0xe0800002;
    codegen_table.table[6] = 0xe2822001;
    codegen_table.table[7] = 0xeafffffa;
    codegen_table.table[8] = 0xe12fff1e;
    codegen_table.len = 9;

    codegen_table_add_pair(codegen_table.labels, 0, "count_s", 0x00);
    codegen_table_add_pair(codegen_table.labels, 1, "count_loop", 0x0C);
    codegen_table_add_pair(codegen_table.labels, 2, "count_done", 0x20);
    codegen_table.label_count = 3;    

    codegen_table_add_pair(codegen_table.publics, 0, "count_s", 0x00);
    codegen_table.public_count = 1;

    codegen_elf_write(&codegen_table, "count_s_ours.o");
}
