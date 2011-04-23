#include <kernel/video.h>

#define WIDTH  80
#define HEIGHT 25

char* video_mem = (char*)0xb8000;
char video_attr = 0x0f;
int video_x = 0;
int video_y = 0;

void video_print(const char* text) {
  int i;
  for (i = 0; text[i] != '\0'; i++) {
    video_put(text[i]);
  }
}

void video_put(char c) {
  switch(c) {
    case '\n':
      video_x = 0;
      video_y++;
      break;

    default:
      video_mem[(video_x+(video_y*WIDTH))*2] = c;
      video_mem[(video_x+(video_y*WIDTH))*2+1] = video_attr;
      video_x++;
  }

  // check width
  if (video_x >= WIDTH) {
    video_x = 0;
    video_y++;
  }

  // check height
  if (video_y ==  HEIGHT) {
    video_scroll();
  }
  video_cursor();
}

void video_clear() {
  int i;
  for (i = 0; i < WIDTH*HEIGHT*2; i += 2) {
    video_mem[i] = ' ';
    video_mem[i+1] = video_attr;
  }
  video_x = 0;
  video_y = 0;
  video_cursor();
}

void video_cursor() {
  unsigned int pos;
  pos = video_y * WIDTH + video_x;
  /*
  Machine::outb(0x3D4, 14);
  Machine::outb(0x3D5, pos >> 8);
  Machine::outb(0x3D4, 15);
  Machine::outb(0x3D5, pos);
  */
}

void video_scroll() {
  int i;
  for (i = 0; i < WIDTH*(HEIGHT-1)*2; i += 2) {
    video_mem[i] = video_mem[i+WIDTH*2];
    video_mem[i+1] = video_mem[i+1+WIDTH*2];
  }
  for (i = WIDTH*(HEIGHT-1)*2; i < WIDTH*HEIGHT*2; i += 2) {
    video_mem[i] = ' ';
    video_mem[i+1] = video_attr;
  }
  video_y--;
}

void video_set_color(char color) {
  video_attr = color;
}

void video_set_background(char color) {
  video_attr = video_attr | (color << 4);
}
