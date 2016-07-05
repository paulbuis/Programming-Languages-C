CC=gcc
CCFLAGS=-O3

all: kata2-0 kata2-1

kata2-0: kata2-0.o intseq.o
	$(CC) $(CCFLAGS) kata2-0.o intseq.o -o kata2-0

kata2-1: kata2-1.o intseq.o
	$(CC) $(CCFLAGS) kata2-1.o intseq.o -o kata2-1

intseq.o: intseq.c intseq.h
kata2-0.o: kata2-0.c intseq.h
kata2-1.o: kata2-1.c intseq.h

clean:
	rm -f kata2-0 kata2-1 a.out *.o
