#include "framebuffer.h"

#define FB_VGA_START (void *) 0xb8000

int fb_puts(char *s) {
    char *cur;
    for (cur = FB_VGA_START; *s != '\0'; s++, cur++)
        *cur++ = *s;
}

int fb_clear() {
    char *i;
    for (i = FB_VGA_START; i < (char *)(500 * 800 * 2); i += 2)
        *i = 0;
}

int fb_init() {
    fb_clear();
}
