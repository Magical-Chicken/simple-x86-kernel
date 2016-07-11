.extern     err_display
.extern     hard_halt

.global     err_0_isr
.type       err_0_isr, @function
err_0_isr:
    # divide by zero fault
    pusha
    cld
    mov     $0,%edx
    call    err_display
    popa
    call    hard_halt

.global     err_1_isr
.type       err_1_isr, @function
err_1_isr:
    # debug
    pusha
    cld
    mov     $1,%edx
    call    err_display
    popa

.global     err_2_isr
.type       err_2_isr, @function
err_2_isr:
    # non maskable interrupt
    pusha
    cld
    mov     $2,%edx
    call    err_display
    popa

.global     err_3_isr
.type       err_3_isr, @function
err_3_isr:
    # breakpoint
    pusha
    cld
    mov     $3,%edx
    call    err_display
    popa

.global     err_4_isr
.type       err_4_isr, @function
err_4_isr:
    # overflow
    pusha
    cld
    mov     $4,%edx
    call    err_display
    popa

.global     err_5_isr
.type       err_5_isr, @function
err_5_isr:
    # bound range exceeded
    pusha
    cld
    mov     $5,%edx
    call    err_display
    popa

.global     err_6_isr
.type       err_6_isr, @function
err_6_isr:
    # invalid opcode
    pusha
    cld
    mov     $6,%edx
    call    err_display
    popa

.global     err_7_isr
.type       err_7_isr, @function
err_7_isr:
    # device not available
    pusha
    cld
    mov     $7,%edx
    call    err_display
    popa

.global     err_8_isr
.type       err_8_isr, @function
err_8_isr:
    # double fault
    cld
    mov     $8,%edx
    call    err_display
    call    hard_halt

.global     err_9_isr
.type       err_9_isr, @function
err_9_isr:
    # unused (coprocessor segment overrun)
    call    hard_halt

.global     err_A_isr
.type       err_A_isr, @function
err_A_isr:
    # invalid tss
    pusha
    cld
    mov     $0xA,%edx
    call    err_display
    popa
