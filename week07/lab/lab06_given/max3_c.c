int max2_c(int v0, int v1) {
    int r;

    if (v0 > v1) {
        r = v0;        
    } else {
        r = v1;
    }

    return r;
}

int max3_c(int v0, int v1, int v2) {
    int r;

    r = max2_c(v0, v1);
    r = max2_c(r, v2);

    return r;
}
