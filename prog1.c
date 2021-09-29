#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

long fibonacci(int n);
float buffon(int r);
float ellipse(int a, int b, int s);
void ballDropping(int x, int y);

int main(int argc, char* argv[]) {

    char buf[100];

    sprintf(buf, "Main Process Started\n");
    write(1, buf, strlen(buf));

    if (argc < 8 ) {
        sprintf(buf, "Not enough command line arguments!\n");
        write(1, buf, strlen(buf));
        sprintf(buf, "Usage: ./prog1 n r a b s x y\n");
        write(1, buf, strlen(buf));
        return 1;
    }

    long n = atol(argv[1]);
    int r = atoi(argv[2]);
    int a = atoi(argv[3]);
    int b = atoi(argv[4]);
    int s = atoi(argv[5]);
    int x = atoi(argv[6]);
    int y = atoi(argv[7]);

    sprintf(buf, "Fibonacci Input            = %ld\n", n);
    write(1, buf, strlen(buf));
    sprintf(buf, "Buffon's Needle Iterations = %d\n", r);
    write(1, buf, strlen(buf));
    sprintf(buf, "Total random Number Pairs  = %d\n", s);
    write(1, buf, strlen(buf));
    sprintf(buf, "Semi-Major Axis Length     = %d\n", a);
    write(1, buf, strlen(buf));
    sprintf(buf, "Semi-Minor Axis Length     = %d\n", b);
    write(1, buf, strlen(buf));
    sprintf(buf, "Number of Bins             = %d\n", x);
    write(1, buf, strlen(buf));
    sprintf(buf, "Number of Ball Droppings   = %d\n", y);
    write(1, buf, strlen(buf));


    sprintf(buf, "Main Process Exits\n");
    write(1, buf, strlen(buf));
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
        d = ((float) rand()) / RAND_MAX;
        a = d * 2 * PI;

        float result = d + sinf(a);
        if (result < 0 || result > 1) {
            t++;
        }
    }

    return t/r;
}

float ellipse(int a, int b, int s) {
    //s = iterations of problem
    int t = 0;
    float x;
    float y;

    for (int i = 0; i < s; i++) {
        //generate a random point in the rectangle bounded by the x and y axes, and the lines x = a, y = b
        x = (((float) rand()) / RAND_MAX) * a;
        y = (((float) rand())/RAND_MAX) * b;

        float result = powf(x, 2)/pow(a, 2) + powf(y, 2)/pow(b, 2);
        if (result <= 1) {
            t++;
        }
    }

    return ((t/s) * a * b) * 4;
}

void ballDropping(int x, int y) {
    int *bins = (int*) calloc(x, sizeof(int));

    double bin;
    int roll;

    for (int i = 0; i < y; i++) {
        bin = (x / 2) + 0.5; //place ball above the starting peg
        for (int j = 0; j < x - 1; j++) {
            roll = rand() % 2;
            if(roll) {
                bin = bin + 0.5;
            } else {
                bin = bin - 0.5;
            }
        }
        bins[(int)bin - 1]++;
    }

    free(bins);
}