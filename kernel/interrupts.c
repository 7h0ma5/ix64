#include <kernel/interrupts.h>
#include <kernel/kprint.h>
#include <kernel/io.h>

typedef struct registers {
  unsigned long r8, r9, r10, r11, r12, r13, r14, r15;
  unsigned long rax, rbx, rcx, rdx, rbp, rsi, rdi;
  unsigned long int_no, err_code;
  unsigned long eip, cs, eflags, useresp, ss;
} registers;

void interrupts_init() {
  idt_init();

  // remap irq's
  outb(0x20, 0x11);
  outb(0xA0, 0x11);
  outb(0x21, 0x20);
  outb(0xA1, 0x28);
  outb(0x21, 0x04);
  outb(0xA1, 0x02);
  outb(0x21, 0x01);
  outb(0xA1, 0x01);
  outb(0x21, 0x0);
  outb(0xA1, 0x0);

  start_interrupts();
}

void isr_handler(registers regs) {
  kputs("received interrupt 0x");
  kputn(regs.int_no, 16);
  kputs("/0x");
  kputn(regs.err_code, 16);
  kputs("\n");
}

void irq_handler(registers regs) {
  kputs("received irq 0x");
  kputn(regs.int_no, 16);
  kputs("/0x");
  kputn(regs.err_code, 16);
  kputs("\n");

  if (regs.int_no >= 40) {
    outb(0xA0, 0x20);
  }
  outb(0x20, 0x20);
}

