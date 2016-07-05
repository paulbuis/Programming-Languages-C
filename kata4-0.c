#include <stdio.h>

long unsigned fib(unsigned int n) {
    if (n <= 1) {
        return n;
    }
    return fib(n-1) + fib(n-2);
}


int main(int argc, char** argv) {
    printf("fib( 0)= %12lu\n", fib(0));
    printf("fib( 1)= %12lu\n", fib(1));
    printf("fib( 2)= %12lu\n", fib(2));
    printf("fib( 3)= %12lu\n", fib(3));
    printf("fib( 4)= %12lu\n", fib(4));
    printf("fib( 5)= %12lu\n", fib(5));
    printf("fib(10)= %12lu\n", fib(10));
    printf("fib(30)= %12lu\n", fib(30));
    printf("fib(40)= %12lu\n", fib(40));
    printf("fib(50)= %12lu\n", fib(50));
    return 0;
}
