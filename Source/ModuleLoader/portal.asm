global PORTAL
global GDT_FLUSH
extern main
[bits 64]
PORTAL:
    cli ;disable interrupt

    lea rax, [rel GDT_R]
    lgdt [rax]
    mov rsp, STACK_BOTTOM
    push qword 0x8
    push qword new
    retf
    new:
	mov ax, 0x10
	mov es, ax
	mov ss, ax
	mov ds, ax
	mov fs, ax
	mov gs, ax
	mov rsp, STACK_BOTTOM
    call main

GDT_R:
	dw 0x18
	dq GDT
GDT:
NULL:
	dq 0x0
CODE:
	dw 0xffff
	dw 0x0
	db 0x0
	db 0x9a
	db 0xaf
	db 0x0
DATA:
	dw 0xffff
	dw 0x0
	db 0x0
	db 0x92
	db 0xcf
	db 0x0

HALT:
	cli
	hlt
	jmp HALT
section .bss
align 4096
STACK_TOP:
	resb 4096
STACK_BOTTOM:
