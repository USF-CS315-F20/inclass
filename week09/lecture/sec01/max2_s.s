.global max2_s

max2_s:
    cmp r0, r1
    bge max2_end
    mov r0, r1
max2_end:
    bx lr

