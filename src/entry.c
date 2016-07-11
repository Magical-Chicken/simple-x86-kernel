#include "console.h"
#include "error.h"
#include "klib.h"
extern void err_0_isr();

void entry() {
    // configure output console and enable vga output
    console_init();
    console_connect_interface(CONSOLE_INTERFACE_VGA);

    // welcome
    puts("hello world");
    //asm volatile ("int %0"::"Nb"(0));

    // halt execution, wait for interrupts
    soft_halt();
}
