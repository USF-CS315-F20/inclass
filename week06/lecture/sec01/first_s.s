/* first_s.s - a simple ARM assembly language program */

/* To see the result of running the program, do the following:

$ ./first_s
$ echo $?
3

*/

/* We need to make the "main" label global so it can be seen and */
/* used by other object files (C or Assembly code). */
.global main

/* Labels designate the address of instruction in memory. */
/* Here, main is a label that designates the address of the following */
/* mov r0, #1 instuction */
main:
    /* The mov instruction puts the second operand into the register */
    /* denoted in the first operand. So, we have r0 = 1. */
    mov r0, #1
    mov r1, #2
    /* The add instruction puts the result of adding the values in the */
    /* registers denoted in the second and third operands. r0 = r0 + r1. */
    add r0, r0, r1

    /* Think of this as equivalent to the "return" statement in C. */
    bx lr
