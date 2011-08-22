#include <ix/kprintf.h>
#include <ix/irq.h>

#define IC_REGS ((volatile unsigned*)0x14000000)

int irq_init() {
  IC_REGS[3] = 0xffffffff;
  irq_enable();
  return 0;
}

void irq_handle() {
  kprintf("got an interrupt\n");
}
