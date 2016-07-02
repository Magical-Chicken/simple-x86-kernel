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
 * VGA ports and crt controller register indices
 */
#define VGA_CRT_REG_ADR_PORT 0x3D4
#define VGA_CRT_REG_DATA_PORT 0x3D5

enum vga_crt_reg_index {
    CRT_HORIZ_TOTAL         = 0x00,
    CRT_END_HORIZ_DISP      = 0x01,
    CRT_START_HORIZ_BLANK   = 0x02,
    CRT_END_HORIZ_BLANK     = 0x03,
    CRT_START_HORIZ_RETRACE = 0x04,
    CRT_END_HORIZ_RETRACE   = 0x05,
    CRT_VERT_TOTAL          = 0x06,
    CRT_OVERFLOW            = 0x07,
    CRT_PRESET_ROW_SCAN     = 0x08,
    CRT_MAX_SCAN_LINE       = 0x09,
    CRT_CURSOR_START        = 0x0A,
    CRT_CURSOR_END          = 0x0B,
    CRT_START_ADR_HIGH      = 0x0C,
    CRT_START_ADR_LOW       = 0x0D,
    CRT_CURSOR_LOC_HIGH     = 0x0E,
    CRT_CURSOR_LOC_LOW      = 0x0F,
    CRT_START_VERT_RETRACE  = 0x10,
    CRT_END_VERT_RETRACE    = 0x11,
    CRT_END_VERT_DISP       = 0x12,
    CRT_OFFSET              = 0x13,
    CRT_UNDERLINE_LOC       = 0x14,
    CRT_START_VERT_BLANK    = 0x15,
    CRT_END_VERT_BLANK      = 0x16,
    CRT_MODE_CONTROL        = 0x17,
    CRT_LINE_COMPARE        = 0x18,
};

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

/***
 * vga display character, char val and color
 */
typedef struct vga_d_char {
    char c;
    uchar color;
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
 * increment line, scrolling text if needed
 */
void vga_newline();

/***
 * update the vga cursor in vga registers
 */
void vga_sync_cursor();

/***
 * update the vga cursor position
 */
void vga_update_cursor(uint16_t x, uint16_t y);

/***
 * either enable or disable vga cursor
 */
void vga_set_cursor_enable(uchar enabled);

/***
 * write text
 */
void vga_puts(char *str);

/***
 * write data to crt control register at index
 */
void vga_crt_reg_set(enum vga_crt_reg_index index, uchar data);

/***
 * read data from crt control register at index
 */
uchar vga_crt_reg_get(enum vga_crt_reg_index index);

#endif
