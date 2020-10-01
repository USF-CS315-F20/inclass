/* sum_array_s.s - sum the elements of an array */

.global sum_array_s

/*
 * r0 - int *array
 * r1 - int len
 *
 * r2 - int sum
 * r3 - int i
 */
sum_array_s:
    mov r2, #0
    mov r3, #0

sum_array_loop:
    cmp r3, r1
    bge sum_array_loop_exit
    ldr r12, [r0]
    add r2, r2, r12
    add r0, r0, #4
    add r3, r3, #1
    b sum_array_loop
sum_array_loop_exit:
    mov r0, r2
    bx lr
