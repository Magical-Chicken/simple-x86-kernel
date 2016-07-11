#include "gdt.h"
#include "interrupt.h"
#include "klib.h"
#include "types.h"

/***
 * idt pointer instance
 */
struct idt_ptr IDT_PTR = {
    .limit = (sizeof(struct idt_entry_raw) * IDT_ENTRY_COUNT) - 1,
    .base = (uint32_t)IDT_ENTRIES,
};

/***
 * configure idt, by default all error handlers are hard halt
 */
extern void hard_halt();
void idt_init() {
    //memset(IDT_ENTRIES, NULL, sizeof(struct idt_entry_raw) * IDT_ENTRY_COUNT);
    int i;
    for (i = 0; i < IDT_ENTRY_COUNT; i++)
        idt_register(i, (uint32_t)&hard_halt, IDT_GATE_INT_ATTR);
}

/***
 * register isr
 */
void idt_register(uint8_t idt_slot, uint32_t isr, enum idt_gate_access access) {
    struct idt_entry_raw *entry = &IDT_ENTRIES[idt_slot];
    // only supports ring isr located in kernel right now
    entry->segment = (uint16_t)GDT_ENTRY_KERNEL_CODE;
    entry->zero = 0;
    entry->base_low = (uint16_t)((uint32_t)isr & 0xFFFF);
    entry->base_high = (uint16_t)(((uint32_t)isr >> 16) & 0xFFFF);
    entry->access = access;
}
