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

#include <math.h>

#include "bitset.h"
#include "primes.h"


void Eratosthenes(bitset_t pole) {
    
    // suppress warning: "expression always false" when using macros
    const bitset_index_t nula = 0;
    
    bitset_setbit(pole, nula, 1);
    bitset_setbit(pole, 1, 1);
    bitset_index_t i = 2;
    
    // const bitset_index_t sqrtN = ceil(sqrt(N))  // optimalizace 1
    // while (i <= sqrtN) {
    // while (i <= (bitset_index_t)ceil(sqrt(N))) {  // optimalizace 2
    while (i <= sqrt(N)) {
        // odstranit ze sita nasobky i
        for (bitset_index_t j = 2 * i; j < N; j += i) {
            bitset_setbit(pole, j, 1);
        }

        // nasobky i odstraneny, budeme pokracovat s i + 1
        i++;

        // pokud i + 1 neni prvocislo, pricitat i dokud nebude prvocislo
        while (bitset_getbit(pole, i) && i <= sqrt(N)) {
            i++;
        }
    }
}
