#include <stdio.h>

long unsigned fib(unsigned int n) {
    long unsigned a = 0;
    long unsigned b = 1;
    long unsigned t;
    unsigned int i;
    if (n <= 1) {
        return n;
    }
    for (i=0; i<n; i++) {
	t = a;
        a = b;
	b += t;
    }
   
    return a;
}


int main(int argc, char** argv) {
    printf("fib( 0)= %20lu\n", fib(0));
    printf("fib( 1)= %20lu\n", fib(1));
    printf("fib( 2)= %20lu\n", fib(2));
    printf("fib( 3)= %20lu\n", fib(3));
    printf("fib( 4)= %20lu\n", fib(4));
    printf("fib( 5)= %20lu\n", fib(5));
    printf("fib(10)= %20lu\n", fib(10));
    printf("fib(30)= %20lu\n", fib(30));
    printf("fib(40)= %20lu\n", fib(40));
    printf("fib(50)= %20lu\n", fib(50));

    printf("fib(90)= %20lu\n", fib(90));
    printf("fib(93)= %20lu\n", fib(93));
    printf("fib(94)= %20lu\n", fib(94));

   
    return 0;
}
