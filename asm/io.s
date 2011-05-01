[BITS 64]

[GLOBAL outb]
outb:
    mov ax, si
    mov dx, di
    out dx, al
    ret

[GLOBAL inb]
inb:
    mov dx, di
    xor rax, rax
    in al, dx
    ret