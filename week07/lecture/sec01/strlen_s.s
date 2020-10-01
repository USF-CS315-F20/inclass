/* strlen_s.s - strlen in assembly */

.global strlen_s

/*
 * r0 = char *s
 *
 * r1 = int len
 */
strlen_s:
    mov r1, #0

strlen_s_loop:
    ldrb r2, [r0]
    cmp r2, #0
    beq strlen_s_loop_exit
    add r1, r1, #1
    add r0, r0, #1
    b strlen_s_loop
strlen_s_loop_exit:
    mov r0, r1
    bx lr
