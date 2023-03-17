CC=gcc
CFLAGS=-m32 -O0 -std=c11 -Wall -Wextra -pedantic -g

all: sll_main

error.o: error.h
	$(CC) $(CFLAGS) -c -o error.o error.c

clean:
	rm *.o *.elf

zkouska: error.o
	$(CC) $(CFLAGS) -o zkouska.elf error.o zkouska.c