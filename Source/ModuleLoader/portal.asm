 global PORTAL
extern main

;global PML4
;global PDP
;global PD
;global PT
PORTAL:
    cli ;disable interrupt
    mov rsp, STACK_BOTTOM
    call main
    jmp HALT

HALT:
	cli
	hlt
	jmp HALT

section .bss
align 4096
;PML4:
;	resb 4096
;PDP:
;	resb 4096
;PD:
;	resb 4096
;PT:
;	resb 4096
STACK_TOP:
	resb 4096
STACK_BOTTOM:
