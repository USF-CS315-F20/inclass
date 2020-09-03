/* ntcalc.c */

#include "ntcalc.h"

int main(int argc, char **argv) {

    /* scanning with new simplified ntcalc scanner */
    struct scan_table_st scan_table;
    struct parse_table_st parse_table;
    struct parse_node_st *parse_tree;

    char input[SCAN_INPUT_LEN];
    int len;

    if ((argc != 3) || (strncmp(argv[1], "-e", SCAN_TOKEN_LEN) != 0)) {
        printf("usage: ./lab03 -e \"expr\"\n");
        printf("  example: ./lab03 -e \"1 + 2\"\n");
        exit(-1);
    }

    strncpy(input, argv[2], SCAN_INPUT_LEN);
    len = strnlen(input, SCAN_INPUT_LEN);

    scan_table_init(&scan_table);
    scan_table_scan(&scan_table, input, len);
    //scan_table_print(&scan_table);

    parse_table_init(&parse_table);
    parse_tree = parse_expression(&parse_table, &scan_table);
    parse_tree_print(parse_tree);

    return 0;
}
