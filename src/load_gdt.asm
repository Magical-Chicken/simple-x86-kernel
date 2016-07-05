.extern     gdt_init
.extern     GDT_PTR

.global     load_gdt
.type       load_gdt, @function
load_gdt:
    call    gdt_init
    lgdt    GDT_PTR
    movw    $0x10,%ax
    movw    %ax,%ds
    movw    %ax,%es
    movw    %ax,%fs
    movw    %ax,%gs
    movw    %ax,%ss
    jmp     _flush + 8
_flush:
    ret
