#include "vga.h"

void main() {
    // init
    vga_init();
    int i;
    for (i = 0; i < 16 * 4; i++)
        vga_puts("test ");
    vga_puts("helloworld");
    vga_newline();
    for (i = 0; i < -1 + 16 * 4 + 14; i++)
        vga_puts("test ");
}
