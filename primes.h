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

#ifndef _PRIMES_H
#define _PRIMES_H

#define N 230000000

/* Provede algoritmus na bitovém poli o velikosti N 
(N definováno v primes.h) */
void Eratosthenes(bitset_t pole);

#endif  // ndef _PRIMES_H