#include "types.h"

#ifndef _KLIB_
#define _KLIB_

/***
 * memory access utils
 */
void *memset(void *dst, uchar val, size_t count);
void *memcpy(void *dst, const void *src, size_t count);

/***
 * port communication
 */
void outb(uint16_t port, uchar val);
uchar inb(uint16_t port);

/***
 * Print functions
 * 
 * note: puts is just passthrough to console_puts,
 *       console_puts re-declared in case console.h not included by caller
 *
 * note: puti and putx are just shorthand for putibasex
 */
void console_puts(const char *str);
void putibasex(int num, int base);
#define puts(args) console_puts(args)
#define puti(args) putibasex(args, 10)
#define putx(args) putibasex(args, 0x10)

#endif
