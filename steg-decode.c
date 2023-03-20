/*****************
**  Vit Pavlik  **
**   xpavli0a   **
**    251301    **
**              **
**   Created:   **
**  2023-03-19  **
**              **
** Last edited: **
**  2023-03-20  **
*****************/
// Fakulta: FIT VUT
// Vyvíjeno s gcc 10.2.1 na Debian GNU/Linux 11

#include <limits.h>        // CHAR_BIT (jea stačilo napsat 8 ale pro jistotu)
#include <stdio.h>

#include "bitset.h"        // vytvoření bitového pole pro funkci eratosthenes
#include "ppm.h"           // načtení ppm souboru do paměti
#include "eratosthenes.h"  // filtrování prvočísel
#include "error.h"         // makra na chybová hlášení

#define START_PRIME 101



/* převede pole 8 charů, které reprezentují bity (0 nebo 1) na jeden char 
   a zároveň vynuluje ono pole charů, LSb je v tomto poli na indexu 0*/
unsigned char bits_to_byte(unsigned char bits[]) {
    unsigned char output = 0;
    for (unsigned int i = 0; i < CHAR_BIT; i++) {
        output += bits[i] << i;
        bits[i] = 0;
    }
    return output;
}


int main(int argc, char *argv[]) {

    // pokud je jiný počet argumentů než jeden
    if (argc != 2) {
        fprintf(stderr, "Usage: steg-decode path\n");
    }

    // načtení ppm obrázku do paměti
    struct ppm *image_struct = ppm_read(argv[1]);
    if (image_struct == NULL) {
        error_exit("Nastala chyba při čtení %s, končím.\n", argv[1]);
    }

    // vytvoření bitového pole: každý bit pro jeden bajt obrázku
    bitset_index_t n = (image_struct->xsize) * (image_struct->ysize) * 3;
    bitset_alloc(policko, n);

    // nastavíme v poli prvočísla
    Eratosthenes(policko, n);
    
    // Pole osmi charů, abych každý char byl bit a každých 8 iterací
    // v následujícím for cyklu z těchto bitů poskládal bajt
    unsigned char bits[CHAR_BIT] = {0};
    bitset_index_t bitcount = 0;
    
    unsigned char c;
    bitset_index_t i;
    for (i = START_PRIME; i < n; i++) {

        // pokud i NENI prvocislo, tak kod pod ifem NEPROBEHNE
        if (bitset_getbit(policko, i)) { 
            continue;
        }

        // ------- nasledujici kod probehne jen kdyz i je prvocislo -------

        // ulozi LSb (LSb z i-teho bajtu obrazku)
        bits[bitcount % CHAR_BIT] = 
        (unsigned char)(image_struct->data)[i] % 2;

        // zvetseni indexu
        bitcount++;

        // každých 8 iterací poskládání jednoho bajtu
        if (bitcount % 8 == 0) {
            c = bits_to_byte(bits);
            putchar(c);
            if (c == '\0') {
                break;  // break at '\0'
            }
        }
    }

    if (i == n - 1) {
        error_exit("Zpráva není ukončena \\0 bytem.\n");
    }

    putchar('\n');  // newline nakonec

    bitset_free(policko);  // uvolneni alokovane pameti
    ppm_free(image_struct);

    return 0;
}