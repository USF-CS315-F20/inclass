.global count_s
count_s:
    mov r1, r0
    mov r0, #0
    mov r2, #0
count_loop:
    cmp r2, r1
    bgt count_done
    add r0, r0, r2
    add r2, r2, #1
    b count_loop
count_done:
    bx lr
