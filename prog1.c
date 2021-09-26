#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char* argv[]) {
    printf("Main Process Started\n");

    if (argc < 8 ) {
        printf("Not enough command line arguments!\n");
        printf("Usage: ./prog1 n r a b s x y\n");
        return 1;
    }

    long n = atol(argv[1]);
    int r = atoi(argv[2]);
    int a = atoi(argv[3]);
    int b = atoi(argv[4]);
    long s = atoi(argv[5]);
    int x = atoi(argv[6]);
    int y = atoi(argv[7]);

    printf("Fibonacci Input            = %ld", n);
    printf("Buffon's Needle Iterations = %d", r);
    printf("Total random Number Pairs  = %ld", s);
    printf("Semi-Major Axis Length     = %d", a);
    printf("Semi-Minor Axis Length     = %d", b);
    printf("Number of Bins             = %d", x);
    printf("Number of Ball Droppings   = %d", y);

    return 0;
}

long fibonacci(int n) {
    if (n < 2) {
        return 1;
    }

    return fibonacci(n - 1) + fibonacci(n - 2);
}

float buffon(int r) {
    //r = iterations of problem
    const double PI = acos(-1.0); //define PI according to slides
    float d;
    float a;

    int t = 0;

    for (int i = 0; i < r; i++) {
        d = (float rand())/RAND_MAX;
        a = d * 2 * PI;

        float result = d + sinf(a);
        if (result < 0 || result > 1) {
            t++;
        }
    }

    return t/r;
}
