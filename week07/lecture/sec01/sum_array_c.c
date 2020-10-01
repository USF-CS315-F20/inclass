int sum_array_c(int *array, int len) {
    int sum = 0;
    int i;

    for (i = 0; i < len; i++) {
        sum = sum + *array;
        array += 1;
    }

    return sum;
}
