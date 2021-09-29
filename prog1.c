#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


long fibonacci(int n);
float buffon(int r);
void ellipse(int a, int b, int s, char* buf);
void ballDropping(int x, int y, char* buf);

int main(int argc, char* argv[]) {

    char buf[100];
    int status;


    //srand(1234);
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

    //Begin forking children
    pid_t pid;
    pid = fork(); //no clue why but my IDE throws a fit when I do this, but the linux compiler takes it fine and it
                  //seems to work so CLion can just be quiet for now.

    //someone smarter than me could probably do this a better way. I am not that person.

    if (pid < 0) {
        sprintf(buf, "First Fork Failed!\n");
        write(1, buf, strlen(buf));
    } else if (pid == 0) {
        //child process 1 logic
        sprintf(buf, "Fibonacci Process Created\n");
        write(1, buf, strlen(buf));

        sprintf(buf, "   Fibonacci Process Started\n");
        write(1, buf, strlen(buf));

        sprintf(buf, "   Input Number %d\n", n);
        write(1, buf, strlen(buf));

        long fibResult = fibonacci(n);
        sprintf(buf,"   Fibonacci Number f(%d) is %ld\n", n, fibResult);
        write(1, buf, strlen(buf));

        sprintf(buf,"   Fibonacci Process Exits\n");
        write(1, buf, strlen(buf));

    } else {
        //still in main process
        pid = fork(); //reassign because we don't need pid to distinguish processes anymore

        if (pid < 0) {
            sprintf(buf, "Second Fork Failed!\n");
            write(1, buf, strlen(buf));
        } else if (pid == 0) {
            //child process 2 logic
            sprintf(buf, "Buffon's Needle Process Created\n");
            write(1, buf, strlen(buf));

            sprintf(buf, "      Buffon's Needle Process Started\n");
            write(1, buf, strlen(buf));

            sprintf(buf, "      Input Number %d\n", r);
            write(1, buf, strlen(buf));

            float bufResult = buffon(r);
            sprintf(buf, "      Estimated Probability is %0.5f\n", bufResult);
            write(1, buf, strlen(buf));

            sprintf(buf, "      Buffon's Needle Process Exits\n");
            write(1, buf, strlen(buf));

        } else {
            //still in main process
            pid = fork();

            if (pid < 0) {
                sprintf(buf, "Third Fork Failed!\n");
                write(1, buf, strlen(buf));
            } else if (pid == 0) {
                //child process 3 logic
                sprintf(buf, "Ellipse Area Process Created\n");
                write(1, buf, strlen(buf));

                sprintf(buf, "         Ellipse Area Process Started\n");
                write(1, buf, strlen(buf));

                sprintf(buf, "         Total random Number Pairs %d\n", s);
                write(1, buf, strlen(buf));

                sprintf(buf, "         Semi-Major Axis Length %d\n", a);
                write(1, buf, strlen(buf));

                sprintf(buf, "         Semi-Minor Axis Length %d\n", b);
                write(1, buf, strlen(buf));

                ellipse(a, b, s, buf);

                sprintf(buf, "         Ellipse Area Process Exits\n");
                write(1, buf, strlen(buf));

            } else {
                //still in main process
                pid = fork();

                if (pid < 0) {
                    sprintf(buf, "Fourth Fork Failed!\n");
                    write(1, buf, strlen(buf));
                } else if ( pid == 0 ) {
                    //child process 4 logic
                    sprintf(buf, "Pinball Process Created\n");
                    write(1, buf, strlen(buf));

                    sprintf(buf, "Simple Pinball Process Started\n");
                    write(1, buf, strlen(buf));

                    sprintf(buf, "Number of Bins %d\n", x);
                    write(1, buf, strlen(buf));

                    sprintf(buf, "Number of Ball Droppings %d\n");
                    write(1, buf, strlen(buf));

                    ballDropping(x, y, buf);
                } else {
                    //still in main process
                    sprintf(buf, "Main Process Waits\n");
                    write(1, buf, strlen(buf));

                    wait(&status);
                    wait(&status);
                    wait(&status);
                    wait(&status);


                    sprintf(buf, "Main Process Exits\n");
                    write(1, buf, strlen(buf));
                }
            }
        }
    }

    return 0;
}

long fibonacci(int n) {
    if (n == 0) {
        return 0;
    } else if (n == 1) {
        return 1;
    }

    return (fibonacci(n - 1) + fibonacci(n - 2));
}

float buffon(int r) {
    //r = iterations of problem
    const double PI = acos(-1.0); //define PI according to slides
    float d;
    float a;

    int t = 0;

    for (int i = 0; i < r; i++) {
        d = (((float) rand()) / RAND_MAX);
        a = (d * 2 * PI);

        float result = d + sinf(a);
        if (result < 0 || result > 1) {
            t++;
        }
    }

    return (float) t/r;
}

void ellipse(int a, int b, int s, char *buf) {
    //s = iterations of problem
    int t = 0;
    float x;
    float y;
    const double PI = acos(-1.0); // define pi according to slides

    for (int i = 0; i < s; i++) {
        //generate a random point in the rectangle bounded by the x and y axes, and the lines x = a, y = b
        x = (((float) rand()) / RAND_MAX) * a;
        y = (((float) rand())/RAND_MAX) * b;

        float result = powf(x, 2)/pow(a, 2) + powf(y, 2)/pow(b, 2);
        if (result <= 1) {
            t++;
        }
    }

    sprintf(buf, "         Total Hits %d\n", t);
    write(1, buf, strlen(buf));

    float estArea = (((float) t/s) * a * b) * 4;
    sprintf(buf, "         Estimated Area is %2.5f\n", estArea);
    write(1, buf, strlen(buf));

    float actArea = (float) a * b * PI;
    sprintf(buf, "         Actual Area is %2.5f\n", actArea);
    write(1, buf, strlen(buf));
}

void ballDropping(int x, int y, char* buf) {
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

    float percent;
    float *percents = malloc(sizeof(float) * x);
    float max = 0;

    for (int i = 0; i < x; i++) {
        percent = ((float) bins[i] / y) * 100;
        if (percent > max) {
            max = percent;
        }
        percents[i] = percent;
    }

    for (int i = 1; i <= x; i++) {
        sprintf(buf,"%3d-(%7d)-(%5.2f%) | ", i, bins[i-1], percents[i - 1]);
        int numStars = ((float) percents[i -1] / max) * 50;
        for (int j = 0; j < numStars; j++) {
            int startInd = strlen(buf);
            sprintf(&buf[startInd], "*");
        }
        int startInd = strlen(buf);
        sprintf(&buf[startInd], "\n");
        write(1, buf, strlen(buf));
    }

    free(percents);
    free(bins);
}