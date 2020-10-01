/* add4_s.s - add 4 args using add2_s */

.global add4_s

add2_s:
    add r0, r0, r1
    bx lr

/*
 * r0 - v0
 * r1 - v1
 * r2 - v2
 * r3 - v3
 */
add4_s:
    sub sp, sp, #8
    str lr, [sp]

    bl add2_s
    /* r0 = r0 + r1 */

    mov r1, r2    
    bl add2_s
    /* r0 = r0 + r1 + r2 */

    mov r1, r3
    bl add2_s

    ldr lr, [sp]
    add sp, sp, #8
    bx lr
