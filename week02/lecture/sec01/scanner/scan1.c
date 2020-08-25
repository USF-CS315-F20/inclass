/* scan1.c

tokens ::= (symbol)*
symbol ::= '+' | '-' | '*' | '/' | '='

*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SCAN_TOKEN_LEN 32
#define SCAN_TABLE_LEN 4096
#define SCAN_TEXT_LEN 8192

enum scan_token_enum {
                      TK_PLUS,  /* + */
                      TK_MINUS, /* - */
                      TK_MULT,  /* * */
                      TK_DIV,   /* / */
                      TK_EQ,    /* = */
                      TK_EOT,   /* end of text */
};

char *scan_token_strings[] = {"TK_PLUS", "TK_MINUS", "TK_MULT", "TK_DIV",
                              "TK_EQ", "TK_EOT"};

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

char * scan_token(char *p, char *end, struct scan_token_st *tp) {
    if (p == end) {
        tp->value[0] = '\0';
        tp->id = TK_EOT;
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

void scan_table_scan(struct scan_table_st *st, char *input) {
    struct scan_token_st *tp;
    char *p = input;
    char *end;
    int len;

    len = strnlen(input, SCAN_TEXT_LEN);
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
    char *input = "+-+";

    scan_table_init(&scan_table);
    scan_table_scan(&scan_table, input);
    scan_table_print(&scan_table);
    
    return(0);
}
