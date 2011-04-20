MB_MAGIC  EQU 0xE85250D6
MB_ARCH   EQU 0
MB_HDRLEN EQU (mb_hdr.end - mb_hdr)
MB_CHKSUM EQU -(MB_MAGIC + MB_ARCH + MB_HDRLEN)

[SECTION multiboot]
ALIGN 64
mb_hdr:
	dd MB_MAGIC
	dd MB_ARCH
	dd MB_HDRLEN
	dd MB_CHKSUM
	;; 	dw 0, 0
	;; 	dd 8
.end:

[BITS 32]
[SECTION .text]

[EXTERN kmain]
[GLOBAL start]
start:
	;; setup the stack
	mov esp, kernel_stack

	call kmain

	;; if something went wrong
	cli
	hlt
	jmp $

;; kernel stack / 8 kB
[SECTION .bss]
resb 8192
kernel_stack:
