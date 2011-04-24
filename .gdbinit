set architecture i386:x86-64
target remote :1234
symbol-file build/kernel.elf
display/i $pc