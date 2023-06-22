# ijc_projekt_i
First project (homework) for the IJC (The C language) course at FIT BUT. I did as best as I knew how and in the end I am happy with how I did it.

Contents:
- project assignment `zadani.txt` (It's in czech, obviously)
- macros and inline functions for bit vectors in `bitset.h` 
   - to use inline functions, the project is compiled with `-DUSE_INLINE`
- implementation of the Sieve of Erastothenes in `erastosthenes.c` using a bit vector
- a program `primes.c` that prints the last ten prime numbers between 1 and 230'000'000
  - run with `make run` 
- a program `steg-decode.c` that prints the message steganographically encoded in `du1-obrazek.ppm` 
  - the message is stored bit by bit on the LSb of the prime bytes (starting with byte 101)
