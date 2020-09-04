/* eval.c - tree interpretation */

#include "ntcalc.h"

int eval_tree(struct parse_node_st *np) {
    int v1, v2;
    
    if (np->type == EX_INTVAL) {
        return np->intval.value;
    } else if (np->type == EX_OPER2) {
        v1 = eval_tree(np->oper2.left);
        v2 = eval_tree(np->oper2.right);
        if (np->oper2.oper == OP_PLUS) {
            return v1 + v2;
        } else if (np->oper2.oper == OP_MINUS) {
            return v1 - v2;
        } else if (np->oper2.oper == OP_MULT) {
            return v1 * v2;
        } else if (np->oper2.oper == OP_DIV) {
            return v1 / v2;
        }
    }
}
