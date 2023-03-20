/*****************
**  Vit Pavlik  **
**   xpavli0a   **
**    251301    **
**              **
**   Created:   **
**  2023-03-20  **
**              **
** Last edited: **
**  2023-03-20  **
*****************/
// Fakulta: FIT VUT
// Vyvíjeno s gcc 10.2.1 na Debian GNU/Linux 11

#ifndef _UTF8CHECK_H
#define _UTF8CHECK_H

/* Kontroluje řetězec na UTF-8 kódování a vrací buď ukazatel na místo s chybou
   nebo NULL jestli je řetězec v pořádku */
unsigned char *utf8_check(unsigned char *s);

#endif  // ndef _UTF8CHECK_H
