AS = nasm -f elf64
CC = gcc -Wall -fno-stack-protector -nostdinc
LD = ld -nostdlib -T tools/link.ld

asm := $(patsubst %.asm,%.o,$(wildcard asm/*.asm))
kernel := $(patsubst %.c,%.o,$(wildcard kernel/*.c))

all: $(asm) $(kernel) $(drivers)
	$(LD) $(LDFLAGS) $(asm) $(kernel) -o kernel.bin
	bash tools/grub.sh
	bash tools/iso.sh

%.o: %.c
	$(CC) $(CXXFLAGS) -c -o $@ $<
	rm -f $@.bc $@.S

%.o: %.asm
	$(AS) -o $@ $<

clean:
	find . -name "*.o" -delete
	rm -f kernel.bin
	rm -f os.iso
	rm -f boot/eltorito.img

qemu:
	bash tools/qemu.sh