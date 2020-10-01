int fact_c(int n) {
    if (n == 0) {
        return 1;    
    } else {
        return n * fact_c(n - 1);
    }
}
