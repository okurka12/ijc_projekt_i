/*****************
**  Vit Pavlik  **
**   xpavli0a   **
**    251301    **
**              **
**   Created:   **
**  2023-02-24  **
**              **
** Last edited: **
**  2023-03-18  **
*****************/
// Fakulta: FIT VUT
// Vyvíjeno s gcc 10.2.1 na Debian GNU/Linux 11

/**
 * řádky s komentářem `xxx` jsou problematické z hlediska přetypování
 * (různé konstanty které by zabránily předefinování UL na jiný typ)
*/

#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "error.h"

#ifndef _BITSET_H

typedef unsigned long bset_ele;  // bitset element - unsigned long
typedef bset_ele bitset_index_t;
typedef bset_ele *bitset_t;

/* určí, v kolikátém UL je n-tý bit (vstup i výstup počítán od nuly) */
#define bity(n) n / (sizeof(unsigned long) * 8)


/* Velikost unsigned longu v bitech */
#define SULB (sizeof(unsigned long) * 8)


/* definuje a nuluje proměnnou jmeno_pole */
#define bitset_create(jmeno, velikost) \
    static_assert(velikost > 0 && velikost <= ULONG_MAX, /* xxx */ \
                  "bitset_create: Nespravna velikost pole " \
                  "(parametr `velikost` je pocet bitu."); \
    bset_ele jmeno[bity(velikost) + 2] = {0}; \
    jmeno[0] = velikost;

#ifndef USE_INLINE

/* definuje proměnnou jmeno_pole tak, aby byla kompatibilní s polem
   vytvořeným pomocí bitset_create, ale pole je alokováno dynamicky */
#define bitset_alloc(jmeno, velikost) \
    assert(velikost > 0 && velikost <= ULONG_MAX); /* xxx */ \
    bset_ele *jmeno = malloc((bity(velikost) + 2) * sizeof(bset_ele)); \
    if (jmeno == NULL) { \
        error_exit("bitset_alloc: Chyba alokace paměti\n"); \
    } \
    memset(jmeno, 0, sizeof(unsigned long) * (bity(velikost) + 2)); \
    jmeno[0] = velikost


/* uvolní paměť dynamicky (bitset_alloc) alokovaného pole */
#define bitset_free(jmeno) free(jmeno)


/* vrátí deklarovanou velikost pole v bitech */
#define bitset_size(jmeno) jmeno[0]


/* nastaví zadaný bit v poli na hodnotu zadanou výrazem
   (nulový výraz == bit 0, nenulový výraz == bit 1) */
#define bitset_setbit(jmeno, index, vyraz) \
    if (index >= jmeno[0]) { \
        error_exit("bitset_setbit: Index %lu mimo rozsah 0..%lu\n", \
                   (bset_ele)index, jmeno[0] - 1); \
    } \
\
    if (vyraz) { \
        /*   [index v poli UL] |=  (maska <<  (index v konkrétním UL)) */ \
        jmeno[bity(index) + 1] |=  (1UL   <<  (index % SULB)); \
    } else { \
        jmeno[bity(index) + 1] &= ~(1UL   <<  (index % SULB)); \
    }


/* získá hodnotu zadaného bitu, vrací hodnotu 0 nebo 1 */
#define bitset_getbit(jmeno, index) \
    ( \
    (index >= jmeno[0]) ? \
        ( \
            error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu\n", \
                       (bset_ele)index, jmeno[0] - 1),  /* operator carka */ \
            0LU \
        ) \
    : \
        (((jmeno[bity(index) + 1]) >> (index % SULB)) & 1UL) \
    )  // tyto uplne nejvic vnejsi zavorky tady jsou proto aby se pred
       // cely bitset_getbit dal dat vykricnik protoze to jinak akorat zneguje
       // podminku ternarniho operatoru coz je veliky headache

#else  // ndef USE_INLINE

/* definuje proměnnou jmeno_pole tak, aby byla kompatibilní s polem
   vytvořeným pomocí bitset_create, ale pole je alokováno dynamicky */
#define bitset_alloc(jmeno, velikost) bitset_t jmeno = _bitset_alloc(velikost)


static inline bset_ele* _bitset_alloc(bset_ele velikost) {
    assert(velikost > 0 && velikost <= ULONG_MAX);
    bset_ele *output;
    if ((output = malloc((bity(velikost) + 2) * sizeof(bset_ele))) == NULL) {
        error_exit("bitset_alloc: Chyba alokace paměti.\n");
    }
    return output;
}


/* uvolní paměť dynamicky (bitset_alloc) alokovaného pole */
static inline void bitset_free(bset_ele *jmeno) {
    free(jmeno);
}


/* vrátí deklarovanou velikost pole v bitech */
static inline bset_ele bitset_size(bitset_t jmeno) {
    return jmeno[0];
}


/* nastaví zadaný bit v poli na hodnotu zadanou výrazem
   (nulový výraz == bit 0, nenulový výraz == bit 1) */
static inline void bitset_setbit(bitset_t jmeno, bset_ele index, int vyraz) {
    if (index >= jmeno[0]) {
        error_exit("bitset_setbit: Index %lu mimo rozsah 0..%lu\n",
                   (unsigned long)index, jmeno[0] - 1);
    }

    if (vyraz) {
        /*   [index v poli UL] |=  (maska <<  (index v konkrétním UL)) */
        jmeno[bity(index) + 1] |=  (1UL   <<  (index % SULB));
    } else {
        jmeno[bity(index) + 1] &= ~(1UL   <<  (index % SULB));
    }
}


/* získá hodnotu zadaného bitu, vrací hodnotu 0 nebo 1 */
static inline bset_ele bitset_getbit(bitset_t jmeno, bset_ele index) {
    if (index >= jmeno[0]) {
        error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu\n",
                   index, jmeno[0] - 1);
    }
    return ((jmeno[bity(index) + 1]) >> (index % SULB)) & 1UL;
}

#endif  // ndef USE_INLINE
#endif  // ndef _BITSET_H