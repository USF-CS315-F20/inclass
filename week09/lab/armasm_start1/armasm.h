/* armasm.h */

#ifndef _ARMASM_H
#define _ARMASM_H

#include <fcntl.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

/*
 * scan.c
 */

/*

# Scanner EBNF for ARM Assembly

tokenlist   ::= (token)*
token       ::= ident | imm | symbol
ident       ::= letter (letter | digit | '_')*
imm         ::= '#' ('-')+ digit (digit)*
symbol      ::= '.' | '[' | ']' | ',' | ':' 
letter      ::= 'a' | ... | 'z' | 'A' | ... | 'Z'
digit       ::= '0' | ... | '9'
eol         ::= '\n'

# Ignore

comment     ::= @ (char)* eol | '/' '*' (char | eol)* '*' '/'
whitespace  ::=  (' ' | '\t') (' ' | '\t')* 

*/

#define SCAN_TOKEN_LEN 64
#define SCAN_TOKEN_TABLE_LEN 1024
#define SCAN_INPUT_LEN 2048

enum scan_token_enum {
    TK_IDENT,    /* (identifier) add, sub, mul, foo, r0, r1, lr, ... */
    TK_DIR,      /* (directive) .global */
    TK_IMM,      /* #1, #-2, ... */
    TK_COMMA,    /* , */
    TK_LBRACKET, /* [ */
    TK_RBRACKET, /* ] */
    TK_COLON,    /* : */
    TK_EOL,      /* End of line */
    TK_EOT,      /* End of text */
    TK_NONE,     /* Invalid token */
    TK_ANY,      /* Special whilecard token for parsing */
};


#define SCAN_TOKEN_STRINGS {"IDENT", "DIR", "IMM", "COMMA", \
                            "LBRACKET", "RBRACKET", "COLON",\
                            "EOL", "EOT", "NONE", "ANY"};

struct scan_token_st {
    enum scan_token_enum id;
    char value[SCAN_TOKEN_LEN];
};

struct scan_table_st {
    struct scan_token_st table[SCAN_TOKEN_TABLE_LEN];
    int len;
    int next;
};

void scan_table_init(struct scan_table_st *st);
void scan_table_scan(struct scan_table_st *st, char *input, int len);
void scan_table_print(struct scan_table_st *st);
struct scan_token_st * scan_table_get(struct scan_table_st *st, int i);
bool scan_table_accept(struct scan_table_st *st, enum scan_token_enum tk_expected);
void scan_table_accept_any_n(struct scan_table_st *st, int n);

/*
 * parse.c
 */

/*
A simple grammar for ARM assembly

program     ::= statements EOT

statements  ::= statement EOL
              | statement EOL statements

statement   ::= directive
              | label ":" instruction
              | instruction

directive   ::= "." ident

instruction ::= dp register "," register "," register
              | dp register "," register "," immediate
              | mem register "," "[" register "]"
              | mem register "," "[" register "," immediate "]"
              | branch label
              | bx register

register    ::= "r0" | "r1" | ...| "r15" | "sp" | "lr" | "ip"

dp          ::= "add" | "cmp" | "lsl" | "lsr" | "mov"

mem         ::= "ldr" |"ldrb" | "str" | "strb"

branch      ::= "b" | "bl" | beq" | "bne" | "bgt" | "bge" | "blt" | "ble"

bx          ::= "bx"

*/

enum parse_opcode_enum {OC_DP, OC_BX, OC_NONE};

#define PARSE_DP_OPS {"add", NULL}
#define PARSE_BX_OPS {"bx", NULL}

enum parse_stmt_enum {INST, SEQ};
enum parse_inst_enum {DP3, BX};

struct parse_node_st {
    enum parse_stmt_enum type;
    union {
        struct {
            char label[SCAN_TOKEN_LEN];
            char name[SCAN_TOKEN_LEN];
            enum parse_inst_enum type;
            union {
                struct {int rd; int rn; int rm;} dp3;
                struct bx {int rn;} bx;
            };
        } inst;
        struct {
            struct parse_node_st *left;
            struct parse_node_st *right;
        } seq;
    } stmt;
};


#define PARSE_TABLE_LEN 1024

struct parse_table_st {
    struct parse_node_st table[PARSE_TABLE_LEN];
    int len;
};

struct parse_reg_pair_st {
    char *name;
    int num;
};

#define PARSE_REG_PAIR_MAP \
   { {"r0", 0}, {"r1", 1}, {"r2", 2,}, {"r3", 3}, \
     {"r4", 4}, {"r5", 5}, {"r6", 6,}, {"r7", 7}, \
     {"r8", 8}, {"r9", 9}, {"r10", 10}, {"r11", 11}, \
     {"r12", 12}, {"r13", 13}, {"r14", 14,}, {"r15", 15}, \
     {"fp", 11}, {"ip", 12}, {"sp", 13}, {"lr", 14}, {"pc", 15} }


void parse_table_init(struct parse_table_st *pt);
struct parse_node_st * parse_node_new(struct parse_table_st *pt);
void parse_tree_print(struct parse_node_st *np);
struct parse_node_st * parse_program(struct parse_table_st *pt, 
                                     struct scan_table_st *st);


/*
 * codegen.c
 */

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
};

struct codegen_map_st {
    char *name;
    uint32_t bits;
};

#define CODEGEN_OPCODE_MAP \
    { {"add", 0b0100} };

enum codegen_cond {
    COND_EQ, COND_NE, COND_CS, COND_CC, COND_MI, COND_PL, COND_VS, COND_VC,
    COND_HI, COND_LS, COND_GE, COND_LT, COND_GT, COND_LE, COND_AL,
};

#define CODEGEN_BCC_MAP { \
    {"b",   COND_AL}, {"bl",  COND_AL}, {"beq", COND_EQ}, {"bne", COND_NE}, \
    {"bcs", COND_CS}, {"bcc", COND_CC}, {"bmi", COND_MI}, {"bpl", COND_PL}, \
    {"bvs", COND_VS}, {"bvc", COND_VC}, {"bhi", COND_HI}, {"bls", COND_LS}, \
    {"bge", COND_GE}, {"blt", COND_LT}, {"bgt", COND_GT}, {"ble", COND_LE}, \
    };

void codegen_table_init(struct codegen_table_st *ct, struct parse_node_st *tree);
void codegen_stmt(struct codegen_table_st *ct, struct parse_node_st *np);
void codegen_print_hex(struct codegen_table_st *ct);
void codegen_hex_write(struct codegen_table_st *ct, struct parse_node_st *np, char *path);

#endif /* _ARMASM_H */
