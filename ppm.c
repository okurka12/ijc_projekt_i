/*****************
**  Vit Pavlik  **
**   xpavli0a   **
**    251301    **
**              **
**   Created:   **
**  2023-03-19  **
**              **
** Last edited: **
**  2023-03-19  **
*****************/
// Fakulta: FIT VUT
// Vyvíjeno s gcc 10.2.1 na Debian GNU/Linux 11

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include "error.h"
#include "ppm.h"

/* Otevře soubor a nepodaří-li se, zavolá exit */
FILE *open_file(const char *filename) {
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        switch (errno) {
        
        case EACCES:
            warning("Není oprávnění k otevření %s\n", filename);
            break;
        case EEXIST:
            warning("Nelze otevřít %s: soubor neexistuje\n", filename);
            break;
        case EINVAL:
            warning("Nelze otevřít %s: název obsahuje neplatné znaky\n", 
                    filename);
            break;
        case EISDIR:
            warning("Nelze otevřít %s: je adresář\n", filename);
            break;
        default:
            warning("Nelze otevřít %s\n", filename);
        }
    }

    return f;
}


/* Přečte hlavičku ppm souboru (stream f) a vloží údaje do struct ppm 
   *image_struct. Při chybě vrací NULL. File stream f je po skončení této 
   funkce na začátku binárních dat */
struct ppm *read_header(struct ppm *image_struct, FILE *f) {
    
    char line[MLL];  // line buffer
    char failure = 0;  // příznak chyby v hlavičce

    for (unsigned int i = 0; i < 3; i++) {
        if (fgets(line, MLL, f) == NULL) {
            warning("Chyba při čtení souboru\n");
            return NULL;
        }

        // pokud první řádek nezačíná "P6"
        if (i == 0 && (line[0] != 'P' || line[1] != '6')) {
            failure = 1;
            break;
        }

        // pokud na druhém řádku nejsou dvě čísla
        if (i == 1 && (sscanf(line, "%u %u", &(image_struct->xsize), 
                              &(image_struct->ysize)) != 2)) {
            failure = 1;
            break;
        }

        // pokud třetí řádek nezačíná "255"
        if (i == 2 && (line[0] != '2' || line[1] != '5' || line[2] != '5')) {
            failure = 1;
            break;
        }
    }
    if (failure) {
        warning("Hlavička ppm souboru je neplatná nebo používá konstrukce, "
                "které nejsou tímto programem implementačně ošetřeny "
                "(např. komentáře nebo zvláštní odřádkování).\n");
        return NULL;
    }
    
    // toto je jedna čtyřnásobná disjunkce, přišlo mi to snazší než psát
    // 4× spojku OR do podmínky příkazu if
    failure = 0;
    failure += image_struct->xsize > MAXSIZE;
    failure += image_struct->xsize < 1;
    failure += image_struct->ysize > MAXSIZE;
    failure += image_struct->ysize < 1;
    if (failure) {
        warning("Obrázek nesprávně velký\n");
        return NULL;
    }
    
    return image_struct;
}


struct ppm *ppm_read(const char *filename) {
    // otevření souboru
    FILE *f = open_file(filename);  // already checked for NULL

    // alokace místa pro strukturu
    struct ppm *image_struct = malloc(sizeof(struct ppm));

    if (image_struct == NULL) {
        warning("Chyba alokace paměti\n");
        return NULL;
    }

    if (read_header(image_struct, f) == NULL) {
        return NULL;
    }

    image_struct->data = malloc((image_struct->xsize) * 
                                (image_struct->ysize) *
                                3 *
                                sizeof(char));

    if (image_struct->data == NULL) {
        warning("Chyba alokace paměti\n");
        return NULL;
    }

    int data_byte;
    unsigned int i;
    for (i = 0; (data_byte = fgetc(f)) != EOF; i++) {
        (image_struct->data)[i] = data_byte;

        if (i > (image_struct->xsize) * (image_struct->ysize) * 3) {
            warning("Soubor má více bajtů než by měl mít "
                    "podle dat v hlavičce\n");
            return NULL;
        }
    }
    fclose(f);

    if ((image_struct->xsize) * (image_struct->ysize) > i) {
        warning("Soubor má méně bajtů než by měl mít podle dat v hlavičce.\n");
        return NULL;
    }

    return image_struct;

}

void ppm_free(struct ppm *image_struct) {
    free(image_struct->data);
    free(image_struct);
}