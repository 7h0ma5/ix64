#include <drivers/video.h>
#include <kernel/io.h>

#define WIDTH  80
#define HEIGHT 25

char* vmem = (char*)0xb8000;
char vattr = 0x0f;
int vx = 0;
int vy = 0;

void video_print(const char* text) {
    int i;
    for (i = 0; text[i] != '\0'; i++) {
        video_put(text[i]);
    }
}

void video_put(char c) {
    switch(c) {
    case '\n':
        vx = 0;
        vy++;
        break;

    case '\b':
        vx--;
        video_put(' ');
        vx--;
        break;

    default:
        vmem[(vx+(vy*WIDTH))*2] = c;
        vmem[(vx+(vy*WIDTH))*2+1] = vattr;
        vx++;
    }

    // check width
    if (vx >= WIDTH) {
        vx = 0;
        vy++;
    }

    // check height
    if (vy ==  HEIGHT) {
        video_scroll();
    }
    video_cursor();
}

void video_clear() {
    int i;
    for (i = 0; i < WIDTH*HEIGHT*2; i += 2) {
        vmem[i] = ' ';
        vmem[i+1] = vattr;
    }
    vx = 0;
    vy = 0;
    video_cursor();
}

void video_cursor() {
    unsigned int pos;
    pos = vy * WIDTH + vx;
    outb(0x3D4, 14);
    outb(0x3D5, pos >> 8);
    outb(0x3D4, 15);
    outb(0x3D5, pos);
}

void video_scroll() {
    int i;
    for (i = 0; i < WIDTH*(HEIGHT-1)*2; i += 2) {
        vmem[i] = vmem[i+WIDTH*2];
        vmem[i+1] = vmem[i+1+WIDTH*2];
    }
    for (i = WIDTH*(HEIGHT-1)*2; i < WIDTH*HEIGHT*2; i += 2) {
        vmem[i] = ' ';
        vmem[i+1] = vattr;
    }
    vy--;
}

void video_set_color(char color) {
    vattr = color;
}

void video_set_background(char color) {
    vattr = vattr | (color << 4);
}
