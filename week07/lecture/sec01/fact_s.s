/* fact_s.s - recursive factorial in assembly */

.global fact_s

/*
 * r0 - int n
 */
fact_s:
    sub sp, sp, #8  /* allocate 2 words on the stack */
    str lr, [sp]    /* save lr on the stack at stack + 0 */

    /* check for base case */
    cmp r0, #0
    bne fact_rec

    /* base case, n == 0 */
    mov r0, #1

    /* branch to fact_end so that we restore lr and adjust SP */
    b fact_end

    /* recursive step */
fact_rec: 
    
    str r0, [sp, #4] /* save r0 (n) on the stack at stack + 4 */
    sub r0, r0, #1   /* compute n - 1 put into r0 (arg0) */

    bl fact_s        /* call fact_s(n - 1) */

    ldr r1, [sp, #4] /* restore previous r0 (n) from stack at stack + 4 */
    mul r0, r1, r0   /* compute n * fact_s(n - 1), put into r0 (return value) */
                 
fact_end:
    ldr lr, [sp]     /* restore lr from stack at stack + 0 */
    add sp, sp, #8   /* restore sp to original value */
    bx lr

