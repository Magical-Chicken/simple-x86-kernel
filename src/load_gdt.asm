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
    # right now there is no offset specified for code in gdt, once code is
    # loaded in a specific location a far jump will be needed here
    ret
