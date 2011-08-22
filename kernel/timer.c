#include <ix/timer.h>
#include <ix/irq.h>
#include <ix/kprintf.h>

#define TIMER_REG ((volatile unsigned*)0x13000000)
#define TIMER1_REG (TIMER_REG + 0x40)

cpu_state* timer_tick(cpu_state* state) {
  TIMER1_REG[3] = 42;
  return state;
}

int timer_init() {
  TIMER1_REG[0] = (10000 + 128) / 256;
  TIMER1_REG[2] = 0xEA;

  irq_register(6, timer_tick);

  return 0;
}
