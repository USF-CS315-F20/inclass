/* first_s.s - a simple ARM Assebly language program */

.global main

main:
    mov r0, #1
    mov r1, #2
    add r0, r0, r1
    bx lr
