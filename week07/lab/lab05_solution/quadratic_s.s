/* quadratic_s.s - quadratic function */

.global quadratic_s

/* x is r0, a is r1, b is r2, c is r3 */
quadratic_s:
    mul r12, r0, r0   /* x * x */
    mul r12, r1, r12  /* a * x * x */ 
    mul r1, r2, r0    /* b * x */ 
    add r12, r12, r1  /* (a * x * x) + (b * x) */
    add r0, r12, r3   /* (a * x * x) + (b * x) + c */
    bx lr
