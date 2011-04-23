#include <kernel/kprint.h>

typedef struct registers {
  unsigned int ds;
  unsigned long r8, r9, r10, r11, r12, r13, r14, r15;
  unsigned long rax, rbx, rcx, rdx, rbp, rsi, rdi;
  unsigned long int_no, err_code;
  unsigned long eip, cs, eflags, useresp, ss;
} registers;

void isr_handler(registers regs) {
  kputs("received interrupt ");
  kputn(regs.int_no, 10);
  kputs("/");
  kputn(regs.err_code, 10);
  kputs("\n");
}
