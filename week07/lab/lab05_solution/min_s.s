/* min_s.s - simple min function */

.global min_s
.global min2_s

/* a is r0, b is r1 */
min_s:
    cmp r0, r1
    blt min_r0
    mov r0, r1
min_r0:
    bx lr

/* A different, more general approach */
min2_s:
    cmp r0, r1
    bgt min2_r1
    mov r0, r0
    b min2_end
min2_r1:
    mov r0, r1
min2_end:
    bx lr
