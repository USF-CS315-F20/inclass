int find_max_c(int *array, int n)
{
    int i;
    int max = array[0];

    for (i = 1; i < n; i++) {
        if (array[i] > max) {
            max = array[i];
        }
    }

    return max; 
}
