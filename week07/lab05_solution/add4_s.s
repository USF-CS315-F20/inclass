/* add4_s.s - simple add function */

.global add4_s

/* a0 is r0, a1 is r1, a2 is r2, a3 is r3 */
add4_s:
    add r0, r0, r1
    add r0, r0, r2
    add r0, r0, r3
    bx lr
