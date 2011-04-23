#ifndef IX_INTERRUPTS_H
#define IX_INTERRUPTS_H

void interrupts_init();

// from interrupts.s
void idt_init();
void start_interrupts();
void stop_interrupts();

#endif