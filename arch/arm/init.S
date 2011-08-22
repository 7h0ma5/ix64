.section .text
.global init
init:

init_stack:
    /* set stack for supervisor mode */
    ldr sp, [pc, #kernel_stack_addr - 8 - .]

    /* set stack for irq mode */
    mov r0, sp
    msr cpsr_ctl, #0xD2
    add sp, r0, #8192
    msr cpsr_ctl, #0xD3

start:
    bl main

stop:
    b stop

kernel_stack_addr:
.4byte kernel_stack

.section .bss

.space 8192
irq_stack:
.space 8192
kernel_stack:
