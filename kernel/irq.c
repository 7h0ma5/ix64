#include <ix/kprintf.h>
#include <ix/irq.h>

#define IC_REGS ((volatile unsigned*)0x14000000)

static irq_handler* irq_handlers[32];

int irq_init() {
  IC_REGS[3] = 0xffffffff;
  irq_enable();
  return 0;
}

cpu_state* irq_handle(cpu_state* state) {
  unsigned irq = 0;
  unsigned status = IC_REGS[0];

  while (status) {
    if (status & 1) {
      state = irq_handlers[irq](state);
    }
    irq++;
    status >>= 1;
  }

  return state;
}

void irq_register(unsigned irq, irq_handler* handler) {
  if (irq > 32) return;
  if (irq_handlers[irq]) return;

  irq_handlers[irq] = handler;

  IC_REGS[2] |= 1 << irq;
}
