/*****************
**  Vit Pavlik  **
**   xpavli0a   **
**    251301    **
**              **
**   Created:   **
**  2023-03-17  **
**              **
** Last edited: **
**  2023-03-18  **
*****************/
// Fakulta: FIT VUT
// Vyvíjeno s gcc 10.2.1 na Debian GNU/Linux 11

#include "bitset.h"
#include "primes.h"


int main() {
    bitset_create(pole, N);
    Eratosthenes(pole);

    for (bitset_index_t i = 0; i < N; i++) {
        if (!bitset_getbit(pole, i)) {  // bit 0 - cislo je prvocislo
            printf("%lu\n", i);
        }
    }
}
