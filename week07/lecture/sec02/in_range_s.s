/* in_range_s.s - check if r0 <= r2 <= r1 */

.global in_range_s

/*
 * r0 - int start
 * r1 - int end
 * r2 - int x
 */

in_range_s:
    mov r3, r0; /* r3 = start */
    mov r0, #0;
    cmp r2, r3
    blt in_range_end
    cmp r2, r1
    bgt in_range_end
    mov r0, #1
in_range_end:
    bx lr
