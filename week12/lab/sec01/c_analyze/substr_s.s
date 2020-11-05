.global substr_s
.global match_s

substr_s:
    sub sp, sp, #24
    str lr, [sp, #0]

    mov r2, #0
    mov r3, #0

substr_loop_len_s1:
    ldrb r12, [r0, r2]
    cmp r12, #0
    beq substr_loop_len_s2
    add r2, r2, #1
    b substr_loop_len_s1
    
substr_loop_len_s2:
    ldrb r12, [r1, r3]
    cmp r12, #0
    beq substr_loop_match_init
    add r3, r3, #1
    b substr_loop_len_s2

substr_loop_match_init:
    mov r12, #0

substr_loop_match_loop:
    cmp r12, r2
    bge substr_exit_not_found

    str r0, [sp, #4]
    str r1, [sp, #8]
    str r2, [sp, #12]
    str r3, [sp, #16]
    str r12, [sp, #20]

    add r0, r0, r12
    mov r2, r3
    
    bl match_s

    cmp r0, #1
    bne substr_loop_match_continue
    ldr r0, [sp, #20]
    b substr_exit

substr_loop_match_continue:
    ldr r12, [sp, #20]
    ldr r3, [sp, #16]
    ldr r2, [sp, #12]
    ldr r1, [sp, #8]
    ldr r0, [sp, #4]
    add r12, r12, #1
    b substr_loop_match_loop    

substr_exit_not_found:
    mov r0, #-1

substr_exit:

    ldr lr, [sp]
    add sp, sp, #24
    bx lr

match_s:
    sub sp, sp, #8
    str r4, [sp]
    mov r3, #0


match_loop:
    cmp r3, r2
    bge match_loop_exit_true
    ldrb r12, [r0]
    ldrb r4, [r1]
    cmp r12, r4
    beq match_continue
    mov r0, #0
    b match_loop_exit

match_continue:
    add r3, r3, #1
    add r0, r0, #1
    add r1, r1, #1
    b match_loop    

match_loop_exit_true:
    mov r0, #1

match_loop_exit:
    ldr r4, [sp]
    add sp, sp, #8
    bx lr

@ End marker
	add r0, r0, #0
