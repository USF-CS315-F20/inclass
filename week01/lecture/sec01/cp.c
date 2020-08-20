#include <stdbool.h>
#include <stdio.h>

int main(int argc, char **argv) {
    FILE *f_in, *f_out;
    char ch;
    int rv;

    if (argc != 3) {
        printf("usage: cp <input_file> <output_file>\n");
        return -1;
    }

    f_in = fopen(argv[1], "r");

    if (!f_in) {
        printf("fopen failed on %s\n", argv[1]);
        return -1;
    }

    f_out = fopen(argv[2], "w");

    if (!f_out) {
        printf("fopen failed on %s\n", argv[2]);
        return -1;
    }
    
    do {
        rv = fread(&ch, sizeof(char), 1, f_in);
        if (rv == 0) {
            break;
        }
        fwrite(&ch, sizeof(char), 1, f_out);        
    } while (true);

    fclose(f_in);
    fclose(f_out);

    return 0;
}

    
        
