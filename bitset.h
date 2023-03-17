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


typedef unsigned long bitset_index_t;
typedef unsigned long bitset_t;

/* určí, v kolikátém UL je n-tý bit (vstup i výstup počítán od nuly) */
#define bity(n) n / (sizeof(unsigned long) * 8)


/* Velikost unsigned longu v bitech */
#define SULB sizeof(unsigned long) * 8


#ifndef USE_INLINE


/* definuje a nuluje proměnnou jmeno_pole */
#define bitset_create(jmeno, velikost) \
    static_assert(velikost > 0 && velikost <= ULONG_MAX, /* xxx */ \
                  "bitset_create: Nesprávná velikost pole " \
                  "(parametr `velikost` je počet bitů."); \
    bitset_t jmeno[bity(velikost) + 2] = {0}; \
    jmeno[0] = velikost;


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
                   (unsigned long)index, jmeno[0]); \
    } \
\
    if (vyraz) { \
        /*   [index v poli UL] |=  (maska <<  (index v konkrétním UL)) */ \
        jmeno[bity(index) + 1] |=  (1UL   <<  (index % SULB)); \
    } \
    else { \
        jmeno[bity(index) + 1] &= ~(1UL   <<  (index % SULB)); \
    }


// takto by to asi melo byt hotove ale radeji zkontrolovat ja uz na to nemam ted
#define bitset_getbit(jmeno, index) \
    (index > jmeno[0] - 1) ? \
        ( \
            error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu\n", \
                       (unsigned long)index, jmeno[0]),  /* operator carka */ \
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



// TODO: use inline !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#endif
