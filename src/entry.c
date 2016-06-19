#include "vga.h"

void main() {
    // init
    vga_init();
    vga_puts("hello world ");
    for (int i = 0; i < 125; i++)
        vga_puts("test ");
}
