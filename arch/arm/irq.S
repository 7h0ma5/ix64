.section .vectors
vectors:
    b init  /* reset */
    b undef /* undefined */
    b swi   /* software interrupt */
    b pabt  /* instruction abort */
    b dabt  /* data abort */
    nop     /* unused */
    b irq   /* irq */

/* fast irq (part of the vector table) */
fiq:
    subs pc, lr, #4

.text
irq:
    /* save registers */
    push {r0 - r12, lr}

    /* save supervisor-sp/lr/spsr and cpsr */
    msr cpsr_ctl, #0xd3
    mrs r1, spsr
    mov r2, sp
    mov r3, lr
    msr cpsr_ctl, #0xd2
    mrs r0, spsr
    push {r0 - r3}

    /* save user-sp/lr */
    stmdb sp, {sp, lr}^
    sub sp, #8

    /* call the interrupt handler */
    mov r0, sp
    bl irq_handle
    mov sp, r0

    /* restore user-sp/lr */
    ldmia sp, {sp, lr}^
    add sp, #8

    /* restore supervisor-sp/lr/spsr and cpsr */
    pop {r0 - r3}
    msr spsr_all, r0
    msr cpsr_ctl, #0xd3
    msr spsr_all, r1
    mov sp, r2
    mov lr, r3
    msr cpsr_all, #0xd2

    /* restore registers */
    pop {r0 - r12, lr}

    subs pc, lr, #4

undef:
    subs pc, lr, #4

swi:
    subs pc, lr, #4

pabt:
    subs pc, lr, #4

dabt:
    subs pc, lr, #4

.global irq_enable
irq_enable:
    mrs r1, cpsr
    bic r1, r1, #0xc0
    msr cpsr_ctl, r1
    mov pc, lr

.global irq_disable
irq_disable:
    mrs r1, cpsr
    orr r1, r1, #0xc0
    msr cpsr_ctl, r1
    mov pc, lr
