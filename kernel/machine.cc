#include <kernel/machine.h>

extern "C" void idt_init();

void Machine::init() {
  idt_init();
}

void Machine::startInterrupts() {
  asm volatile("sti");
}

void Machine::stopInterrupts() {
  asm volatile("cli");
}

void Machine::outb(unsigned short port, unsigned char value) {
  asm volatile("outb %1, %0" : : "dN" (port), "a" (value));
}

unsigned char Machine::inb(unsigned short port) {
  unsigned char ret;
  asm volatile("inb %1, %0" : "=a" (ret) : "dN" (port));
  return ret;
}

unsigned short Machine::inw(unsigned short port) {
  unsigned short ret;
  asm volatile("inw %1, %0" : "=a" (ret) : "dN"(port));
  return ret;
}
