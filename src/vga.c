#include "klib.h"
#include "types.h"
#include "vga.h"

/***
 * contents of current vga display
 */
static struct vga_d_char *VGA_BUF = (struct vga_d_char *)0xB8000;
static struct vga_state VGA_STATE;

/***
 * set up vga:
 *
 * set cursor to (0, 0)
 * set default fg/bg color
 * clear screen
 */
void vga_init() {
    VGA_STATE.fg = GREEN, VGA_STATE.bg = BLACK;
    vga_clear();
}

/***
 * clear vga screen
 */
void vga_clear() {
    memset(VGA_BUF, NULL, VGA_WIDTH * VGA_HEIGHT * 2);
    VGA_STATE.cursor_x = VGA_STATE.cursor_y = 0;
}

/***
 * write text to vmem
 */
void vga_puts(char *str) {
    char cur;
    vga_d_char_t *pos = VGA_BUF +
            (VGA_STATE.cursor_y * VGA_WIDTH + VGA_STATE.cursor_x);
    while ((cur = *str++) != NULL) {
        (*pos).c = cur;
        (*pos++).color = VGA_STATE.fg | (VGA_STATE.bg << 4);
        if (++VGA_STATE.cursor_x >= VGA_WIDTH) {
            VGA_STATE.cursor_x = 0;
            VGA_STATE.cursor_y += 1;
        }
    }
}
