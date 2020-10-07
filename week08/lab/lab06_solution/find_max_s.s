/* find_max_s - find the maximum value in an interger array */

.global find_max_s

/*
 * r0 - int *array
 * r1 - int n
 *
 * r2 - int i
 * r3 - int max
 */     
find_max_s:
    mov r2, #1
    ldr r3, [r0]              /* r3 = array[0] */

find_max_loop:
    cmp r2, r1
    bge find_max_loop_exit
    ldr r12, [r0, r2, LSL #2] /* r12 = array[i] */
    cmp r12, r3
    ble find_max_not_greater
    mov r3, r12               /* r3 = array[i] */    

find_max_not_greater:
    add r2, r2, #1
    b find_max_loop

find_max_loop_exit:
    mov r0, r3
    bx lr
