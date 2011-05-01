#include <kernel/interrupts.h>
#include <kernel/kprint.h>
#include <kernel/video.h>
#include <kernel/io.h>

int interrupts_init() {
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

  return 0;
}

void exception(interrupt_stack stack) {
  stop_interrupts();
  video_set_background(video_red);
  video_clear();

  kputs("KERNEL PANIC\n\n");
  kputs("An exception has occurred.\n");
  kputs("Please reboot.\n\n");

  kprintf("EXCEPTION %p with code %p\n\n", stack.int_no, stack.err_code);

  kprintf("rax: %p rbx: %p rcx: %p rdx: %p\n", stack.rax, stack.rbx, stack.rcx, stack.rdx);
  kprintf("rbp: %p rsi: %p rdi: %p\n", stack.rbp, stack.rsi, stack.rdi);
  kprintf("r8: %p r9: %p r10: %p r11: %p\n", stack.r8, stack.r9, stack.r10, stack.r11);
  kprintf("r12: %p r13: %p r14: %p r15: %p\n", stack.r12, stack.r13, stack.r14, stack.r15);

  while (1) {};
}

void isr_handler(interrupt_stack stack) {
  exception(stack);
}

void irq_handler(interrupt_stack stack) {
  if (stack.int_no >= 40) {
    outb(0xA0, 0x20);
  }
  outb(0x20, 0x20);
}
