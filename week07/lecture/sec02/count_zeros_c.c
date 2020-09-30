int count_zeros_c(int *array, int len) {
    /* Pointer version */
    int count = 0;
    int i;

    for (i = 0; i < len; i++) {
        if (*array == 0) {
            count += 1;
        }
        array += 1;
    }

    return count;
}

int count_zeros_index_c(int array[], int len) {
    /* Index version */
    int count = 0;
    int i;

    for (i = 0; i < len; i++) {
        if (array[i] == 0) {
            count += 1;
        }
    }

    return count;
}
