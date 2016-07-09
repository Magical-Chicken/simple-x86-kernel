#include "gdt.h"
#include "types.h"

/***
 * actual gdt entry array
 * note: gdt size limit should always be one byte than actual size
 */
static struct gdt_entry GDT_ENTRIES[GDT_ENTRY_COUNT];
struct gdt_ptr GDT_PTR = {
    .limit = (sizeof(struct gdt_entry) * GDT_ENTRY_COUNT) - 1,
    .base = (uint32_t)&GDT_ENTRIES,
};

/***
 * write gdt data
 */
void gdt_init() {
    // first entry has to be null
    gdt_populate_struct(&GDT_ENTRIES[0], 0, 0, GDT_NULL_ACCESS, 0);
    // FIXME: for now just using full 4G address space for both code and data,
    //        may be good to limit size for both and separate them once kernel
    //        is near its final size
    gdt_populate_struct(&GDT_ENTRIES[1], 0, ~(uint32_t)0,
            GDT_CODE_ACCESS_RING0, 0xCF);
    gdt_populate_struct(&GDT_ENTRIES[2], 0, ~(uint32_t)0,
            GDT_DATA_ACCESS_RING0, 0xCF);
}

void gdt_populate_struct(struct gdt_entry *dst, uint32_t base, uint32_t limit,
        enum gdt_access_mode access, uchar granularity) {
    // base is split for 32 bit systems for compat with 16 bit
    (*dst).base_low = base & 0xFFFF;
    (*dst).base_middle = (base >> 16) & 0xFF;
    (*dst).base_high = (base >> 24) & 0xFF;
    // limit high and granularity in same byte
    (*dst).limit_low = limit & 0xFFFF;
    (*dst).granularity = ((limit >> 16) & 0x0F) | (granularity & 0xF0);
    // access mode
    (*dst).access = (uint8_t)access;
}
