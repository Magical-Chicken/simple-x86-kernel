#include "types.h"

#ifndef _KLIB_
#define _KLIB_

/***
 * Set memory contents at dst with count bytes of value c
 * Returns write destination
 */
void *memset(void *dst, uchar val, size_t count);

/***
 * Copy count bytes of memory from src to dst
 * Returns write destination
 */
void *memcpy(void *dst, const void *src, size_t count);

/***
 * Write byte to port
 */
void outb(uint16_t port, uchar val);

/***
 * Read byte from port
 */
uchar inb(uint16_t port);

/***
 * Print functions
 * 
 * note: puts is just passthrough to console_puts,
 *       console_puts re-declared in case console.h not included by caller
 */
void console_puts(const char *str);
#define puts(args) console_puts(args)

#endif
