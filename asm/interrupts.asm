[BITS 64]
[GLOBAL idt_init]
[EXTERN test_interrupt]

idt_init:
%assign i 0
%rep 32
    mov rax, isr%[i]                ; load interrupt address

    mov word [idt+(i*16)], ax       ; set first 16 bit of base

    mov word [idt+i*16+2], 0x08     ; set code selector
    mov word [idt+i*16+4], 0x8E00   ; set flags

    shr rax, 16
    mov word [idt+i*16+6], ax       ; set next 16 bit of base

    shr rax, 16
    mov dword [idt+i*16+8], eax     ; set last 32 bit of base
%assign i i+1
%endrep

    lidt [idt.pointer]
    ret

[SECTION .bss]
idt:
    resb 256*16

[SECTION .text]
.pointer:
    dw 256*16-1
    dq idt

isr_common_stub:
    push rax
    push rbx
    push rcx
    push rdx
    push rbp
    push rsi
    push rdi
    push rsp

    call test_interrupt

    pop rsp
    pop rdi
    pop rsi
    pop rbp
    pop rdx
    pop rcx
    pop rbx
    pop rax

    add esp, 8

    sti
    iret

;; define all interrupt service routines
%macro ISR_NOERRCODE 1
isr%1:
    cli
    push byte 0
    push byte %1
    jmp isr_common_stub
%endmacro

%macro ISR_ERRCODE 1
isr%1:
    cli
    push byte %1
    jmp isr_common_stub
%endmacro

ISR_NOERRCODE 0
ISR_NOERRCODE 1
ISR_NOERRCODE 2
ISR_NOERRCODE 3
ISR_NOERRCODE 4
ISR_NOERRCODE 5
ISR_NOERRCODE 6
ISR_NOERRCODE 7
ISR_ERRCODE   8
ISR_NOERRCODE 9
ISR_ERRCODE   10
ISR_ERRCODE   11
ISR_ERRCODE   12
ISR_ERRCODE   13
ISR_ERRCODE   14
ISR_NOERRCODE 15
ISR_NOERRCODE 16
ISR_NOERRCODE 17
ISR_NOERRCODE 18
ISR_NOERRCODE 19
ISR_NOERRCODE 20
ISR_NOERRCODE 21
ISR_NOERRCODE 22
ISR_NOERRCODE 23
ISR_NOERRCODE 24
ISR_NOERRCODE 25
ISR_NOERRCODE 26
ISR_NOERRCODE 27
ISR_NOERRCODE 28
ISR_NOERRCODE 29
ISR_NOERRCODE 30
ISR_NOERRCODE 31