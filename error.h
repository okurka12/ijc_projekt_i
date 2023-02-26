/*****************
**  Vit Pavlik  **
**   xpavli0a   **
**    251301    **
**              **
**   Created:   **
**  2023-02-26  **
**              **
** Last edited: **
**  2023-02-26  **
*****************/



/* 
   Napište modul "error.c" s rozhraním v "error.h", který definuje
   funkci void warning(const char *fmt, ...) a
   funkci void error_exit(const char *fmt, ...).
   Tyto funkce mají stejné parametry jako printf(); tisknou
   text "Warning: " nebo "Error: " a potom chybové hlášení podle
   formátu fmt. Vše se tiskne do stderr (standardní funkcí vfprintf)
   a potom pouze error_exit ukončí program voláním funkce exit(1).
   Použijte definice ze stdarg.h.
*/

/* Tiskne warning do stderr, voláno stejně jako printf() */
void warning(const char *fmt, ...);


/* Tiskne error do stderr a ukončí program, voláno stejně jako printf() */
void error_exit(const char *fmt, ...);
