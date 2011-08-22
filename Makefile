ARCH = arm

CC = arm-elf-gcc
ASM = arm-elf-as
LD = arm-elf-ld

CFLAGS = -Iinclude -Iarch/$(ARCH) -std=gnu99 -fno-builtin-putchar	\
-nostartfiles -nodefaultlibs -nostdinc -Wall -Wextra				\
-fno-stack-protector -ffreestanding -march=armv5t -mfloat-abi=hard	\
-mfpu=fpa -include stddef.h

ASMFLAGS = -mfloat-abi=hard -mfpu=fpa
LDFLAGS = -nostdlib -Tetc/link.ld

ARCHOBJS = arch/$(ARCH)/init.o \
		   arch/$(ARCH)/irq.o

KERNELOBJS = kernel/main.o \
	         kernel/irq.o \
             kernel/kprintf.o \
             kernel/pmm.o \
			 kernel/vmm.o \
			 kernel/timer.o

LIBOBJS = lib/string.o

all: $(ARCHOBJS) $(KERNELOBJS) $(LIBOBJS)
	$(LD) $(LDFLAGS) -o kernel.bin $(ARCHOBJS) $(KERNELOBJS) $(LIBOBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

%.o: %.S
	$(ASM) $(ASMFLAGS) -c -o $@ $<

clean:
	rm -f $(ARCHOBJS) $(KERNELOBJS) $(LIBOBJS)
	rm -f kernel.bin

qemu: all
	qemu-system-arm -monitor vc:1200x800 -kernel kernel.bin -serial stdio
