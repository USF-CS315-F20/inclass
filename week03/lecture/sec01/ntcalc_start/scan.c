/* scan.c - token scanner */

#include "ntcalc.h"

char *scan_token_strings[] = SCAN_TOKEN_STRINGS;

void scan_error(char *err) {
    printf("scan_error: %s\n", err);
    exit(-1);
}

void scan_table_init(struct scan_table_st *st) {
    st->len = 0;
    st->next = 0;
}

struct scan_token_st * scan_table_new_token(struct scan_table_st *st) {
    struct scan_token_st *tp;

    tp = &st->table[st->len];
    st->len += 1;

    return tp;
}

char * scan_read_token(struct scan_token_st *tp, char *p, int len,
                       enum scan_token_enum id) {
    /* Read a token starting a p for len characters.
       Update the given token with the token string and token id. */
    int i;

    tp->id = id;
    for (i = 0; i < len; i++) {
        tp->value[i] = *p;
        p += 1;
    }
    tp->value[i] = '\0';
    return p;
}

bool scan_is_digit(char c) {
    return c >= '0' && c <= '9';
}

bool scan_is_whitespace(char c) {
    return (c == ' ' || c == '\t');
}

char * scan_whitespace(char *p, char *end) {
    while (scan_is_whitespace(*p) && (p < end)) {
        p += 1;
    }
    return p;
}
    
char * scan_integer(char *p, char *end, struct scan_token_st *tp) {
    int i = 0;
    while (scan_is_digit(*p) && p < end) {
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
        p = scan_read_token(tp, p, 0, TK_EOT);
    } else if (scan_is_whitespace(*p)) {
        p = scan_whitespace(p, end);
        p = scan_token(p, end, tp);
    } else if (scan_is_digit(*p)) {
        p = scan_integer(p, end, tp);
    } else if (*p == '+') {
        p = scan_read_token(tp, p, 1, TK_PLUS);
    } else if (*p == '-') {
        p = scan_read_token(tp, p, 1, TK_MINUS);
    } else if (*p == '*') {
        p = scan_read_token(tp, p, 1, TK_MULT);
    } else if (*p == '/') {
        p = scan_read_token(tp, p, 1, TK_DIV);                        
    } else if (*p == '(') {
        p = scan_read_token(tp, p, 1, TK_LPAREN);
    } else if (*p == ')') {
        p = scan_read_token(tp, p, 1, TK_RPAREN);        
    } else {
        scan_error("Invalid character");
    }

    return p;
}

void scan_table_scan(struct scan_table_st *st, char *input, int len) {
    struct scan_token_st *tp;
    char *p = input;
    char *end = p + len;

    while(true) {
        tp = scan_table_new_token(st);
        p = scan_token(p, end, tp);
        if (tp->id == TK_EOT) {
            break;
        }
    }
}

void scan_token_print(struct scan_token_st *t) {
    printf("%s(\"%s\")\n", scan_token_strings[t->id], t->value);
}

void scan_table_print(struct scan_table_st *st) {
    int i;

    for (i = 0; i < st->len; i++) {
        scan_token_print(&st->table[i]);
    }
}

struct scan_token_st * scan_table_get(struct scan_table_st *st, int i) {
    return &(st->table[st->next + i]);
}

bool scan_table_accept(struct scan_table_st *st, enum scan_token_enum tk_expected) {
    struct scan_token_st *tp;

    if (tk_expected == TK_ANY) {
        st->next += 1;
        return true;
    }

    tp = scan_table_get(st, 0);

    if (tp->id == tk_expected) {
        st->next += 1;
        return true;
    }

    return false;
}


