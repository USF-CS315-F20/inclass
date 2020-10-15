/* parse.c - parsing and parse tree construction */

#include "armasm.h"

char *parse_dp_ops[] = PARSE_DP_OPS;
char *parse_bx_ops[] = PARSE_BX_OPS;

struct parse_reg_pair_st parse_reg_map[] = PARSE_REG_PAIR_MAP;


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


/* Parsing helpers */

bool parse_is_member(char *s, char **list) {
    char **p;
    bool rv = false;

    for (p = list; *p != NULL; p = p + 1) {
        if (strncmp(s, *p, SCAN_TOKEN_LEN) == 0) {
            rv = true;
            break;
        }
    }

    return rv;
}

enum parse_opcode_enum parse_opcode(struct scan_token_st *tp) {
    enum parse_opcode_enum rv = OC_NONE;

    if (parse_is_member(tp->value, parse_dp_ops)) {
        rv = OC_DP;
    } else if (parse_is_member(tp->value, parse_bx_ops)) {
        rv = OC_BX;
    } else {
        parse_error("Bad opcode");
    }

    return rv;
}

int parse_reg_to_int(char *s) {
    int i;
    int reg_map_len = sizeof(parse_reg_map) / sizeof(parse_reg_map[0]);

    for (i = 0; i < reg_map_len; i++) {
        if (strncmp(s, parse_reg_map[i].name, SCAN_TOKEN_LEN) == 0) {
            return parse_reg_map[i].num;
        }
    }

    parse_error("Bad register name");
    return 0;
}

void parse_eols(struct scan_table_st *st) {
    while (scan_table_accept(st, TK_EOL));
}

/* These prototypes are needed for the mutual recursion between
   parse_expression() and parse_operand()
*/


struct parse_node_st * parse_statements(struct parse_table_st *pt,
                                        struct scan_table_st *st);
struct parse_node_st * parse_statement(struct parse_table_st *pt,
                                       struct scan_table_st *st);                                        
struct parse_node_st * parse_instruction(struct parse_table_st *pt,
                                       struct scan_table_st *st);



struct parse_node_st * parse_program(struct parse_table_st *pt,
                             struct scan_table_st *st) {
    struct parse_node_st *np;

    np = parse_statements(pt, st);
    if (!scan_table_accept(st, TK_EOT)) {
        parse_error("expecting EOT");
    }
    
    return np;
}

struct parse_node_st * parse_statements(struct parse_table_st *pt,
                                        struct scan_table_st *st) {

    struct parse_node_st *np, *np1, *np2;
    enum scan_token_enum tid;

    parse_eols(st);
    np = parse_statement(pt, st);
    if (!scan_table_accept(st, TK_EOL)) {
        parse_error("expecting EOL");
    }
    parse_eols(st);

    tid = scan_table_get(st, 0)->id;
    if (tid != TK_EOT) {
        /* Recursively add more statements to parse tree */
        np1 = parse_node_new(pt);
        np1->type = SEQ;
        np2 = parse_statements(pt, st);
        np1->stmt.seq.left = np;
        np1->stmt.seq.right = np2;
        np = np1;
    }

    return np;
}

struct parse_node_st * parse_statement(struct parse_table_st *pt,
                                       struct scan_table_st *st) {
    struct parse_node_st *np;

    np = parse_instruction(pt, st);

    return np;
}

struct parse_node_st * parse_instruction(struct parse_table_st *pt,
                                       struct scan_table_st *st) {
    struct scan_token_st *tp0, *tp1, *tp2, *tp3, *tp4, *tp5;
    struct parse_node_st *np;
    enum parse_opcode_enum opcode;

    np = parse_node_new(pt);
    np->type = INST;

    /* Parse instruction label if it exists. */

    tp0 = scan_table_get(st, 0);
    tp1 = scan_table_get(st, 1);

    if (tp0->id == TK_IDENT && tp1->id == TK_COLON) {
        tp0 = scan_table_get(st, -2);
        strncpy(np->stmt.inst.label, tp0->value, SCAN_TOKEN_LEN);
        /* Accept the two tokens */
        scan_table_accept_any_n(st, 2);
        /* Skip over newlines */        
        parse_eols(st);
    }

    /* Parse instruction */
    
    tp0 = scan_table_get(st, 0);
    opcode = parse_opcode(tp0);

    tp1 = scan_table_get(st, 1);
    tp2 = scan_table_get(st, 2);
    tp3 = scan_table_get(st, 3);
    tp4 = scan_table_get(st, 4);
    tp5 = scan_table_get(st, 5);                

     if ((opcode == OC_DP) && (tp1->id == TK_IDENT) && 
         (tp2->id = TK_COMMA) && (tp3->id == TK_IDENT) && 
         (tp4->id == TK_COMMA) && (tp5->id == TK_IDENT)) {
        /* Parse dp3 instructions: op reg, reg, reg */
  
        np->stmt.inst.type = DP3;
        strncpy(np->stmt.inst.name, tp0->value, SCAN_TOKEN_LEN);
        np->stmt.inst.dp3.rd = parse_reg_to_int(tp1->value);
        np->stmt.inst.dp3.rn = parse_reg_to_int(tp3->value);
        np->stmt.inst.dp3.rm = parse_reg_to_int(tp5->value);

        /* Accept instruction tokens */
        scan_table_accept_any_n(st, 6);
        
     } else if ((opcode == OC_BX) && (tp1->id == TK_IDENT)) {
        /* Parse bx instructions: bx reg */ 
  
        strncpy(np->stmt.inst.name, tp0->value, SCAN_TOKEN_LEN);
        np->stmt.inst.type = BX;
        np->stmt.inst.bx.rn = parse_reg_to_int(tp1->value);

        /* Accept instruction tokens */
        scan_table_accept_any_n(st, 2);

    } else {
       parse_error("Bad operation");
    }

    return np;        
}

/*
 * Parse tree pretty printing
 */

void parse_tree_print_indent(int level) {
    for (int i = 0; i < level; i++) {
        printf(" ");
    }
}
void parse_tree_print_inst(struct parse_node_st *np, int level) {
    parse_tree_print_indent(level);

    printf("INST ");
    printf("[%s] ", np->stmt.inst.label);

    if (np->stmt.inst.type == DP3) {
        printf("dp3 (%s) %d %d %d\n", np->stmt.inst.name,
            np->stmt.inst.dp3.rd, np->stmt.inst.dp3.rn, np->stmt.inst.dp3.rm);
    } else if (np->stmt.inst.type == BX) {
        printf("bx (%s) %d\n", np->stmt.inst.name, np->stmt.inst.bx.rn);
    }
}

void parse_tree_print_stmt(struct parse_node_st *np, int level) {
    parse_tree_print_indent(level);

    if (np->type == INST) {
        parse_tree_print_inst(np, level+1);
    } else if (np->type == SEQ) {
        printf("SEQ\n");
        parse_tree_print_stmt(np->stmt.seq.left, level+1);
        parse_tree_print_stmt(np->stmt.seq.right, level+1);
    }
}

void parse_tree_print(struct parse_node_st *np) {
    parse_tree_print_stmt(np, 0);
}

