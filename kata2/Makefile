CC=gcc

kata2-0: kata2-0.o intseq.o
	$(CC) $(CFLAGS) kata2-0.o intseq.o -o kata2-0

intseq.o: intseq.c intseq.h
kata2-0.o: kata2-0.c intseq.h

clean:
	rm -f kata2-0 a.out *.o
