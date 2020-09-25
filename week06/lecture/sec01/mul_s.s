/* mul_s.s - simple mul function */

.global mul_s

/* a0 is r0, a1 is r1, a2 is r2 */
mul_s:
    mul r0, r1, r0
    mul r0, r2, r0
    bx lr
