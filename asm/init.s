[BITS 32]
[SECTION .multiboot]

[GLOBAL entry]
[EXTERN data_end]
[EXTERN bss_end]

entry:
    jmp start

MB_MAGIC  EQU 0x1BADB002
MB_FLAGS  EQU 1 << 1 | 1 << 16
MB_CHKSUM EQU -(MB_MAGIC + MB_FLAGS)

align 4
mb_hdr:
    dd MB_MAGIC
    dd MB_FLAGS
    dd MB_CHKSUM
    dd mb_hdr
    dd entry
    dd data_end
    dd bss_end
    dd entry

[SECTION .text]
start:
    cli ; stop interrupts

    ;; enable A20 gate
    in al, 0x92
    or al, 0x2
    out 0x92, al

    ;; setup the page tables
    mov edi, 0x1000 ; page tables at 0x1000
    mov cr3, edi
    xor eax, eax
    mov ecx, 4096
    rep stosd
    mov edi, cr3

    ;; add a first table chain
    mov dword [edi], 0x2003
    add edi, 0x1000
    mov dword [edi], 0x3003
    add edi, 0x1000
    mov dword [edi], 0x4003
    add edi, 0x1000

    ;; fill the first two megabytes
    mov ebx, 0x00000003
    mov ecx, 512
.set_entry:
    mov dword [edi], ebx
    add ebx, 0x1000
    add edi, 8
    loop .set_entry

    ;; enable physical address extension
    mov eax, cr4
    or eax, 1 << 5
    mov cr4, eax

    ;; set the long mode bit
    mov ecx, 0xC0000080
    rdmsr
    or eax, 1 << 8
    wrmsr

    ;; enable paging
    mov eax, cr0
    or eax, 1 << 31
    mov cr0, eax

    ;; set the gdt
    lgdt [gdt.pointer]

    jmp gdt.code:start64

align 8
gdt:
.null: equ $ - gdt
    dq 0

.code: equ $ - gdt
    dw 0xFFFF
    dw 0
    db 0
    db 0b10011010
    db 0b10101111
    db 0

.data: equ $ - gdt
    dw 0xFFFF
    dw 0
    db 0
    db 0b10010010
    db 0b10001111
    db 0

.pointer:
    dw $ - gdt - 1
    dq gdt

[BITS 64]
[EXTERN kmain]
start64:

    mov rcx, 90000000
.l:
    nop
    loop .l

    ;; set segment registers
    mov ax, gdt.data
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    ;; set up the stack
    mov rsp, kernel_stack

    call kmain

    ;; if something went wrong
    cli
    hlt

[SECTION .bss]
;; kernel stack / 32 kB
resb 32768
kernel_stack:
