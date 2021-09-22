#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    printf("Hello, World!\n");
    return 0;
}

long fibonacci(int n) {
    if (n < 2) {
        return 1;
    }

    return fibonacci(n - 1) + fibonacci(n - 2);
}
