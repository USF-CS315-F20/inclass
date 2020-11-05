.global sum_array_s

sum_array_s:
    mov r2, #0
    mov r3, #0

sum_array_loop:
    cmp r3, r1
    bge sum_array_loop_exit
    ldr r12, [r0]
    add r2, r2, r12
    add r0, r0, #4
    add r3, r3, #1
    b sum_array_loop

sum_array_loop_exit:    
    mov r0, r2
    bx lr
    
@ End marker
	add r0, r0, #0
