global PORTAL
global GDT_FLUSH
extern main
[bits 64]
PORTAL:
    cli ;disable interrupt
	mov rsp, STACK_BOTTOM
    call main

GDT_R:
	dw GDT_END - GDT
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
