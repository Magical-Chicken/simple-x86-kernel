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

/***
 * temporary function to print integral value until printf is written
 */
void puti(int num) {
    // TODO: when malloc written make it dynamic
    int i, cur, digit_count;
    char buf[256], *pos, *end;
    bool add_minus = num < 0;
    buf[0] = add_minus ? '-' : ' ';
    buf[255] = NULL;
    pos = buf;
    end = &buf[255];
    if (add_minus) num *= -1;
    for (i = num, digit_count = 0; i > 0; i /= 10, digit_count++);
    for (i = digit_count; i > 0; i--) {
        cur = 0x30 + num;
        num /= 10;
        cur -= 10 * num;
        buf[add_minus ? i : i - 1] = 0xFF & cur;
    }
    buf[add_minus ? digit_count + 1 : digit_count] = NULL;
    puts(buf);
}
