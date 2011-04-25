[BITS 64]
[EXTERN isr_handler]
[EXTERN irq_handler]

[GLOBAL start_interrupts]
start_interrupts:
    sti
    ret

[GLOBAL stop_interrupts]
stop_interrupts:
    cli
    ret

%macro set_gate 2
    mov rax, %2                        ; load interrupt address

    mov word [idt+(%1*16)], ax         ; set first 16 bit of base

    mov word [idt+%1*16+2], 0x0008     ; set code selector
    mov byte [idt+%1*16+5], 0b10001110 ; set flags

    shr rax, 16
    mov word [idt+%1*16+6], ax         ; set middle 16 bit of base

    shr rax, 16
    mov dword [idt+%1*16+8], eax       ; set last 32 bit of base
%endmacro

[GLOBAL idt_init]
idt_init:
    ;; map first 32 interrupt service routines (and irqs)
    %assign i 0
    %rep 48
        set_gate i, isr%[i]
        %assign i i+1
    %endrep

    lidt [idt.pointer]
    ret

idt:
    times 256 * 16 db 0

.pointer:
    dw 256 * 16 - 1
    dq idt

;; pusha, popa macros // to push/pop all registers
%macro pusha 0
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
%endmacro

%macro popa 0
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
%endmacro

isr_common_stub:
    pusha

    call isr_handler

    mov rcx, 90000000
.l:
    nop
    loop .l

    popa
    add rsp, 0x38

    iretq

;; macros for interrupt service routines
%macro ISR_NOERRCODE 1
isr%1:
    push qword 0
    push qword %1
    jmp isr_common_stub
%endmacro

%macro ISR_ERRCODE 1
isr%1:
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

irq_common_stub:
    pusha

    call irq_handler

    popa
    add rsp, 0x38

    iretq

;; macro for interrupt requests
%macro IRQ 2
isr%2:
    push qword 0
    push qword %1
    jmp irq_common_stub
%endmacro

;; define all interrupt requests
IRQ 0,  32
IRQ 1,  33
IRQ 2,  34
IRQ 3,  35
IRQ 4,  36
IRQ 5,  37
IRQ 6,  38
IRQ 7,  39
IRQ 8,  40
IRQ 9,  41
IRQ 10, 42
IRQ 11, 43
IRQ 12, 44
IRQ 13, 45
IRQ 14, 46
IRQ 15, 47