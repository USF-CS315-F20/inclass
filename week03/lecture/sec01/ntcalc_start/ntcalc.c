/* ntcalc.c */

#include "ntcalc.h"

int main(int argc, char **argv) {

    /* scanning with new limited ntcalc scanner */
    struct scan_table_st scan_table;

    char *input = "1 + 2";
    int len;

    len = strnlen(input, SCAN_INPUT_LEN);

    scan_table_init(&scan_table);
    scan_table_scan(&scan_table, input, len);
    scan_table_print(&scan_table);

    /* parse tree construction manaul */

    struct parse_node_st node1;
    struct parse_node_st node2;
    struct parse_node_st node3;

    node1.type = EX_INTVAL;
    node1.intval.value = 1;

    node2.type = EX_INTVAL;
    node2.intval.value = 2;

    node3.type = EX_OPER2;
    node3.oper2.oper = OP_PLUS;
    node3.oper2.left = &node1;
    node3.oper2.right = &node2;

    parse_tree_print(&node3);

    /* parse tree construction from parse_table */
    struct parse_node_st *np1, *np2, *np3;
    struct parse_table_st parse_table;

    parse_table_init(&parse_table);

    np1 = parse_node_new(&parse_table);
    np1->type = EX_INTVAL;
    np1->intval.value = 1;
    
    np2 = parse_node_new(&parse_table);
    np2->type = EX_INTVAL;
    np2->intval.value = 1;
    
    np3 = parse_node_new(&parse_table);
    np3->type = EX_OPER2;
    np3->oper2.oper = OP_PLUS;
    np3->oper2.left = np1;
    np3->oper2.right = np2;

    parse_tree_print(np3);

    /* parse */
    struct parse_node_st *parse_tree;

    parse_table_init(&parse_table);
    parse_tree = parse_expression(&parse_table, &scan_table);
    parse_tree_print(parse_tree);
    
    return 0;
}
