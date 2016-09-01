global GDT_FLUSH
extern gdt_r
GDT_FLUSH:
	
	lgdt [gdt_r]

	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax

	mov rax, new
	push qword 0x8
	push rax
	retf
new:
	ret