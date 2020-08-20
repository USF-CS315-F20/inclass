#include <stdbool.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    FILE *f;
    char ch;
    int rv;

    if (argc != 2) {
        printf("usage: cat <filename>\n");
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
        printf("%c", ch);
    } while(true);

    fclose(f);

    return 0;
}
