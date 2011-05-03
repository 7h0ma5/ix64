#include <kernel/interrupts.h>
#include <kernel/kprint.h>
#include <kernel/io.h>

char lowercase[256] = {'^','x','1','2','3','4','5','6','7','8','9','0','x','x','\b',
                       '\t','q','w','e','r','t','z','u','i','o','p','x','+','\n','x',
                       'a','s','d','f','g','h','j','k','l','x','x','<','x','#',
                       'y','x','c','v','b','n','m',',','.','-'};

char uppercase[256] = {'°','X','!','"','§','$','%','&','/','(',')','=','X','X','\b',
                       '\t','Q','W','E','R','T','Z','U','I','O','P','X','*','\n','X',
                       'A','S','D','F','G','H','J','K','L','X','X','>','X','\'',
                       'Y','X','C','V','B','N','M',';',':','_'};

unsigned int shift_state;

void keyboard_interrupt(interrupt_stack stack) {
    unsigned char scan_code = inb(0x60);

    switch(scan_code) {
    case 0x2a:
        shift_state = 1;
        break;

    case 0xAA:
        shift_state = 0;
        break;

    default:
        if (scan_code > 128) {
            // ignore
        }
        else {
            if (shift_state) {
                kputc(uppercase[scan_code]);
            }
            else {
                kputc(lowercase[scan_code]);
            }
        }
        break;
    }

    outb(0x20, 0x20);
}

int keyboard_init() {
    interrupts_register(33, &keyboard_interrupt);
    return 0;
}
