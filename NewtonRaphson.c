#include <stdio.h>
#include <math.h>
#define EPSILON 1e-6


double h(double x) {
    return pow(x, 3) - 4 * pow(x, 2) + 3 * x - 6;
}

double h_prime(double x) {
    return 3 * pow(x, 2) - 8 * x + 3;
}

double f(double x) {
    return 2 * pow(x, 3) - 4 * pow(x, 2) + 3 * x - 6;
}

double f_prime(double x) {
    return 6 * pow(x, 2) - 8 * x + 3;
}


double newton_raphson(double (*fp)(double), double (*fp_prime)(double)) {
    double x = 1.5;
    while (fabs(fp(x)) > EPSILON){
        x = x - fp(x) / fp_prime(x);
    }
    return x;
}

int main() {
    printf("%g\n", newton_raphson(f, f_prime));
    printf("%g\n", newton_raphson(h, h_prime));
    return 0;
}
