[BITS 64]

[GLOBAL outb]
outb:
    mov rax, rsi
    mov rdx, rdi
    out dx, al
    ret