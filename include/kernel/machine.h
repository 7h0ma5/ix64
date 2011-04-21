#ifndef MACHINE_H
#define MACHINE_H

class Machine {
public:
  static void init();

  static void startInterrupts();
  static void stopInterrupts();

  static void outb(unsigned short, unsigned char);
  static unsigned char inb(unsigned short);
  static unsigned short inw(unsigned short);
};

#endif