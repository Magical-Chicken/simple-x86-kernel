.extern     GDT_PTR

.global     load_gdt
.type       load_gdt, @function
load_gdt:
    lgdt    GDT_PTR
    movw    $0x10,%ax
    movw    %ax,%ds
    movw    %ax,%es
    movw    %ax,%fs
    movw    %ax,%gs
    movw    %ax,%ss
    # the new gdt may have caused a shift of 8 bytes, so jump to skip
    jmp     _flush
    ret    
    .skip 8
_flush:
    ret
