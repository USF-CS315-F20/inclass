/* Compute the quadratic equation:
 *
 * r = a(x^2) + bx + c
 */
 
int quadratic_c(int x, int a, int b, int c) {
    int r;

    r = (a * x * x) + (b * x) + c;

    return r;
}
