//
// Created by Jade on 29-Sep-21.
//
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <unistd.h>


int main(int argc, char* argv[]) {
    char buf[100];

    if (argc < 3) {
        printf("Not enough cmd line arguments");
    }

    int x = atoi(argv[1]);
    int y = atoi(argv[2]);

    sprintf(buf,"Testing Ball Dropping Method\n");
    write(1, buf, strlen(buf));

    sprintf(buf, "Number of Bins %d\n", x);
    sprintf(buf, "Number of Ball Droppings %d\n", y);

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
    for (int i = 1; i <= x; i++) {
        percent = ((float) bins[i-1] / y) * 100;
        printf("%3d-(%7d)-(%5.2f%)\n", i, bins[i-1], percent);
    }

    free(bins);
}