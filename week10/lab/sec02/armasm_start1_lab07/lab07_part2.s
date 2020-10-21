@ r0 and r1 are memory addresses whose contents we will swap
swap:
    ldr r2, [r0]
    ldr r3, [r1]
    str r2, [r1]
    str r3, [r0]
    bx lr
