#include "klib.h"
#include "types.h"
#include "framebuffer.h"

#define FB_VGA_START (void *) 0xb8000

int fb_puts(char *s) {
    char *cur = FB_VGA_START;
    while (*s != '\0'){
        *cur++ = *s++;
        *cur++ = 0x0E;
    }
}

int fb_clear() {
    memset(FB_VGA_START, NULL, 500 * 800 * 2);
}

int fb_init() {
    fb_clear();
}
