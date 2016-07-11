#include "klib.h"
#include "error.h"
#include "interrupt.h"
#include "types.h"

extern void err_0_isr();

void error_init() {
    //idt_register(0, (void *)&err_0_isr, IDT_GATE_INT_ATTR);
}

void err_display(uint8_t err) {
    puts("\ntest");
}
