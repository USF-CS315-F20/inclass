/* ntcalc.c */

#include "ntcalc.h"

struct config_st {
    char input[SCAN_INPUT_LEN];
    int base;
};

void ntcalc_config_init(struct config_st *cp) {
    cp->input[0] = '\0';
    cp->base = 10;
}

void ntcalc_print_usage (void) {
    printf("usage: ./ntcalc [-b base] -e \"expr\"\n");
    printf("  -b base can be 2 or 10\n");
    printf("  examples: ./lab03 -e \"1 + 2\"\n");
    printf("  examples: ./lab03 -b 2 -e \"~(0b1110 >> 2)\"\n");  
}

void ntcalc_parse_args(int argc, char **argv, struct config_st *cp) {
    int i = 1;

    if (argc == 1) {
        ntcalc_print_usage();
        exit(0);
    }

    while (i < argc) {
        if (argv[i][0] == '-' && argv[i][1] == 'e') {
            strncpy(cp->input, argv[i+1], SCAN_INPUT_LEN);
            i += 2;
        } else if (argv[i][0] == '-' && argv[i][1] == 'b') {
            cp->base = atoi(argv[i+1]);
            i += 2;
        }
    }

    if (!((cp->base == 2) || (cp->base == 10))) {
        printf("Invalid base\n");
        ntcalc_print_usage();
        exit(-1);
    }

    if (strnlen(cp->input, SCAN_INPUT_LEN) == 0) {
        printf("No expression provided\n");
        ntcalc_print_usage();
        exit(-1);
    }
}

int main(int argc, char **argv) {

    /* scanning with new simplified ntcalc scanner */
    struct scan_table_st scan_table;
    struct parse_table_st parse_table;
    struct parse_node_st *parse_tree;
    int len;
    uint32_t result;
    struct config_st config;

    ntcalc_config_init(&config);
    ntcalc_parse_args(argc, argv, &config);

    /* Remove this line in your final solution */
    printf("config.base = %d\n", config.base);
    
    len = strnlen(config.input, SCAN_INPUT_LEN);

    scan_table_init(&scan_table);
    scan_table_scan(&scan_table, config.input, len);
    //scan_table_print(&scan_table);

    parse_table_init(&parse_table);
    parse_tree = parse_program(&parse_table, &scan_table);
    //parse_tree_print(parse_tree);

    result = eval_tree(parse_tree);
    printf("%u\n", result);

    return 0;
}
