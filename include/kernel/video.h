#ifndef VIDEO_H
#define VIDEO_H

class Video {
private:
  static char* mem;
  static char attr; 
  static int x;
  static int y;

public:
  static void put(char);
  static void print(const char*);
  static void clear();
  
  static void cursor();
  static void scroll();
  
  static void setColor(char);
  static void setBackground(char);
  
  enum {
    black = 0x0,
    blue = 0x1,
    green = 0x2,
    cyan = 0x3,
    red = 0x4,
    magenta = 0x5,
    brown = 0x6,
    bright_grey = 0x7,
    grey = 0x8,
    bright_blue = 0x9,
    bright_green = 0xa,
    bright_cyan = 0xb,
    bright_red = 0xc,
    bright_magenta = 0xd,
    yellow = 0xe,
    white = 0xf,
  };
};

#endif