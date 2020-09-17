/* eval.c - tree interpretation */

#include "ntcalc.h"

uint32_t eval_tree(struct parse_node_st *np) {
    uint32_t v1, v2;
    
    if (np->type == EX_INTVAL) {
        return np->intval.value;
    } else if (np->type == EX_OPER1) {
        v1 = eval_tree(np->oper1.operand);
        if (np->oper1.oper == OP_MINUS) {
            return -v1;
        } else if (np->oper1.oper == OP_NOT) {
            return ~v1;
        }
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
        } else if (np->oper2.oper == OP_LSL) {
            return v1 << v2;
        }
    }
}
