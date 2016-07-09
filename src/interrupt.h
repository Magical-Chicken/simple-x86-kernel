#include "types.h"

#ifndef _INTERRUPT_
#define _INTERRUPT_

/***
 * how many idt entries should be present
 * this should always be 256
 */
#define IDT_ENTRY_COUNT 256

/***
 * idt access flags
 */
enum idt_gate_types {
    IDT_GATE_TASK_32    = 0x05, // Task gate 32 bit
    IDT_GATE_INT_16     = 0x06, // Interrupt gate 16 bit
    IDT_GATE_TRAP_16    = 0x07, // Trap gate 16 bit
    IDT_GATE_INT_32     = 0x0E, // Interrupt gate 32 bit
    IDT_GATE_TRAP_32    = 0x0F, // Trap gate 32 bit
};


/***
 * raw and simplified idt entry struct
 */
struct idt_entry_raw {
    uint16_t    base_low;
    uint16_t    segment;
    uint8_t     zero;
    uint8_t     access;
    uint16_t    base_high;
} __attribute__((packed));

typedef struct idt_entry_simple {
    void *isr_pointer;
    uint8_t int_slot;
} idt_entry_t;

/***
 * idt pointer for lidt call
 */
struct idt_ptr {
    uint16_t    limit;
    uint32_t    base;
} __attribute__((packed));

/***
 * write idt data
 */
void idt_init();
void idt_register(idt_entry_t entry);

#endif
