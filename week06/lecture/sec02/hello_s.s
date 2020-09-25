/* hello_s.s - hello world in ARM assembly language */

/* External labels (functions) */
.global printf

/* .data designed data definitons, like C globals */
.data

/* The greeting label designates an address to the following string. */
/* The .asciz directive means the string is null terminated. */
greeting:
 .asciz "Hello, ARM!\n"   

/* Tell the assembler the following section contains code. */
.text
 
.global main
main:
    /* Make space on the stack */
    sub sp, sp, #8
    /* Put the value in lr (link register) onto the stack */
    str lr, [sp]

    /* Put the address of greeting into register r0 */
    ldr r0, =greeting

    /* Call printf() from C Library */
    bl printf

    /* Restore lr from stack so that the bx lr below returns to the */
    /* right location. */
    
    ldr lr, [sp]

    /* Deallocate space on the stack */
    add sp, sp, #8
    bx lr
    
