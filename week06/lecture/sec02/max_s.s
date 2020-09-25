/* max_s.s - simple max function */

.global max_s

/* a0 is r0, a1 is r1 */
max_s:
    cmp r0, r1
    bgt max_end
    mov r0, r1    
max_end:
    bx lr
