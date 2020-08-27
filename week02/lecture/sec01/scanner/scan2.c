/* scan1.c

tokens ::= (token)*
token  ::= integer | symbol
symbol ::= '+' | '-' | '*' | '/' | '='
integer ::= digit (digit)*
digit  ::= '0' | '1' | ... | '9'

# ignore
whitespace ::= ' ' | '\t'

*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SCAN_TOKEN_LEN 32
#define SCAN_TABLE_LEN 4096
#define SCAN_TEXT_LEN 8192

enum scan_token_enum {
                      TK_INTLIT,/* 1, 22, 403 */
                      TK_PLUS,  /* + */
                      TK_MINUS, /* - */
                      TK_MULT,  /* * */
                      TK_DIV,   /* / */
                      TK_EQ,    /* = */
                      TK_EOT,   /* end of text */
};

char *scan_token_strings[] = {"TK_INTLIT", "TK_PLUS", "TK_MINUS", "TK_MULT",
                              "TK_DIV", "TK_EQ", "TK_EOT"};

struct scan_token_st {
    enum scan_token_enum id;
    char value[SCAN_TOKEN_LEN];
};

struct scan_table_st {
    struct scan_token_st table[SCAN_TABLE_LEN];
    int len;
};
    
void scan_token_print(struct scan_token_st *tp) {
    printf("%s(\"%s\")\n", scan_token_strings[tp->id], tp->value);
}

void scan_table_print(struct scan_table_st *st) {
    int i;

    for (i = 0; i < st->len; i++) {
        scan_token_print(&st->table[i]);
    }
}

void scan_table_init(struct scan_table_st *st) {
    st->len = 0;
}

struct scan_token_st * scan_table_new_token(struct scan_table_st *st) {
    struct scan_token_st *tp;

    tp = &(st->table[st->len]);
    st->len += 1;

    return tp;
}

bool scan_is_whitespace(char ch) {
    return (ch == ' ') || (ch == '\t');
}

char *scan_whitespace(char *p, char *end) {
    while(scan_is_whitespace(*p) && (p < end)) {
        p += 1;
    }
    return p;
}


bool scan_is_digit(char ch) {
    return (ch >= '0' && ch <= '9');
}

char * scan_integer(char *p, char *end, struct scan_token_st *tp) {
    int i = 0;

    while (scan_is_digit(*p) && (p < end)) {
        tp->value[i] = *p;
        p += 1;
        i += 1;
    }
    tp->value[i] = '\0';
    tp->id = TK_INTLIT;
    
    return p;
}

char * scan_token(char *p, char *end, struct scan_token_st *tp) {
    if (p == end) {
        tp->value[0] = '\0';
        tp->id = TK_EOT;
    } else if (scan_is_whitespace(*p)) {
        p = scan_whitespace(p, end);
        p = scan_token(p, end, tp);
    } else if (scan_is_digit(*p)) {
        p = scan_integer(p, end, tp);
    } else if (*p == '+') {
        tp->value[0] = *p;
        tp->value[1] = '\0';
        tp->id = TK_PLUS;
        p += 1;
    } else if (*p == '-') {
        tp->value[0] = *p;
        tp->value[1] = '\0';
        tp->id = TK_MINUS;
        p += 1;
    } else {
        printf("scan error: invalid char\n");
        exit(-1);
    }
    return p;
}

void scan_table_scan(struct scan_table_st *st, char *input, int len) {
    /* Scan input text for tokens. Put tokens into scan_table st */
    struct scan_token_st *tp;
    char *p = input;
    char *end;

    end = p + len;

    do {
        tp = scan_table_new_token(st);
        p = scan_token(p, end, tp);
        if (tp->id == TK_EOT) {
            break;
       }
    } while(true);
}

int main(int argc, char **argv) {
    struct scan_table_st scan_table;
    int len;
    
    char *input = "1 + 2 - 99 + 33";
    len = strnlen(input, SCAN_TEXT_LEN);
    
    scan_table_init(&scan_table);
    scan_table_scan(&scan_table, input, len);
    scan_table_print(&scan_table);
    
    return(0);
}
