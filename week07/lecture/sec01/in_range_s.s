/* in_range_s.s - check if r0 <= r2 <= r1 */

.global in_range_s

/*
 * start - r0 (r3)
 * end   - r1
 * x     - r2
 */
in_range_s:
    mov r3, r0; /* r3 = start */
    mov r0, #0;
    cmp r2, r3
    blt in_range_end /* branch if x(r2) < start(r3) */
    cmp r2, r1
    bgt in_range_end /* branch if x(r2) > end(r1) */
    mov r0, #1
in_range_end:
    bx lr
    
