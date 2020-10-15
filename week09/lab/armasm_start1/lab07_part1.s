@ x is r0, a is r1, b is r2, c is r3
quadratic_s:
    mul r2, r2, r0      @ bx
    mul r0, r0, r0      @ x^2
    mul r1, r1, r0      @ ax^2
    add r0, r1, r2      @ ax^2 + bx
    add r0, r0, r3      @ ax^2 + bx + c
    bx lr
