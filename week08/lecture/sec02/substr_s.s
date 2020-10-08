/* substr_s - find substring in assembly */

.global substr_s
.global match_s

/*
 * r0 - char *s1
 * r1 - char *s2
 * r2 - int len2
 *
 * r3 - int i
 */
match_s:
    sub sp, sp, #8
    str r4, [sp]    
    mov r3, #0

match_loop:
    cmp r3, r2
    bge match_end_true
    ldrb r12, [r0, r3]
    ldrb r4, [r1, r3]
    cmp r12, r4       /* s1[i] != s2[i] */
    beq match_loop_continue
    mov r0, #0
    b match_exit
    
match_loop_continue:
    add r3, r3, #1
    b match_loop    

match_end_true:
    mov r0, #1

match_exit:
    ldr r4, [sp]
    add sp, sp, #8
    bx lr


/*
 * r0 - char *s1
 * r1 - char *s2
 *
 * r2 - int len1
 * r3 - int len2
 */
substr_s:
    sub sp, sp, #24
    str lr, [sp, #0]
    mov r2, #0
    mov r3, #0

substr_s1_len_loop:
    ldrb r12, [r0, r2]  /* s1[len1] */
    cmp r12, #0
    beq substr_s2_len_loop
    add r2, r2, #1
    b substr_s1_len_loop
    
substr_s2_len_loop:
    ldrb r12, [r1, r3]  /* s2[len2] */
    cmp r12, #0
    beq substr_match_init
    add r3, r3, #1
    b substr_s1_len_loop

/* r12 - int i */
substr_match_init:
    mov r12, #0

substr_match_loop:
    cmp r12, r2
    bge substr_match_not_found

    str r0, [sp, #4]
    str r1, [sp, #8]
    str r2, [sp, #12]
    str r3, [sp, #16]
    str r12, [sp, #20]

    /* r0 = r0 + r12 */
    add r0, r0, r12
    /* r1 - already set */
    /* r2 */
    mov r2, r3
        
    bl match_s
    /* r0 */
    cmp r0, #1
    bne substr_match_loop_continue
    ldr r0, [sp, #20]   /* r0 = i */
    b substr_exit
    
substr_match_loop_continue:
    ldr r12, [sp, #20]
    ldr r3, [sp, #16]
    ldr r2, [sp, #12]
    ldr r1, [sp, #8]
    ldr r0, [sp, #4]
    add r12, r12, #1
    b substr_match_loop

substr_match_not_found:
    mov r0, #-1

substr_exit:
    ldr lr, [sp, #0]
    add sp, sp, #8
    bx lr
