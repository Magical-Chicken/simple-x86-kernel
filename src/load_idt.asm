.extern     IDT_PTR
.extern     idt_init

.global     load_idt
.type       load_idt, @function
load_idt:
    cli
    call    idt_init
    lidt    IDT_PTR
    ret
