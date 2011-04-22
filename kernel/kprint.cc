#include <kernel/kprint.h>
#include <kernel/video.h>

void kputn(long value, unsigned int radix) {
  char buffer[65];
  char* ptr = buffer;
  const char* const chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  unsigned long temp;
  unsigned long digits;

  if (value < 0) {
    kputc('-');
    value = -value;
  }
  if (radix < 2 || radix > 36) return;

  temp = value;
  digits = 0;
  do {
    digits++;
    temp = temp/radix;
  } while (temp > 0);

  if (digits > 65) return;
  ptr += digits;
  *ptr = 0;

  temp = value;
  do {
    *--ptr = chars[temp%radix];
    temp = temp/radix;
  } while (--digits);

  kputs(ptr);
}

void kputs(const char* str) {
  Video::print(str);
}

void kputc(char c) {
  Video::put(c);
}
