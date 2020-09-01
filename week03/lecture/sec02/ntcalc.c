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

    return 0;
}
