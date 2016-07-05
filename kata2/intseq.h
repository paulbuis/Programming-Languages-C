/*
 * intseq.h
 */

struct intSeq {
    int length;
    int capacity;
    int* data;
};

extern struct intSeq newIntSeq();

extern void intSeqAdd(struct intSeq* pis, int newValue);

