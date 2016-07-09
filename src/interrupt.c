#include "interrupt.h"
#include "klib.h"
#include "types.h"

/***
 * actual idt entry array
 */
static struct idt_entry_raw IDT_ENTRIES[IDT_ENTRY_COUNT];
struct idt_ptr IDT_PTR = {
    .limit = (sizeof(struct idt_entry_raw) * IDT_ENTRY_COUNT) - 1,
    .base = (uint32_t)IDT_ENTRIES,
};

/***
 * configure idt
 */
void idt_init() {
    memset(IDT_ENTRIES, NULL, IDT_ENTRY_COUNT);
}

/***
 * register isr
 */
void idt_register(uint8_t idt_slot, void *isr) {
}
