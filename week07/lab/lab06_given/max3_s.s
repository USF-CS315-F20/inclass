/* max3_s.s - find the maximum value of three arguments using max2 */

.global max3_s

max2_s:
    cmp r0, r1
    bgt max2_end
    mov r0, r1
max2_end:
    bx lr

/* v0 - r0
 * v1 - r1
 * v2 - r2
 */
max3_s:
    mov r0, #0
    bx lr
