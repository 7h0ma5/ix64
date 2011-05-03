#ifndef IX_VIDEO_H
#define IX_VIDEO_H

void video_put(char);
void video_print(const char*);
void video_clear();
  
void video_cursor();
void video_scroll();
  
void video_set_color(char);
void video_set_background(char);
  
enum {
    video_black = 0x0,
    video_blue = 0x1,
    video_green = 0x2,
    video_cyan = 0x3,
    video_red = 0x4,
    video_magenta = 0x5,
    video_brown = 0x6,
    video_bright_grey = 0x7,
    video_grey = 0x8,
    video_bright_blue = 0x9,
    video_bright_green = 0xa,
    video_bright_cyan = 0xb,
    video_bright_red = 0xc,
    video_bright_magenta = 0xd,
    video_yellow = 0xe,
    video_white = 0xf
};

#endif