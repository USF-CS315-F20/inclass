int strlen_c(char *s) {
    int len = 0;

    while (*s != '\0') {
        len += 1;
        s += 1;
    }

    return len;
}
