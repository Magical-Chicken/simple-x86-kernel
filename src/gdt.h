#include "types.h"

#ifndef _GDT_
#define _GDT_

/***
 * how may entries should space be reserved for
 *
 * note: this does not leave space for any tss tables, will add later
 *       depending on how multitasking is to be done many may be needed
 */
#define GDT_ENTRY_COUNT 3

/***
 * gdt segment access modes (incomplete list)
 */
enum gdt_access_mode {
    GDT_NULL_ACCESS = 0,
    GDT_CODE_ACCESS = 0x9A,
    GDT_DATA_ACCESS = 0x92,
    GDT_TSS_ACCESS  = 0x92,
};

/***
 * raw gdt entry struct
 */
struct gdt_entry {
    uint16_t    limit_low;
    uint16_t    base_low;
    uint8_t     base_middle;
    uint8_t     access;
    uint8_t     granularity;
    uint8_t     base_high;
} __attribute__((packed));

/***
 * gdt pointer for lgdt call
 */
struct gdt_ptr {
    uint16_t    limit;
    uint32_t    base;
} __attribute__((packed));

/***
 * write gdt data
 */
void gdt_init();
void gdt_populate_struct(struct gdt_entry *dst, uint32_t base, uint32_t limit,
        enum gdt_access_mode access, uchar granularity);

#endif
