#include <kernel/video.h>

void init_interrupts();

void step(const char* message) {
  video_print(message);
  video_print("... ");
}

void done() {
  video_set_color(video_bright_green);
  video_print("done\n");
  video_set_color(video_white);
}

void fail() {
  video_set_color(video_bright_red);
  video_print("fail\n");
  video_set_color(video_white);
}

void kmain() {
  video_clear();
  video_set_color(video_bright_green);
  video_print("IX 0.1\n\n");
  video_set_color(video_white);

  step("starting interrupts");
  init_interrupts();
  asm volatile("sti");
  done();

  while (1) {};
}
