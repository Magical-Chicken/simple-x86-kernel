#include "klib.h"
#include "types.h"

void *memset(void *dst, uchar val, size_t count) {
    uint i;
    for (i = 0; i < count; i++) ((uchar *)dst)[i] = val;
    return dst;
}

void *memcpy(void *dst, const void *src, size_t count) {
    uint i;
    for (i = 0; i < count; i++) ((uchar *)dst)[i] = ((uchar *)src)[i];
    return dst;
}
