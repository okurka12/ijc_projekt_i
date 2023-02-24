/*****************
**  Vit Pavlik  **
**   xpavli0a   **
**    251301    **
**              **
**   Created:   **
**  2023-02-24  **
**              **
** Last edited: **
**  2023-02-24  **
*****************/

#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>


typedef unsigned long bitset_index_t;
typedef unsigned long * bitset_t;

/* určí, kolik je potřeba unsigned longů na n bitů */
#define bity(n) n / sizeof(unsigned long) + 2


#ifndef USE_INLINE

/* definuje a nuluje proměnnou jmeno_pole */
#define bitset_create(jmeno, velikost) \
    bitset_t jmeno[bity(velikost)] = {0}; \
    jmeno[0] = velikost; \
    static_assert(velikost > 0 && bity(velikost) <= ULONG_MAX)


/* definuje proměnnou jmeno_pole tak, aby byla kompatibilní s polem
   vytvořeným pomocí bitset_create, ale pole je alokováno dynamicky */
#define bitset_alloc(jmeno, velikost) \
    jmeno = malloc(bity(velikost) * sizeof(unsigned long)); \
    if (jmeno == NULL) { \
        fprintf(stderr, "bitset_alloc: Chyba alokace paměti\n"); \
        exit(1); \
    } \
    memset(jmeno, 0, sizeof(unsigned long) * bity(velikost)); \
    jmeno[0] = velikost; \
    assert(velikost > 0 && bity(velikost) <= ULONG_MAX)


/* uvolní paměť dynamicky (bitset_alloc) alokovaného pole */
#define bitset_free(jmeno) free(jmeno)


/* vrátí deklarovanou velikost pole v bitech (uloženou v poli) */
#define bitset_size(jmeno) jmeno[0]


/* nastaví zadaný bit v poli na hodnotu zadanou výrazem
   (nulový výraz == bit 0, nenulový výraz == bit 1) */
#define bitset_setbit(jmeno, index, vyraz) 

// tady uz si nejsem jisty jak to udelat tak ja to do priste vymyslim a budu ted
// pokracovat rozhranim error.h protoze s jeho pomoci mame kontrolovat meze
// tady v tom xd vis co

// TODO: use inline !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#endif
