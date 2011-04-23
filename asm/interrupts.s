[BITS 64]
[GLOBAL init_interrupts]
[EXTERN isr_handler]

init_interrupts:
    ;; map first 32 interrupts
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
    push r8
    push r9
    push r10
    push r11
    push r12
    push r13
    push r14
    push r15

    mov ax, ds
    push rax

    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    call isr_handler

    pop rax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    pop r15
    pop r14
    pop r13
    pop r12
    pop r11
    pop r10
    pop r9
    pop r8
    pop rdi
    pop rsi
    pop rbp
    pop rdx
    pop rcx
    pop rbx
    pop rax

    add rsp, 0x38
    sti
    hlt
    iret

;; macros for interrupt service routines
%macro ISR_NOERRCODE 1
isr%1:
    cli
    push qword 0
    push qword %1
    jmp isr_common_stub
%endmacro

%macro ISR_ERRCODE 1
isr%1:
    cli
    push qword %1
    jmp isr_common_stub
%endmacro

;; define all interrupt service routines
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