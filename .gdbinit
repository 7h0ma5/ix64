set architecture i386:x86-64:intel
target remote :1234
symbol-file kernel.elf
display/i $pc