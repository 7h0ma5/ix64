#include <kernel/kprint.h>
#include <drivers/video.h>
#include <stdarg.h>

void kprintf(const char* format, ...) {
    va_list ap;
    va_start(ap, format);

    while (*format) {
        if (*format == '%') {
            format++;
            switch (*format) {
            case 'i':
                kputn(va_arg(ap, int), 10);
                break;

            case 'p':
                kputn(va_arg(ap, unsigned long), 16);
                break;

            case 's':
                kputs(va_arg(ap, const char*));
                break;
                }
            }
        else {
            kputc(*format);
        }
        format++;
    }
    va_end(ap);
}

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
    video_print(str);
}

void kputc(char c) {
    video_put(c);
}
