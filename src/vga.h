#include "types.h"

#ifndef _VGA_
#define _VGA_

/***
 * set default vga dimensions
 */
#ifndef VGA_WIDTH
#define VGA_WIDTH 40
#endif
#ifndef VGA_HEIGHT
#define VGA_HEIGHT 25
#endif

/***
 * 16 color mode only
 */
typedef enum vga_color {
    BLACK   = 0x0,
    MAROON  = 0x1,
    GREEN   = 0x2,
    OLIVE   = 0x3,
    NAVY    = 0x4,
    PURPLE  = 0x5,
    TEAL    = 0x6,
    SILVER  = 0x7,
    GREY    = 0x8,
    RED     = 0x9,
    LIME    = 0xA,
    YELLOW  = 0xB,
    BLUE    = 0xC,
    FUSCIA  = 0xD,
    AQUA    = 0xE,
    WHITE   = 0xF,
} vga_color_t;

typedef uchar vga_full_color_t;

/***
 * vga display character, char val and color
 */
typedef struct vga_d_char {
    char c;
    vga_full_color_t color;
} vga_d_char_t;

/***
 * current vga display state:
 */
typedef struct vga_state {
    uint cursor_x, cursor_y;
    enum vga_color fg, bg;
} vga_state;

/***
 * set up vga
 */
void vga_init();

/***
 * clear screen
 */
void vga_clear();

/***
 * write text
 */
void vga_puts(char *str);

#endif
