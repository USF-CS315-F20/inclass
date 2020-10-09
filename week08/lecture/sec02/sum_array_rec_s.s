/* sum_array_rec_s.s - recursive sum_array in assembly */

.global sum_array_rec_s

/*
 * r0 - int *array
 * r1 - int index
 * r2 - int len
 */
 
sum_array_rec_s:
    sub sp, sp, #8
    str lr, [sp]
    
    sub r3, r2, #1
    cmp r1, r3
    bne sum_array_rec_step
    ldr r0, [r0, r1, LSL #2]
    b sum_array_rec_end

sum_array_rec_step:
    ldr r3, [r0, r1, LSL #2]
    str r3, [sp, #4]

    add r1, r1, #1    
    bl sum_array_rec_s

    ldr r3, [sp, #4]
    add r0, r0, r3

sum_array_rec_end:
    ldr lr, [sp]
    add sp, sp, #8
    bx lr
