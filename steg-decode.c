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
#include "eratosthenes.h"  // filtrování prvočísel
#include "error.h"         // makra na chybová hlášení
#include "ppm.h"           // načtení ppm souboru do paměti
#include "utf8check.h"     // funkce utf8_check

#define START_PRIME 101
#define MSG_BUFFSIZE 2048



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


/* Přečte bity dané prvočísly zadaným způsobem. Když zpráva nekončí '\0' nebo
   bude přetečen buffer, zavolá error_exit. Zprávu nahraje do bufferu.
   Parametr n je velikost bitového pole prvočísel, buffsize velikost bufferu */
void read_message(struct ppm *image_struct, bitset_t policko, bitset_index_t n,
                  unsigned char *message_buffer, unsigned int buffsize) {

    // Pole osmi charů, abych každý char byl bit a každých 8 iterací
    // v následujícím for cyklu z těchto bitů poskládal bajt
    unsigned char bits[CHAR_BIT] = {0};
    bitset_index_t bitcount = 0;
    bitset_index_t bytecount = 0;

    unsigned char c;
    bitset_index_t i;
    for (i = START_PRIME; i < n; i++) {

        // pokud i NENÍ prvočíslo, kéd pod příkazem if NEPROBĚHNE
        if (bitset_getbit(policko, i)) {
            continue;
        }

        // ------- následující kód proběhne jen když i je prvočíslo -------

        // uloží LSb (LSb z i-tého bajtu obrázku)
        bits[bitcount % CHAR_BIT] =
        (unsigned char)(image_struct->data)[i] % 2;

        bitcount++;  // zvětšení indexu v poli osmi bitů

        // každých 8 iterací poskládání jednoho bajtu
        if (bitcount % 8 == 0) {
            c = bits_to_byte(bits);
            message_buffer[bytecount] = c;
            bytecount++;  // zvětšení indexu v bufferu
            if (bytecount == buffsize) {
                error_exit("Zpráva se nevlezla do bufferu o velikosti %u. "
                "Velikost bufferu je možné změnit změnou makra MSG_BUFFSIZE "
                "ve zdrojovém souboru " __FILE__ ".\n", buffsize);
            }
            if (c == '\0') {
                break;  // break at '\0'
            }
        }
    }

    if (i == n - 1) {
        error_exit("Zpráva není ukončena \\0 bytem.\n");
    }

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

    // nastavit v poli prvočísla (eratostenovo síto)
    Eratosthenes(policko, n);

    // přečíst zprávu a nahrát ji do bufferu
    unsigned char message_buffer[MSG_BUFFSIZE];
    read_message(image_struct, policko, n, message_buffer, MSG_BUFFSIZE);

    // zkontrolovat zprávu na kódování
    if (utf8_check(message_buffer) != NULL) {
        error_exit("Zpráva není správně zakódována kódováním UTF-8.\n");
    }

    // vytisknout zprávu
    printf("%s\n", message_buffer);

    bitset_free(policko);  // uvolnění alokované paměti
    ppm_free(image_struct);

    return 0;
}
