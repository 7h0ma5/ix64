#include <kernel/video.h>
#include <kernel/interrupts.h>
#include <kernel/kprint.h>

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

void panic() {
  stop_interrupts();
  video_set_background(video_red);
  video_clear();

  kputs("KERNEL PANIC\n\n");
  kputs("An exception has occured.\n");
  kputs("Please reboot.\n\n");
  
  while (1) {};
}

void kmain() {
  video_clear();
  video_set_color(video_bright_green);
  video_print("IX 0.1");
  video_set_color(video_blue);
  video_print("       Copyright 2011\n\n");
  video_set_color(video_white);

  step("starting interrupts");
  interrupts_init();
  done();

  while (1) {};

  panic();
}