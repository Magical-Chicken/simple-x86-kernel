# multiboot config and setup
.set ALIGN,     1 << 0              # align modules on page boundaries
.set MEMINFO,   1 << 1              # provide memory map
.set FLAGS,     ALIGN | MEMINFO     # flags
.set MAGIC,     0x1BADB002          # header magic
.set CHECKSUM,  -(MAGIC + FLAGS)    # checksum to prove multi

.section .multiboot

.align  4
.long   MAGIC
.long   FLAGS
.long   CHECKSUM

# configure early stack (to be replaced once gdt loaded)
.section .stack, "aw", @nobits

stack_bottom:
    .skip   16384
stack_top:

.section .text

.extern     entry
.extern     load_gdt
.extern     load_idt

.global     _start
.type       _start, @function
_start:
    movl    $stack_top,%esp
    cli
    call    load_gdt
    call    load_idt
    #call    error_init
    #sti
    call    entry
    jmp     _halt

.extern     _halt
.type       _halt, @function
_halt:
    cli
    hlt
    jmp     _halt

.size _start, . - _start
