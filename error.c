/*****************
**  Vit Pavlik  **
**   xpavli0a   **
**    251301    **
**              **
**   Created:   **
**  2023-03-17  **
**              **
** Last edited: **
**  2023-03-17  **
*****************/
// Fakulta: FIT VUT
// Vyvíjeno s gcc 10.2.1 na Debian GNU/Linux 11

#include <stdarg.h>  // va_list
#include <stdio.h>   // fprintf
#include <stdlib.h>  // exit()

#include "error.h"

void warning(const char *fmt, ...) {
    va_list valist;

    fprintf(stderr, "Warning: ");
    va_start(valist, fmt);
    vfprintf(stderr, fmt, valist);
    va_end(valist);

}


void error_exit(const char *fmt, ...) {
    va_list valist;

    fprintf(stderr, "Error: ");
    va_start(valist, fmt);
    vprintf(fmt, valist);
    va_end(valist);
    exit(1);

}