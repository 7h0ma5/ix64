#include <ix/version.h>
#include <ix/kprintf.h>
#include <ix/pmm.h>
#include <ix/vmm.h>
#include <ix/irq.h>
#include <ix/timer.h>

void do_init(const char* msg, int (*initfun)()) {
  kprintf(":: %s...", msg);
  int res = initfun();
  if (!res) kprintf(" done\n");
  else      kprintf(" failed\n");
}

void main() {
  kprintf("=== IX " VERSION " ===\n");

  do_init("init irqs", irq_init);
  do_init("init timer", timer_init);
  do_init("init physical memory", pmm_init);
  do_init("init virtual memory", vmm_init);

  for (;;) {}
}
