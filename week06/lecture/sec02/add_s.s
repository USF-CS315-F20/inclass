/* add_s.s - simple add function */

.global add_s

/* a0 is r0, a1 is r1 */
add_s:
    add r0, r0, r1
    bx lr
