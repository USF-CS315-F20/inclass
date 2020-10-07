int sum_array_rec_c(int *array, int index, int len) {
    if (index == (len - 1)) {
        return array[index];
    } else {
        return array[index] + sum_array_rec_c(array, index + 1, len);
    }
}
