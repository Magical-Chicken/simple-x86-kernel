bits 32
section .text
    align   4
    dd      0x1BADB002
    dd      0x00
    dd    - (0x1BADB002 + 0x00)

global start
extern main

start:
    cli
    mov     esp, kstack
    call    main
    hlt

section .bss
resb    8192
kstack:
