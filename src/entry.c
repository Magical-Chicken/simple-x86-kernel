#include "console.h"
#include "klib.h"

void entry() {
    // configure output console and enable vga output
    console_init();
    console_connect_interface(CONSOLE_INTERFACE_VGA);

    // welcome
    puts("hello world\n");
    puti(-12345678);
    puts("\n\t");
    putx(1491625);
    puts("\n\t");
    putibasex(0xA5A5, 2);
}
