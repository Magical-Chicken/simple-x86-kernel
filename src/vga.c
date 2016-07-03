#include "klib.h"
#include "types.h"
#include "vga.h"

#define FORMAT_COLORS(fg, bg) (uchar)(fg | (bg << 4))

/***
 * contents of current vga display
 */
static struct vga_d_char *VGA_BUF = (struct vga_d_char *)0xB8000;
static struct vga_state VGA_STATE = { .fg = GREEN, .bg = BLACK };

/***
 * set up vga:
 *
 * set cursor to (0, 0)
 * set default fg/bg color
 * clear screen
 */
void vga_init() {
    //VGA_STATE.fg = GREEN, VGA_STATE.bg = BLACK;
    vga_set_cursor_enable(true);
    vga_clear();
}

/***
 * clear vga screen
 */
void vga_clear() {
    vga_d_char_t *pos, *end;
    end = VGA_BUF + VGA_HEIGHT * VGA_WIDTH * sizeof(vga_d_char_t);
    for (pos = VGA_BUF; pos < end; pos++) {
        (*pos).c = NULL;
        (*pos).color = FORMAT_COLORS(VGA_STATE.fg, VGA_STATE.bg);
    }
    vga_update_cursor(0, 0);
}

/***
 * increment line, scrolling text if needed
 */
void vga_newline() {
    int i;
    //vga_d_char_t *pos;
    VGA_STATE.cursor_x = 0;
    if (++VGA_STATE.cursor_y >= VGA_HEIGHT) {
        VGA_STATE.cursor_y = VGA_HEIGHT - 1;
        for (i = 0; i < VGA_HEIGHT; i++) {
            memcpy((void *)(VGA_BUF + i * VGA_WIDTH),
                   (void *)(VGA_BUF + (i + 1) * VGA_WIDTH),
                   (size_t)VGA_WIDTH * sizeof(vga_d_char_t));
        }
    }
    vga_sync_cursor();
}

/***
 * update the vga cursor position
 */
void vga_update_cursor(uint16_t x, uint16_t y) {
    VGA_STATE.cursor_x = x;
    VGA_STATE.cursor_y = y;
    vga_sync_cursor();
}

/***
 * update the vga cursor in vga registers
 */
void vga_sync_cursor() {
    uint16_t cursor_pos = VGA_STATE.cursor_x + VGA_STATE.cursor_y * VGA_WIDTH;
    vga_crt_reg_set(CRT_CURSOR_LOC_HIGH,
            (uchar)((cursor_pos & (0xFF << 8)) >> 8));
    vga_crt_reg_set(CRT_CURSOR_LOC_LOW, (uchar)(cursor_pos & 0xFF));
}

/***
 * either enable or disable vga cursor
 */
void vga_set_cursor_enable(bool enabled) {
    uchar start_reg_val = vga_crt_reg_get(CRT_CURSOR_START);
    // enable/disable is bit 5
    if (!enabled) start_reg_val = start_reg_val | 0x20;
    else start_reg_val = start_reg_val & 0xDF;
    vga_crt_reg_set(CRT_CURSOR_START, start_reg_val);
}

/***
 * write char to vmem
 */
void vga_putchar(const char c) {
    vga_d_char_t *pos;
    // write character and set color
    pos = VGA_BUF + VGA_STATE.cursor_x + (VGA_STATE.cursor_y * VGA_WIDTH);
    (*pos).c = c;
    (*pos).color = FORMAT_COLORS(VGA_STATE.fg, VGA_STATE.bg);
    // update cursor position
    if (++VGA_STATE.cursor_x >= VGA_WIDTH) vga_newline();
    vga_sync_cursor();
}

/***
 * write data to crt control register at index
 */
void vga_crt_reg_set(enum vga_crt_reg_index index, uchar data) {
    // save previous index value and restore later
    int16_t prev = inb(VGA_CRT_REG_ADR_PORT);
    outb(VGA_CRT_REG_ADR_PORT, (int16_t)index);
    outb(VGA_CRT_REG_DATA_PORT, data);
    outb(VGA_CRT_REG_ADR_PORT, prev);
}

/***
 * read data from crt control register at index
 */
uchar vga_crt_reg_get(enum vga_crt_reg_index index) {
    uchar res;
    int16_t prev = inb(VGA_CRT_REG_ADR_PORT);
    outb(VGA_CRT_REG_ADR_PORT, (int16_t)index);
    res = inb(VGA_CRT_REG_DATA_PORT);
    outb(VGA_CRT_REG_ADR_PORT, prev);
    return res;
}
