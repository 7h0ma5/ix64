[BITS 64]

[GLOBAL start_interrupts]
start_interrupts:
    sti
    ret

[GLOBAL stop_interrupts]
stop_interrupts:
    cli
    ret

set_gate:
    ;; calculate the offset
    mov rdx, 16                     ; multiply with 16 (16 byte per entry)
    mul dx
    add rax, idt                    ; add the idt base address

    ;; set idt entry
    mov word [rax], bx              ; set first 16 bit of base
    mov word [rax+2], 0x0008        ; set code selector
    mov byte [rax+5], 0b10001110    ; set flags
    shr rbx, 16
    mov word [rax+6], bx            ; set middle 16 bit of base
    shr rbx, 16
    mov dword [rax+8], ebx          ; set last 32 bit of base

    ret

[GLOBAL idt_init]
idt_init:
    ;; map first 32 interrupt service routines (and irqs)
    %assign i 0
    %rep 255
        [EXTERN isr%[i]]
        mov rax, i
        mov rbx, isr%[i]
        call set_gate
        %assign i i+1
    %endrep

    lidt [idt.pointer]
    ret

[SECTION .bss]
idt:
    resb 256*16

[SECTION .data]
.pointer:
    dw 256 * 16 - 1
    dq idt