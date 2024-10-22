/* ntcalc.c */

#include "ntcalc.h"

struct config_st {
    char input[SCAN_INPUT_LEN];
    int base;
    bool debug;
};

void ntcalc_config_init(struct config_st *cp) {
    cp->input[0] = '\0';
    cp->base = 10;
    cp->debug = false;
}

void ntcalc_print_usage (void) {
    printf("usage: ./ntcalc [-b base] -e \"expr\"\n");
    printf("  -b base can be 2 or 10\n");
    printf("  examples: ./ntcalc -e \"1 + 2\"\n");
    printf("  examples: ./ntcalc -b 2 -e \"~(0b1110 >> 2)\"\n");  
}

void ntcalc_parse_args(int argc, char **argv, struct config_st *cp) {
    int i = 1;

    if (argc == 1) {
        ntcalc_print_usage();
        exit(0);
    }

    while (i < argc) {
        if (argv[i][0] == '-' && argv[i][1] == 'e' && (i + 1) < argc) {
            strncpy(cp->input, argv[i + 1], SCAN_INPUT_LEN);
            i += 2;
        } else if (argv[i][0] == '-' && argv[i][1] == 'b' && (i + 1) < argc) {
            cp->base = atoi(argv[i + 1]);
            i += 2;
        } else if (argv[i][0] == '-' && argv[i][1] == 'd') {
            cp->debug = true;
            i += 1;
        } else {
            printf("Invalid option: %s\n", argv[i]);
            exit(-1);
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
    char result_str[SCAN_INPUT_LEN];

    ntcalc_config_init(&config);
    ntcalc_parse_args(argc, argv, &config);

    len = strnlen(config.input, SCAN_INPUT_LEN);

    scan_table_init(&scan_table);
    scan_table_scan(&scan_table, config.input, len);
    if (config.debug) {
        scan_table_print(&scan_table);
    }
    
    parse_table_init(&parse_table);
    parse_tree = parse_program(&parse_table, &scan_table);
    if (config.debug) {
        parse_tree_print(parse_tree);
    }

    result = eval_tree(parse_tree);
    if (config.base == 2) {
        conv_uint32_to_binstr(result, result_str);
        printf("%s\n", result_str);
    } else if (config.base == 10) {
        printf("%u\n", result);
    }
    
    return 0;
}
