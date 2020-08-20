#include <stdbool.h>
#include <stdio.h>


bool is_whitespace(char ch) {
    return (ch == ' ') || (ch == '\t') || (ch == '\n');
}

int main(int argc, char **argv) {
    FILE *f;
    char ch;
    int rv;
    int count = 0;
    bool in_word = false;

    if (argc != 2) {
        printf("usage: wcount <filename>\n");
        return -1;
    }

    f = fopen(argv[1], "r");

    if (!f) {
        printf("fopen failed on %s\n", argv[1]);
        return -1;
    }

    do {
        rv = fread(&ch, sizeof(char), 1, f);
        if (rv == 0) {
            break;
        }
        if (in_word && is_whitespace(ch)) {
            count += 1;
        }
        in_word = !is_whitespace(ch);
    } while (true);

    fclose(f);

    printf("word count = %d\n", count);
    
    return 0;
}

    
        
