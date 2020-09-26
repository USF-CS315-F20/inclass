#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_PATH 256

int main(int argc, char **argv) {
    int id;
    char progname[MAX_PATH];

    if (argc != 2) {
        printf("usage: ./lab05 <progname>\n");
        exit(-1);
    }

    progname[0] = '\0';
    strncpy(progname, argv[1], MAX_PATH);

    id = fork();

    if (id == 0) {
        execl(progname, progname, NULL);
        printf("execl(%s) failed\n", progname);
    }

    wait(NULL);   

    return(0);
}
