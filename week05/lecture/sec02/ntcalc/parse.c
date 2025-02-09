/* parse.c - parsing and parse tree construction */

#include "ntcalc.h"


void parse_table_init(struct parse_table_st *pt) {
    pt->len = 0;
}

struct parse_node_st * parse_node_new(struct parse_table_st *pt) {
    struct parse_node_st *np;

    np = &(pt->table[pt->len]);
    pt->len += 1;

    return np;
}

void parse_error(char *err) {
    printf("parse_error: %s\n", err);
    exit(-1);
}

char *parse_oper_strings[] = {"PLUS", "MINUS", "MULT", "DIV", "NOT", "LSL"};

void parse_tree_print_indent(int level) {
    level *= 2;
    for (int i = 0; i < level; i++) {
        printf(".");
    }
}

void parse_tree_print_expr(struct parse_node_st *np, int level) {
    parse_tree_print_indent(level);
    printf("EXPR ");

    if (np->type == EX_INTVAL) {
        printf("INTVAL %d\n", np->intval.value);
    } else if (np->type == EX_OPER1) {
        printf("OPER1 %s\n", parse_oper_strings[np->oper1.oper]);
        parse_tree_print_expr(np->oper1.operand, level+1);
    } else if (np->type == EX_OPER2) {
        printf("OPER2 %s\n", parse_oper_strings[np->oper2.oper]);
        parse_tree_print_expr(np->oper2.left, level+1);
        parse_tree_print_expr(np->oper2.right, level+1);
    }
}

void parse_tree_print(struct parse_node_st *np) {
    parse_tree_print_expr(np, 0);
    
}


/* These prototypes are needed for the mutual recursion between
   parse_expression() and parse_operand()
*/

struct parse_node_st * parse_program(struct parse_table_st *pt, 
                                        struct scan_table_st *st);
struct parse_node_st * parse_expression(struct parse_table_st *pt, 
                                        struct scan_table_st *st);
struct parse_node_st * parse_operand(struct parse_table_st *pt,
                                     struct scan_table_st *st);


struct parse_node_st * parse_program(struct parse_table_st *pt, 
                                        struct scan_table_st *st) {
    struct parse_node_st *np1;

    np1 = parse_expression(pt, st);

    if (!scan_table_accept(st, TK_EOT)) {
        parse_error("Expecting EOT");        
    }

    return np1;                                       
}

enum parse_oper_enum parse_token_oper_lookup(enum scan_token_enum tkid) {
    switch(tkid) {
        case TK_PLUS:
            return OP_PLUS;
        case TK_MINUS:
            return OP_MINUS;
        case TK_MULT:
            return OP_MULT;
        case TK_DIV:
            return OP_DIV;
        case TK_LSL:
            return OP_LSL;
        default:
            parse_error("Invalid operator");
    }
}

struct parse_node_st * parse_expression(struct parse_table_st *pt, 
                                        struct scan_table_st *st) {
    struct scan_token_st *tp;
    struct parse_node_st *np1, *np2;

    np1 = parse_operand(pt, st);

    while (true) {    
        tp = scan_table_get(st, 0);
        if (tp->id == TK_PLUS || tp->id == TK_MINUS
            || tp->id == TK_MULT || tp->id == TK_DIV
            || tp->id == TK_LSL) {
            scan_table_accept(st, TK_ANY);
            np2 = parse_node_new(pt);
            np2->type = EX_OPER2;
            np2->oper2.oper = parse_token_oper_lookup(tp->id);
            np2->oper2.left = np1;
            np2->oper2.right = parse_operand(pt, st);
            np1 = np2;
        } else {
            break;
        }
    }

    return np1;
}

struct parse_node_st * parse_operand(struct parse_table_st *pt,
                                     struct scan_table_st *st) {
    struct scan_token_st *tp;
    struct parse_node_st *np1;

    if (scan_table_accept(st, TK_INTLIT)) {
        tp = scan_table_get(st, -1);
        np1 = parse_node_new(pt);
        np1->type = EX_INTVAL;
        np1->intval.value = atoi(tp->value);
    } else if (scan_table_accept(st, TK_BINLIT)) {
        tp = scan_table_get(st, -1);
        np1 = parse_node_new(pt);
        np1->type = EX_INTVAL;
        np1->intval.value = conv_binstr_to_uint32(tp->value);
    } else if (scan_table_accept(st, TK_MINUS)) {
        np1 = parse_node_new(pt);
        np1->type = EX_OPER1;
        np1->oper1.oper = OP_MINUS;
        np1->oper1.operand = parse_operand(pt, st);
    } else if (scan_table_accept(st, TK_NOT)) {
        np1 = parse_node_new(pt);
        np1->type = EX_OPER1;
        np1->oper1.oper = OP_NOT;
        np1->oper1.operand = parse_operand(pt, st);
    } else if (scan_table_accept(st, TK_LPAREN)) {
        np1 = parse_expression(pt, st);
        if (!scan_table_accept(st, TK_RPAREN)) {
            parse_error("Expecting RPAREN");
        }
    } else {
        parse_error("Bad operand");
    }

    return np1;
}
