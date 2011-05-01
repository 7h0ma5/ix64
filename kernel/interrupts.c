#include <kernel/interrupts.h>
#include <kernel/kprint.h>
#include <kernel/video.h>
#include <kernel/io.h>

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

void ipanic(istack stack) {
  stop_interrupts();
  video_set_background(video_red);
  video_clear();

  kputs("KERNEL PANIC\n\n");
  kputs("An exception has occurred.\n");
  kputs("Please reboot.\n\n");

  kputs("EXCEPTION 0x");
  kputn(stack.int_no, 16);
  kputs(" with code 0x");
  kputn(stack.err_code, 16);
  kputs("\n\n");

  kputs("rax: 0x");
  kputn(stack.rax, 16);
  kputs(" / rbx: 0x");
  kputn(stack.rbx, 16);
  kputs(" / rcx: 0x");
  kputn(stack.rcx, 16);
  kputs(" / rdx: 0x");
  kputn(stack.rdx, 16);

  kputs("\nrbp: 0x");
  kputn(stack.rbp, 16);
  kputs(" / rsi: 0x");
  kputn(stack.rsi, 16);
  kputs(" / rdi: 0x");
  kputn(stack.rdi, 16);
  kputs("\n\n");

  kputs("r8: 0x");
  kputn(stack.r8, 16);
  kputs(" / r9: 0x");
  kputn(stack.r9, 16);
  kputs(" / r10: 0x");
  kputn(stack.r9, 16);
  kputs(" / r11: 0x");
  kputn(stack.r9, 16);

  kputs("\nr12: 0x");
  kputn(stack.r9, 16);
  kputs(" / r13: 0x");
  kputn(stack.r9, 16);
  kputs(" / r14: 0x");
  kputn(stack.r9, 16);
  kputs(" / r15: 0x");
  kputn(stack.r9, 16);

  while (1) {};
}

void isr_handler(istack stack) {
  kputs("received interrupt 0x");
  kputn(stack.int_no, 16);
  kputs("/0x");
  kputn(stack.err_code, 16);
  kputs("\n");

  if (stack.int_no == 0xD) {
    ipanic(stack);
  }
}

void irq_handler(istack stack) {
  if (stack.int_no >= 40) {
    outb(0xA0, 0x20);
  }
  outb(0x20, 0x20);
}
