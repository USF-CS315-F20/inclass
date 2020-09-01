/* ntcalc.h */

#ifndef _NTCALC_H
#define _NTCALC_H

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

# Scanner EBNF

tokenlist   ::= (token)*
token       ::= integer | symbol
integer     ::= digit (digit)*
symbol      ::= '+' | '-' | '*' | '/' | '(' | ')'
digit       ::= '0' | ... | '9'

# Ignore

whitespace  ::=  (' ' | '\t') (' ' | '\t')* 

*/

#define SCAN_TOKEN_LEN 32
#define SCAN_TOKEN_TABLE_LEN 1024
#define SCAN_INPUT_LEN 2048

enum scan_token_enum {
    TK_INTLIT, /* -123, 415 */
    TK_LPAREN, /* ( */
    TK_RPAREN, /* ) */
    TK_PLUS,   /* + */
    TK_MINUS,  /* - */
    TK_MULT,   /* * */
    TK_DIV,    /* / */
    TK_EOT,    /* end of text */
};

#define SCAN_TOKEN_STRINGS {"TK_INTLIT", "TK_LPAREN", "TK_RPAREN", \
                            "TK_PLUS", "TK_MINUS", "TK_MULT", "TK_DIV", \
                            "TK_EOT"};

struct scan_token_st {
    enum scan_token_enum id;
    char value[SCAN_TOKEN_LEN];
};

struct scan_table_st {
    struct scan_token_st table[SCAN_TOKEN_TABLE_LEN];
    int len;
    int next;
};

void scan_table_init(struct scan_table_st *tt);
void scan_table_scan(struct scan_table_st *tt, char *input, int len);
void scan_table_print(struct scan_table_st *tt);

/*
 * parse.c
 */

 /*
 A simple grammar for the ntcalc langauge

 # Parser

 expression ::= operand (operator operand)* EOT
 operand    ::= integer
              | '-' operand
              | '(' expression ')'
*/

struct parse_node_st {}


#endif /* _NTCALC_H */
