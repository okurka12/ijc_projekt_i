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

#include <stdio.h>

#include "ppm.h"
#include "error.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: steg-decode path\n");
    }
    printf("debug oteviram %s\n", argv[1]);
    struct ppm *image_struct = ppm_read(argv[1]);
    if (image_struct == NULL) {
        error_exit("Nastala chyba při čtení %s, končím.\n", argv[1]);
    }
    printf("dabug jou funguje to dobry\n");
    return 0;
}