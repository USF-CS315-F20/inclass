/*
int in_range_c(r0, r1, x) {
    return (x >= r0) && (x <= r1);    
}
*/

int in_range_c(int start, int end, int x) {
    int r = 0;

    if (x >= start) {
        if (x <= end) {
            r = 1;
        }
    }

    return r;
}
