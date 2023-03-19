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

#define MLL 30  // max line length (buffer size) for ppm header line
#define MAXSIZE 16000  // max size of one side of the image

// struktura s obrázkem včetně metadat
struct ppm {
    unsigned xsize;
    unsigned ysize;
    char *data;    // RGB bajty, celkem 3*xsize*ysize
};


/* Načte obsah P6 PPM souboru do touto funkcí dynamicky
   alokované struktury. Při chybě formátu použije funkci warning
   a vrátí NULL. */
struct ppm * ppm_read(const char * filename);


// uvolní paměť dynamicky alokovanou v ppm_read
void ppm_free(struct ppm *p);
