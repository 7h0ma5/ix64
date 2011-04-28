#ifndef IX_INTERRUPTS_H
#define IX_INTERRUPTS_H

typedef struct istack {
  unsigned long r8, r9, r10, r11, r12, r13, r14, r15;
  unsigned long rax, rbx, rcx, rdx, rbp, rsi, rdi;
  unsigned long int_no, err_code;
} istack;

void interrupts_init();

// from interrupts.s
void idt_init();
void start_interrupts();
void stop_interrupts();

#endif