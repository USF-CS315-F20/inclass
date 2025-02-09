/* count_zeros_s.s - count the number of zeros in array pointed to by r0 */

.global count_zeros_s
.global count_zeros_index_s

/*
 * r0 = int *array
 * r1 = int len
 *
 * r2 = int count;
 * r3 = int i;
 */
count_zeros_s:
    mov r2, #0; /* count(r2) = 0 */
    mov r3, #0; /* i(r3) = 0 */

count_zeros_loop:
    cmp r3, r1
    bge count_zeros_loop_end

    ldr r12, [r0]     /* r12 = *array */
    cmp r12, #0
    bne count_zeros_not_zero
    add r2, r2, #1    /* count = count + 1 */
count_zeros_not_zero:
    add r0, r0, #4    /* array = array + 4 */
    add r3, r3, #1    /* i = i + 1 */
    b count_zeros_loop
count_zeros_loop_end:
    mov r0, r2
    bx lr

/*
 * r0 = int *array
 * r1 = int len
 *
 * r2 = int count;
 * r3 = int i;
 */
count_zeros_index_s:
    mov r2, #0; /* count(r2) = 0 */
    mov r3, #0; /* i(r3) = 0 */

count_zeros_index_loop:
    cmp r3, r1
    bge count_zeros_index_loop_end

    ldr r12, [r0, r3, LSL #2]  /* r12 = *(array + (i * 4)) */
    cmp r12, #0
    bne count_zeros_index_not_zero
    add r2, r2, #1    /* count = count + 1 */
count_zeros_index_not_zero:
    add r3, r3, #1    /* i = i + 1 */
    b count_zeros_index_loop
count_zeros_index_loop_end:
    mov r0, r2
    bx lr
