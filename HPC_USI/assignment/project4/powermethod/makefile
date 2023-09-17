CC=mpicc
CFLAGS=-O3 -lm

all: powermethod

powermethod: powermethod.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f powermethod
