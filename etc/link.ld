SECTIONS {
  .text 0x00000000 : AT(0x00000000) {
    *(.vectors);
    *(.text);
  }

  .data : ALIGN(4096) {
    *(.data);
  }

  .rodata : ALIGN(4096) {
    *(.rodata);
  }

  .bss : ALIGN(4096) {
    *(.bss);
   }
}