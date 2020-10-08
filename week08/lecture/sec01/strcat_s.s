/* strcat_s.s - strcat in assembly */

.global strcat_s

/*
 * r0 - char *dst
 * r1 - char *src
 *
 * r2 = char *d
 */
strcat_s:
    mov r2, r0      /* r2(d) = dst */

strcat_find_end_loop:
    ldrb r3, [r2]   /* r3 = *d */
    cmp r3, #0
    beq strcat_copy_loop
    add r2, r2, #1
    b strcat_find_end_loop
    
strcat_copy_loop:
    ldrb r3, [r1]
    cmp r3, #0
    beq strcat_end
    strb r3, [r2]
    add r1, r1, #1
    add r2, r2, #1
    b strcat_copy_loop

strcat_end:
    strb r3, [r2]
    bx lr
