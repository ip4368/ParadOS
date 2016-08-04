 
global PORTAL
extern main

PORTAL:
    cli ;disable interrupt
    call main ;enter module loader
    jmp HALT ;if module loader is returned, that mean ParadOS is dead.

HALT: ;halt!
	cli
	hlt
	jmp HALT
