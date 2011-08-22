.section .text
.global init
init:

init_stack:
    ldr sp, [pc, #kernel_stack_addr - 8 - .]

start:
    bl main

stop:
    b stop

kernel_stack_addr:
.4byte kernel_stack

.section .bss
.space 8192
kernel_stack:
