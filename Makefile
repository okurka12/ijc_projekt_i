# Vit Pavlik
# login: xpavli0a
# osobni cislo: 251301
# fakulta: FIT VUT
# Created:  2022-03-17
# Modified: 2022-03-18
# vyvijeno s GNU Make 4.3 (Built for x86_64-pc-linux-gnu)

CC=gcc
CFLAGS=-m32 -O0 -std=c11 -Wall -Wextra -pedantic -g
#CFLAGS=-std=c11 -Wall -Wextra -pedantic -g

all: primes primes-i

# primes (link only)
primes: primes.o eratosthenes.o error.o
	$(CC) $(CFLAGS) -o primes primes.o eratosthenes.o error.o 

# primes-i (link only)
primes-i: primes-i.o eratosthenes.o error.o
	$(CC) $(CFLAGS) -o primes-i primes-i.o eratosthenes.o error.o 

# compile primes.c
primes.o: primes.h primes.c bitset.h
	$(CC) $(CFLAGS) -c -o primes.o primes.c

# compile primes.c
primes-i.o: primes.h primes.c bitset.h 
	$(CC) $(CFLAGS) -c -o primes-i.o -DUSE_INLINE primes.c

# compile eratosthenes.c
eratosthenes.o: eratosthenes.c bitset.h primes.h.
	$(CC) $(CFLAGS) -c -o eratosthenes.o eratosthenes.c

# compile error.c
error.o: error.h error.c
	$(CC) $(CFLAGS) -c -o error.o error.c

clean:
	rm -f *.o *.elf primes primes-i

# jen pro ucely vyvoje
zkouska: error.o
	$(CC) $(CFLAGS) -o zkouska.elf error.o zkouska.c