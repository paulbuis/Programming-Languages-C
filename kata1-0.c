#include <stdio.h>
#include <time.h>

double average(int, int, int);
int read(int*, int*, int*);

int main(int argc, char** argv) {
    int a, b, c;
    if (scanf("%d %d %d", &a, &b, &c) == 3) {
        printf("Average: %f\n", average(a, b, c));
    }
    else {
        printf("Error reading input values");
    }
    return 0;
}

double average(int x, int y, int z) {
    return (x+y+z)/3.0;
}

int read(int *px, int *py, int* pz) {
    int scanCount = scanf("%d", px);
    if (scanCount != 1) return 1;
    scanCount = scanf("%d", py);
    if (scanCount != 1) return 2;
    scanCount = scanf("%d", pz);
    if (scanCount != 1) return 3;
    return 0;
}
