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
 * gdt segment access modes (from intel manual)
 */
#define GDT_BASE_ACCESS GDT_SEG_DESC_DATA | GDT_SEG_PRES | GDT_SEG_NOT_SAVL | \
    GDT_SEG_NOT_LONG | GDT_SEG_32B | GDT_SEG_4G_GRAN

enum gdt_access_permissions {
    GDT_SEG_DATA_RD         = 0x00, // Read only
    GDT_SEG_DATA_RDA        = 0x01, // Read only, accessed
    GDT_SEG_DATA_RDWR       = 0x02, // Read/Write
    GDT_SEG_DATA_RDWRA      = 0x03, // Read/Write, accessed
    GDT_SEG_DATA_RDEXPD     = 0x04, // Read only, expand down
    GDT_SEG_DATA_RDEXPDA    = 0x05, // Read only, expand down, accessed
    GDT_SEG_DATA_RDWREXPD   = 0x06, // Read/Write expand down
    GDT_SEG_DATA_RDWREXPDA  = 0x07, // Read/Write expand down, accessed
    GDT_SEG_CODE_EX         = 0x08, // Execute only
    GDT_SEG_CODE_EXA        = 0x09, // Execute only, accessed
    GDT_SEG_CODE_EXRD       = 0x0A, // Execute/Read
    GDT_SEG_CODE_EXRDA      = 0x0B, // Execute/Read, accessed
    GDT_SEG_CODE_EXC        = 0x0C, // Execute, conforming
    GDT_SEG_CODE_EXCA       = 0x0D, // Execute, conforming, accessed
    GDT_SEG_CODE_EXRDC      = 0x0E, // Execute/Read, conforming
    GDT_SEG_CODE_EXRDCE     = 0x0F, // Execute/Read, conforming, accessed
};

enum gdt_access_flags {
    GDT_SEG_DESC_SYS        = 0,         // System segment
    GDT_SEG_DESC_DATA       = 1 << 0x04, // Code/data segment
    GDT_SEG_NOT_PRES        = 0,         // Not present
    GDT_SEG_PRES            = 1 << 0x07, // Present
    GDT_SEG_NOT_SAVL        = 0,         // Not available for sys use
    GDT_SEG_SAVL            = 1 << 0x0C, // Available for sys use
    GDT_SEG_NOT_LONG        = 0,         // Not long mode
    GDT_SEG_LONG            = 1 << 0x0D, // Long mode
    GDT_SEG_16B             = 0,         // 16 bit
    GDT_SEG_32B             = 1 << 0x0E, // 32 bit
    GDT_SEG_1M_GRAN         = 0,         // 1B-1MB granularity
    GDT_SEG_4G_GRAN         = 1 << 0x0F, // 4KB-4GB granularity
    GDT_SEG_PRIV_RING0      = 0,         // Ring 0, max priv
    GDT_SEG_PRIV_RING1      = 1 << 0x05, // Ring 1, unused
    GDT_SEG_PRIV_RING2      = 2 << 0x05, // Ring 2, unused
    GDT_SEG_PRIV_RING3      = 3 << 0x05, // Ring 3, userspace priv
};

enum gdt_access_mode {
    GDT_NULL_ACCESS = 0,
    GDT_CODE_ACCESS_RING0   = GDT_BASE_ACCESS | GDT_SEG_CODE_EXRD |
                              GDT_SEG_PRIV_RING0,
    GDT_DATA_ACCESS_RING0   = GDT_BASE_ACCESS | GDT_SEG_DATA_RDWR |
                              GDT_SEG_PRIV_RING0,
    GDT_CODE_ACCESS_RING3   = GDT_BASE_ACCESS | GDT_SEG_CODE_EXRD |
                              GDT_SEG_PRIV_RING3,
    GDT_DATA_ACCESS_RING3   = GDT_BASE_ACCESS | GDT_SEG_DATA_RDWR |
                              GDT_SEG_PRIV_RING3,
    GDT_TSS_ACCESS_RING0    = GDT_BASE_ACCESS | GDT_SEG_DATA_RDWR |
                              GDT_SEG_PRIV_RING0,
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
