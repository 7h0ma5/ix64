#include <kernel/machine.h>
#include <kernel/video.h>

void step(const char* message) {
  Video::print(message);
  Video::print("... ");
}

void done() {
  Video::setColor(Video::bright_green);
  Video::print("done\n");
  Video::setColor(Video::white);
}

void fail() {
  Video::setColor(Video::bright_red);
  Video::print("fail\n");
  Video::setColor(Video::white);
}

extern "C" void test_interrupt() {
  Video::print("received interrupt\n");
}

extern "C" void kmain() {
  Video::clear();
  Video::setColor(Video::bright_green);
  Video::print("BOOTING PROTIX 0.1\n\n");
  Video::setColor(Video::white);

  Machine::init();

  step("starting interrupts");
  Machine::startInterrupts();
  done();

  while (true) {};
}
