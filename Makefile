AS = nasm -f elf64
LD = ld -nostdlib -T tools/link.ld
CXX = g++ -g -Iinclude -Wall -nostdlib -fno-builtin -nostartfiles -nodefaultlibs -fno-exceptions -fno-rtti -fno-stack-protector

asm := $(patsubst %.asm,%.o,$(wildcard asm/*.asm))
kernel := $(patsubst %.cc,%.o,$(wildcard kernel/*.cc))

all: kernel.bin iso

kernel.bin: $(kernel) $(asm)
	$(LD) $(LDFLAGS) $(asm) $(kernel) -o kernel.elf
	objcopy -O binary kernel.elf kernel.bin

%.o: %.cc
	$(CXX) -c -o $@ $<

%.o: %.asm
	$(AS) -o $@ $<

clean:
	find . -name "*.o" -delete
	rm -f kernel.bin kernel.elf
	rm -f os.iso

grub:
	bash tools/grub.sh

iso:
	bash tools/iso.sh

qemu:
	bash tools/qemu.sh

.PHONY: all qemu iso grub clean