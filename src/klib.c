#include "klib.h"
#include "types.h"

/***
 * Set memory contents at dst with count bytes of value c
 * Returns write destination
 */
void *memset(void *dst, uchar val, size_t count) {
    uint i;
    for (i = 0; i < count; i++) ((uchar *)dst)[i] = val;
    return dst;
}

/***
 * Copy count bytes of memory from src to dst
 * Returns write destination
 */
void *memcpy(void *dst, const void *src, size_t count) {
    uint i;
    for (i = 0; i < count; i++) ((uchar *)dst)[i] = ((uchar *)src)[i];
    return dst;
}

/***
 * Write byte to port
 */
inline void outb(uint16_t port, uchar val){
    asm volatile("outb %0,%1"::"a"(val), "Nd"(port));
}

/***
 * Read byte from port
 */
inline uchar inb(uint16_t port) {
    uchar res;
    asm volatile("inb %1,%0":"=a"(res):"Nd"(port));
    return res;
}
