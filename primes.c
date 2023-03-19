/*****************
**  Vit Pavlik  **
**   xpavli0a   **
**    251301    **
**              **
**   Created:   **
**  2023-03-17  **
**              **
** Last edited: **
**  2023-03-19  **
*****************/
// Fakulta: FIT VUT
// Vyvíjeno s gcc 10.2.1 na Debian GNU/Linux 11

#include "bitset.h"
#include "eratosthenes.h"

#include <stdio.h>
#include <string.h>
#include <time.h>

#define LNUM 10  // number of lines to be printed
#define N 230000000


int main() {
    bitset_create(pole, N);
    double start = clock();
    Eratosthenes(pole, N);
    fprintf(stderr, "Time=%.3g\n", (double)(clock()-start)/CLOCKS_PER_SEC);

    // pole pro poslednich LNUM prvocisel
    bitset_index_t primes[LNUM] = {0};
    
    // aby se nemuselo rolovat vsech LNUM polozek v poli, 
    // tak bude klouzavy zacatek
    unsigned int idx = 0;
    
    // iterace pres bitove pole aby se naslo poslednich LNUM prvocisel
    for (bitset_index_t i = 0; i < N; i++) {
        if (!bitset_getbit(pole, i)) {  // bit 0 - cislo je prvocislo
            primes[idx % LNUM] = i;
            idx++;
        }
    }
    idx = idx % LNUM;
    for (unsigned int i = idx; i < LNUM + idx; i++) {
        printf("%lu\n", primes[i % LNUM]);
    }
}
