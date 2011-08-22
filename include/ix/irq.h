#ifndef IX_IRQ_H
#define IX_IRQ_H

#include <cpu.h>

typedef void (irq_handler)(cpu_state*);

int irq_init();
void irq_enable();
void irq_disable();
void irq_handle(cpu_state*);
void irq_register(unsigned, irq_handler*);

#endif
