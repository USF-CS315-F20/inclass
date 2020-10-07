char *strcat_c(char *dst, char *src) {
    char *d = dst;
    while (*d != '\0')
        d++;
    while (*src != '\0') {
        *d = *src;
        d++;
        src++;
    }
    *d = '\0';
    return dst;
}
