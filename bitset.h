/*****************
**  Vit Pavlik  **
**   xpavli0a   **
**    251301    **
**              **
**   Created:   **
**  2023-02-24  **
**              **
** Last edited: **
**  2023-03-01  **
*****************/

#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "error.h"


typedef unsigned long bitset_index_t;
typedef unsigned long bitset_t;

/* určí, kolik je potřeba unsigned longů na n bitů 
   (včetně prvního unsigned longu pro velikost) */
#define bity(n) n / sizeof(unsigned long) + 2

/* Velikost unsigned longu v bitech */
#define SULB sizeof(unsigned long) * 8


#ifndef USE_INLINE


/* definuje a nuluje proměnnou jmeno_pole */
#define bitset_create(jmeno, velikost) \
    bitset_t jmeno[bity(velikost)] = {0}; \
    jmeno[0] = velikost; \
    static_assert(velikost > 0 && bity(velikost) <= ULONG_MAX, \
                  "bitset_create: Nesprávná velikost pole " \
                  "(parametr `velikost` je počet bitů.");


/* definuje proměnnou jmeno_pole tak, aby byla kompatibilní s polem
   vytvořeným pomocí bitset_create, ale pole je alokováno dynamicky */
#define bitset_alloc(jmeno, velikost) \
    jmeno = malloc(bity(velikost) * sizeof(unsigned long)); \
    if (jmeno == NULL) { \
        error_exit("bitset_alloc: Chyba alokace paměti\n"); \
    } \
    memset(jmeno, 0, sizeof(unsigned long) * bity(velikost)); \
    jmeno[0] = velikost; \
    assert(velikost > 0 && bity(velikost) <= ULONG_MAX)


/* uvolní paměť dynamicky (bitset_alloc) alokovaného pole */
#define bitset_free(jmeno) free(jmeno)


/* vrátí deklarovanou velikost pole v bitech */
#define bitset_size(jmeno) jmeno[0]


/* nastaví zadaný bit v poli na hodnotu zadanou výrazem
   (nulový výraz == bit 0, nenulový výraz == bit 1) */
#define bitset_setbit(jmeno, index, vyraz) \
    if (index > jmeno[0] - 1) { \
        error_exit("bitset_setbit: Index %lu mimo rozsah 0..%lu\n", \
                   (unsigned long)index, jmeno[0]); \
    } \
\
    if (vyraz) { \
        /*   [index v poli UL] |=  (maska <<  (index v konkrétním UL)) */ \
        jmeno[bity(index) - 1] |=  (1UL   <<  (index % SULB)); \
    } \
    else { \
        jmeno[bity(index) - 1] &= ~(1UL   <<  (index % SULB)); \
    }


// BITSET_GETBIT NENI DODELANE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#define bitset_getbit(jmeno, index) \
    if (index > jmeno[0] - 1) { \
        error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu\n", \
                   (unsigned long)index, jmeno[0]) \
    } \
    /** muj problem tady je ze toto je makro na nejaky vyraz ktery vrati  \
     * hodnotu nejakeho bitu ale jak mam uprostred tohodle vyrazu         \
     * udelat ten bound check aby                                         \
     * to byl stale platny vyraz 🤔🤔🤔🤔🤔🤔🤔🤔🤔🤔🤔🤔 */


// TODO: use inline !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#endif
