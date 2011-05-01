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

    ;; set up a stack
    mov esp, kernel_stack.start

    ;; save multiboot information structure (as qword)
    push 0x0
    push ebx

    ;; setup the page tables
    mov edi, pml4
    mov cr3, edi
    xor eax, eax
    mov ecx, 4096
    rep stosd

    ;; add a first table chain
    mov edi, pml4
    mov dword [edi], pdpt
    or dword [edi], 7

    mov edi, pdpt
    mov dword [edi], pd
    or dword [edi], 7

    mov edi, pd
    mov dword [edi], pt
    or dword [edi], 7

    ;; fill the first two megabytes
    mov edi, pt
    mov ebx, 0x3
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

    ;; complete tss gdt entry
    mov eax, tss
    mov word [gdt.tss+2], ax
    shr eax, 16
    mov byte [gdt.tss+4], al
    mov byte [gdt.tss+7], ah

    ;; load the gdt
    lgdt [gdt.pointer]

    jmp 0x08:start64

align 8
gdt:
.null:
    dq 0

.code:
    dw 0xFFFF
    dw 0
    db 0
    db 0b10011010
    db 0b10101111
    db 0

.data:
    dw 0xFFFF
    dw 0
    db 0
    db 0b10010010
    db 0b10001111
    db 0

.tss:
    dw 0x0067
    dw 0
    db 0
    db 0b10001001
    db 0b10010000
    db 0

.pointer:
    dw $ - gdt - 1
    dq gdt

tss:
    times 65 dq 0

[BITS 64]
[EXTERN kmain]
start64:
    ;; clear segment registers
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    ;; pass multiboot information structure
    pop rdi
    call kmain

    ;; if something went wrong
    cli
    hlt

[SECTION .bss]
;; kernel stack / 32 kB
kernel_stack:
.end:
  resb 32768
.start:

;; basic paging structures
align 4096
pml4:
  resq 512
pdpt:
  resq 512
pd:
  resq 512
pt:
  resq 512