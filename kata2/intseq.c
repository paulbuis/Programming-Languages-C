/*
 * intseq.c
 */
#include <stdlib.h>
#include "intseq.h"

struct intSeq newIntSeq() {
    struct intSeq seq;
    seq.length = 0;
    seq.capacity = 4;
    seq.data = (int*)malloc(4*sizeof(int));
    return seq;
}

void intSeqAdd(struct intSeq* pis, int newValue) {
    int* newData;
    int index;
    if (pis->length == pis->capacity - 1) {
        newData = (int*)malloc(2 * pis->capacity * sizeof(int));
        pis->capacity *= 2;
        for (index = 0; index < pis->length; index++) {
            newData[index] = pis->data[index];
        }
        free(pis->data);
        pis->data = newData;
    }

    pis->data[pis->length++] = newValue;
}

