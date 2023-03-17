/*****************
**  Vit Pavlik  **
**   xpavli0a   **
**    251301    **
**              **
**   Created:   **
**  2023-02-24  **
**              **
** Last edited: **
**  2023-03-17  **
*****************/

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

typedef unsigned long bitset_index_t;
typedef unsigned long bitset_t;

/* určí, v kolikátém UL je n-tý bit (vstup i výstup počítán od nuly) */
#define bity(n) n / (sizeof(unsigned long) * 8)


/* Velikost unsigned longu v bitech */
#define SULB sizeof(unsigned long) * 8


/* definuje a nuluje proměnnou jmeno_pole */
#define bitset_create(jmeno, velikost) \
    static_assert(velikost > 0 && velikost <= ULONG_MAX, /* xxx */ \
                  "bitset_create: Nespravna velikost pole " \
                  "(parametr `velikost` je pocet bitu."); \
    bitset_t jmeno[bity(velikost) + 2] = {0}; \
    jmeno[0] = velikost;

#ifndef USE_INLINE

/* definuje proměnnou jmeno_pole tak, aby byla kompatibilní s polem
   vytvořeným pomocí bitset_create, ale pole je alokováno dynamicky */
#define bitset_alloc(jmeno, velikost) \
    assert(velikost > 0 && velikost <= ULONG_MAX); /* xxx */ \
    bitset_t *jmeno = malloc((bity(velikost) + 2) * sizeof(bitset_t)); \
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
    if (index > jmeno[0] - 1) { \
        error_exit("bitset_setbit: Index %lu mimo rozsah 0..%lu\n", \
                   (bitset_t)index, jmeno[0]); \
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
    (index > jmeno[0] - 1) ? \
        ( \
            error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu\n", \
                       (bitset_t)index, jmeno[0]),  /* operator carka */ \
            0 \
        ) \
    : \
        (((jmeno[bity(index) + 1]) >> (index % SULB)) & 1UL) 
    /** 
     * Haha hadejte co vite jak jsem se tady minule rozciloval jak jsem
     * hodinu se snazili prijit na OPERATOR CARKA tak on to
     * dr Peringer za dva tydny uplne vsem zadarmo vyzradil na prednasce :)
     * 
     * me to uplne nastvalo ze proc jim radis bro at si na to prijdou sami
     * jako ja
     * */

#else  // ndef USE_INLINE

/* definuje proměnnou jmeno_pole tak, aby byla kompatibilní s polem
   vytvořeným pomocí bitset_create, ale pole je alokováno dynamicky */
#define bitset_alloc(jmeno, velikost) bitset_t *jmeno = _bitset_alloc(velikost)


static inline bitset_t* _bitset_alloc(bitset_t velikost) {
    assert(velikost > 0 && velikost <= ULONG_MAX);
    bitset_t *output;
    if ((output = malloc(bity(velikost) + 2)) == NULL) {
        error_exit("bitset_alloc: Chyba alokace paměti.\n");
    }
    return output;
}


/* uvolní paměť dynamicky (bitset_alloc) alokovaného pole */
static inline void bitset_free(bitset_t *jmeno) {
    free(jmeno);
}


/* vrátí deklarovanou velikost pole v bitech */
static inline bitset_t bitset_size(bitset_t jmeno[]) {
    return jmeno[0];
}


/* nastaví zadaný bit v poli na hodnotu zadanou výrazem
   (nulový výraz == bit 0, nenulový výraz == bit 1) */
static inline void bitset_setbit(bitset_t jmeno[], bitset_t index, int vyraz) {
    if (index > jmeno[0] - 1) {
        error_exit("bitset_setbit: Index %lu mimo rozsah 0..%lu\n",
                   (unsigned long)index, jmeno[0]);
    }

    if (vyraz) {
        /*   [index v poli UL] |=  (maska <<  (index v konkrétním UL)) */
        jmeno[bity(index) + 1] |=  (1UL   <<  (index % SULB));
    } else {
        jmeno[bity(index) + 1] &= ~(1UL   <<  (index % SULB));
    }
}


/* získá hodnotu zadaného bitu, vrací hodnotu 0 nebo 1 */
static inline bitset_t bitset_getbit(bitset_t jmeno[], bitset_t index) {
    if (index > jmeno[0] - 1) {
        error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu\n",
                   index, jmeno[0]);

    }
    return ((jmeno[bity(index) + 1]) >> (index % SULB)) & 1UL;
}

#endif  // ndef USE_INLINE
#endif  // ndef _BITSET_H