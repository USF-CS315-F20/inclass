/* codegen.c - machine code generation */

#include "armasm.h"

struct codegen_map_st codegen_opcode_map[] = CODEGEN_OPCODE_MAP;
struct codegen_map_st codegen_bcc_map[] = CODEGEN_BCC_MAP;

#define COND_BIT 28

void codegen_error(char *err) {
    printf("codegen_error: %s\n", err);
    exit(-1);
}

void codegen_table_init(struct codegen_table_st *ct, struct parse_node_st *tree) {
    ct->len = 0;
    ct->next = 0;
    ct->tree = tree;
}

void codegen_add_inst(struct codegen_table_st *ct, uint32_t inst) {
    ct->table[ct->len] = inst;
    ct->len += 1;
}

uint32_t codegen_lookup(char *name, struct codegen_map_st *map, int map_len) {
    int i;
    for (i = 0; i < map_len; i++) {
        if (strncmp(name, map[i].name, SCAN_TOKEN_LEN) == 0) {
            return map[i].bits;
        }
    }

    codegen_error(name);
    return (uint32_t) -1;
}

uint32_t codegen_lookup_opcode(char *name) {
    int len = sizeof(codegen_opcode_map) / sizeof(codegen_opcode_map[0]);
    return codegen_lookup(name, codegen_opcode_map, len);
}

void codegen_dp_common(struct codegen_table_st *ct, uint32_t imm, uint32_t op, 
    uint32_t rn, uint32_t rd, uint32_t op2) {

    const uint32_t DP_IMM_BIT = 25;
    const uint32_t DP_OP_BIT  = 21;
    const uint32_t DP_RN_BIT  = 16;
    const uint32_t DP_RD_BIT  = 12;
    uint32_t inst = 0;

    inst = (COND_AL << COND_BIT)
        | (imm << DP_IMM_BIT)
        | (op  << DP_OP_BIT)
        | (rn  << DP_RN_BIT)
        | (rd  << DP_RD_BIT)
        | op2;
    codegen_add_inst(ct, inst);
}

void codegen_dp3(struct codegen_table_st *ct, struct parse_node_st *np) {
    codegen_dp_common(
        ct,
        0, /*imm*/
        codegen_lookup_opcode(np->stmt.inst.name),
        np->stmt.inst.dp3.rn,
        np->stmt.inst.dp3.rd,
        np->stmt.inst.dp3.rm);
}

void codegen_bx(struct codegen_table_st *ct, struct parse_node_st *np) {
    const uint32_t BX_CODE_BIT = 4;
    const uint32_t bx_code = 0b000100101111111111110001;

    uint32_t inst = (COND_AL << COND_BIT)
        | (bx_code << BX_CODE_BIT)
        | np->stmt.inst.bx.rn;
    codegen_add_inst(ct, inst);
}

void codegen_inst(struct codegen_table_st *ct, struct parse_node_st *np) {

    switch (np->stmt.inst.type) {
        case DP3 : codegen_dp3(ct, np); break;
        case BX  : codegen_bx(ct, np); break;
        default  : codegen_error("unknown stmt.inst.type");
    }
}

void codegen_stmt(struct codegen_table_st *ct, struct parse_node_st *np) {

    if (np->type == INST) {
        codegen_inst(ct, np);
    } else if (np->type == SEQ) {
        codegen_stmt(ct, np->stmt.seq.left);
        codegen_stmt(ct, np->stmt.seq.right);
    }
}

void codegen_print_hex(struct codegen_table_st *ct) {
    int i;

    printf("v2.0 raw\n");
    for (i = 0; i < ct->len; i++) {
        printf("%8X\n", ct->table[i]);
    }
}

void codegen_write(struct codegen_table_st *ct, char *path) {
    int i;
    FILE *obj = fopen(path, "w");

    fprintf(obj, "v2.0 raw\n");
    for (i = 0; i < ct->len; i++) {
        fprintf(obj, "%8X\n", ct->table[i]);
    }
    fclose(obj);
}

void codegen_hex_write(struct codegen_table_st *ct, struct parse_node_st *np, char *path) {
    codegen_write(ct, path);
}
