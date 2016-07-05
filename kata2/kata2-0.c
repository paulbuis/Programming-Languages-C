#include <stdio.h>
#include "intseq.h"

struct intSeq readInts();
double average(struct intSeq);

int main(int argc, char** argv) {
    struct intSeq seq = readInts();

    double a = average(seq);
    printf("Average: %f\n", average(seq));

    return 0;
}

struct intSeq readInts() {
    struct intSeq seq = newIntSeq();
    int count = 0;
    int value;
    char buffer[128];
    while (fgets(buffer, 128, stdin) != NULL) {
        if (sscanf(buffer, "%d", &value) != 1) {
            break;
        }
        intSeqAdd(&seq, value);
    }
    return seq;
}

double average(struct intSeq seq) {
    int index;
    int sum = 0;
    for (index = 0; index < seq.length; index++) {
        sum += seq.data[index];
    }
    return ((double)sum)/seq.length;
}


