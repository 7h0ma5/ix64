#include <kernel/video.h>
#include <kernel/machine.h>

#define WIDTH  80
#define HEIGHT 25

char* Video::mem = (char*)0xb8000;
char Video::attr = 0x0f;
int Video::x = 0;
int Video::y = 0;

void Video::print(const char* text) {
  for (int i = 0; text[i] != '\0'; i++) {
    Video::put(text[i]);
  }
}

void Video::put(char c) {
  switch(c) {
    case '\n':
      x = 0;
      y++;
      break;

    default:
      mem[(x+(y*WIDTH))*2] = c;
      mem[(x+(y*WIDTH))*2+1] = attr;
      x++;
  }

  // check width
  if (x >= WIDTH) {
    x = 0;
    y++;
  }

  // check height
  if (y ==  HEIGHT) {
    scroll();
  }
  cursor();
}

void Video::clear() {
  for (int i = 0; i < WIDTH*HEIGHT*2; i += 2) {
    mem[i] = ' ';
    mem[i+1] = attr;
  }
  x = 0;
  y = 0;
  cursor();
}

void Video::cursor() {
  unsigned int pos;
  pos = y * WIDTH + x;
  Machine::outb(0x3D4, 14);
  Machine::outb(0x3D5, pos >> 8);
  Machine::outb(0x3D4, 15);
  Machine::outb(0x3D5, pos);
}

void Video::scroll() {
  for (int i = 0; i < WIDTH*(HEIGHT-1)*2; i += 2) {
    mem[i] = mem[i+WIDTH*2];
    mem[i+1] = mem[i+1+WIDTH*2];
  }
  for (int i = WIDTH*(HEIGHT-1)*2; i < WIDTH*HEIGHT*2; i += 2) {
    mem[i] = ' ';
    mem[i+1] = attr;
  }
  y--;
}

void Video::setColor(char color) {
  attr = color;
}

void Video::setBackground(char color) {
  attr = attr | (color << 4);
}
