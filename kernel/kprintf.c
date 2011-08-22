#include <ix/kprintf.h>
#include <stdarg.h>

#define SERIAL_DR *((volatile unsigned char*)0x16000000)
#define SERIAL_FR *((volatile unsigned int*)0x16000018)
#define SERIAL_BUFFER_FULL (1 << 5)

static void putchar(char c) {
    while (SERIAL_FR & SERIAL_BUFFER_FULL);

    SERIAL_DR = c;
}

void kprintf(const char *s, ...) {
    va_list va;

    va_start(va, s);

    while (*s)
    {
        switch (*(s++))
        {
            case '%':
                switch (*(s++))
                {
                    case '%':
                        putchar('%');
                        break;
                    case 's':
                    {
                        const char *ns = va_arg(va, const char *);
                        while (*ns)
                            putchar(*(ns++));
                        break;
                    }
                    case 'c':
                        putchar(va_arg(va, int));
                        break;
                    case 'd':
                    case 'i':
                    {
                        int num = va_arg(va, int);
                        if (!num)
                            putchar('0');
                        else
                        {
                            if (num < 0)
                            {
                                putchar('-');
                                num *= -1;
                            }

                            char buf[11];
                            int i = 11;
                            while (num)
                            {
                                buf[--i] = num % 10 + '0';
                                num /= 10;
                            }
                            while (i < 11)
                                putchar(buf[i++]);
                        }
                        break;
                    }
                    case 'x':
                    {
                        unsigned num = va_arg(va, unsigned);
                        if (!num)
                            putchar('0');
                        else
                        {
                            int i;
                            for (i = 0; !(num >> 28); i++)
                                num <<= 4;
                            for (; i < 8; i++)
                            {
                                putchar((num >> 28) + ((num >> 28) < 10 ? '0' : 'a' - 10));
                                num <<= 4;
                            }
                        }
                        break;
                    }
                    case 'X':
                    {
                        unsigned num = va_arg(va, unsigned);
                        if (!num)
                            putchar('0');
                        else
                        {
                            int i;
                            for (i = 0; !(num >> 28); i++)
                                num <<= 4;
                            for (; i < 8; i++)
                            {
                                putchar((num >> 28) + ((num >> 28) < 10 ? '0' : 'A' - 10));
                                num <<= 4;
                            }
                        }
                        break;
                    }
                    case 'p':
                    {
                        unsigned num = va_arg(va, unsigned);
                        putchar('0');
                        putchar('x');
                        for (int i = 0; i < 8; i++)
                        {
                            putchar((num >> 28) + ((num >> 28) < 10 ? '0' : 'a' - 10));
                            num <<= 4;
                        }
                        break;
                    }
                    default:
                        putchar('%');
                        putchar(s[-1]);
                }
                break;
            default:
                putchar(s[-1]);
        }
    }

    va_end(va);
}
