global ENTRY_HERE
extern main

jmp ENTRY_HERE

ENTRY_HERE: ;dont write anything before call main, it might destory the BootHeader.
	call main
	ret;never go here
	jmp $

