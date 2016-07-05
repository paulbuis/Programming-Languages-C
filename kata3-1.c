#include <stdio.h>

double factorial(unsigned int n) {
    double result = n;
    while (n > 1) {
        result *= --n;
    }
    return result;
}


int main(int argc, char** argv) {
    printf(" 10!= %20g\n", factorial(10));
    printf(" 20!= %20g\n", factorial(20));
    printf(" 40!= %20g\n", factorial(40));
    printf(" 80!= %20g\n", factorial(80));
    printf("160!= %20g\n", factorial(160));
    printf("200!= %20g\n", factorial(200));
    return 0;
}
