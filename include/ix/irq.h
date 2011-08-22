#ifndef IX_IRQ_H
#define IX_IRQ_H

#include <cpu.h>

typedef cpu_state* (irq_handler)(cpu_state*);

int irq_init();
void irq_enable();
void irq_disable();
cpu_state* irq_handle(cpu_state*);
void irq_register(unsigned, irq_handler*);

#endif
