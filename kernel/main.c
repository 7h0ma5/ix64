#include <kernel/video.h>
#include <kernel/interrupts.h>
#include <kernel/kprint.h>
#include <kernel/multiboot.h>
#include <kernel/memory.h>
#include <kernel/paging.h>

void step(const char* message) {
  kprintf("%s...", message);
}

void test(int res) {
  if (res == 0) {
    video_set_color(video_bright_green);
    video_print("done\n");
    video_set_color(video_white);
  }
  else {
    video_set_color(video_bright_red);
    video_print("fail\n");
    video_set_color(video_white);
  }
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

void kmain(multiboot_info* mbinfo) {
  video_clear();
  video_set_color(video_bright_green);
  video_print("IX 0.1");
  video_set_color(video_blue);
  video_print("       Copyright 2011\n\n");
  video_set_color(video_white);


  step("starting interrupts");
  test(interrupts_init());

  step("initialize memory");
  test(memory_init());

  step("initialize paging");
  test(paging_init());

  while (1) {};

  panic();
}
