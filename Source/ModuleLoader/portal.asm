global PORTAL
extern main
[bits 64]
PORTAL:
    cli ;disable interrupt

	lgdt [GDT_R]

	mov eax, 0x10
	push rax
	mov rax, STACK_BOTTOM
	push rax
	push 0x202
	mov eax, 0x8
	push rax
	mov rax, InNewGDT
	push rax
	iretq
InNewGDT:
	mov ax, 0x10
	mov es, ax
	mov ss, ax
	mov ds, ax
	mov fs, ax
	mov gs, ax

	lea rax, [rel main]
	call rax
    jmp HALT

GDT_R:
	dw GDT_END - GDT - 1
	dq GDT
GDT:
NULL: equ $ - GDT
	dq 0x0
CODE: equ $ - GDT
	dw 0xffff
	dw 0x0
	db 0x0
	db 0x9a
	db 0xaf
	db 0x0
DATA: equ $ - GDT
	dw 0xffff
	dw 0x0
	db 0x0
	db 0x92
	db 0xcf
	db 0x0
GDT_END:

HALT:
	cli
	hlt
	jmp HALT
section .bss
align 4096
STACK_TOP:
	resb 4096
STACK_BOTTOM:
