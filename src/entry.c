//#include "vga.h"
#include "console.h"
#include "klib.h"

void main() {
    // configure output console and enable vga output
    console_init();
    console_connect_interface(CONSOLE_INTERFACE_VGA);

    // welcome
    puts("hello world\n");
}
