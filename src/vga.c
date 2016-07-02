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
                   (size_t)VGA_WIDTH * 2);
        }
    }
}

/***
 * write text to vmem
 */
void vga_puts(char *str) {
    char cur;
    vga_d_char_t *pos;
    while ((cur = *str++) != NULL) {
        // write character and set color
        pos = VGA_BUF + VGA_STATE.cursor_x + (VGA_STATE.cursor_y * VGA_WIDTH);
        (*pos).c = cur;
        (*pos).color = VGA_STATE.fg | (VGA_STATE.bg << 4);
        // update cursor position
        if (++VGA_STATE.cursor_x >= VGA_WIDTH)
            vga_newline();
    }
}
