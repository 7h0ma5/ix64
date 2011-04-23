ENTRY(entry)
OUTPUT_FORMAT(elf64-x86-64)

SECTIONS {
    . = 0x100000;

    .text : {
        text_start = .;
        *(.multiboot)
        *(.text)
        text_end = .;
    }

    .data ALIGN(4096) : {
        data_start = .;
        *(.data)
        *(.rodata)
        data_end = .;
    }

    .bss ALIGN(4096) : {
        bss_start = .;
        *(.bss)
        bss_end = .;
    }
}
