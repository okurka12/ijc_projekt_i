/*****************
**  Vit Pavlik  **
**   xpavli0a   **
**    251301    **
**              **
**   Created:   **
**  2023-02-26  **
**              **
** Last edited: **
**  2023-03-17  **
*****************/
// Fakulta: FIT VUT
// Vyvíjeno s gcc 10.2.1 na Debian GNU/Linux 11

#ifndef _ERROR_H
#define _ERROR_H


/* Tiskne warning do stderr, voláno stejně jako printf() */
void warning(const char *fmt, ...);


/* Tiskne error do stderr a ukončí program, voláno stejně jako printf() */
void error_exit(const char *fmt, ...);

#endif  // ndef _ERROR_H



#if 0  // warning a error pak naimplementovat takhle

void error_exit(const char *fmt, ...) {
    va_list valist;

    va_start(valist, fmt);
    vprintf(fmt, valist);
    va_end(valist);

}

#endif
