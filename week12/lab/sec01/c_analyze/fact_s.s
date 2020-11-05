.global fact_s

fact_s:
    sub sp, sp, #8
    str lr, [sp]

    cmp r0, #0
    bne fact_rec

    mov r0, #1

    b fact_end

fact_rec: 
    
    str r0, [sp, #4]
    sub r0, r0, #1

    bl fact_s

    ldr r1, [sp, #4]
    mul r0, r1, r0
                 
fact_end:
    ldr lr, [sp]
    add sp, sp, #8
    bx lr

@ End marker
	add r0, r0, #0
